#include <cmath>
#include <QDebug>
#include <QList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "tutorialscene.h"
#include "renderutils.h"
#include "geometry/vector2f.h"
#include "graphics/phongshader.h"
#include <graphics/pointlight.h>

TutorialScene::TutorialScene(OpenGLWidget &openGLWidget, UserInput &userInput, QObject *parent) :
	BaseTutorialScene(openGLWidget, userInput, parent)
{
	m_mesh = new Mesh(*this);
	QList<Vertex> vertices;
	QVector<unsigned int> indices;
	m_texture = new Texture(*this, "test.png");
	m_material = new Material(m_texture, Vector3f(1, 1, 1), 1, 8);

	float fieldDepth = 10;
	float fieldWidth = 10;

	vertices += Vertex(Vector3f(-fieldWidth, 0, -fieldDepth), Vector2f(0, 0));
	vertices += Vertex(Vector3f(-fieldWidth, 0, fieldDepth * 3), Vector2f(0, 1));
	vertices += Vertex(Vector3f(fieldWidth * 3, 0, -fieldDepth), Vector2f(1, 0));
	vertices += Vertex(Vector3f(fieldWidth * 3, 0, fieldDepth * 3), Vector2f(1, 1));

	indices += 0;
	indices += 1;
	indices += 2;
	indices += 2;
	indices += 1;
	indices += 3;

	m_mesh->setVertices(vertices, indices, true);

	PhongShader *phongShader = new PhongShader(*this, m_camera);
	phongShader->setAmbientLight(Vector3f(0.1, 0.1, 0.1));
	phongShader->setDirectionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0.1), Vector3f(1, 1, -1)));
	m_shader = phongShader;

	PointLight *pointLight1 = new PointLight(BaseLight(Vector3f(1, 0.5, 0), 0.8),
											 Attenuation(0, 0, 1), Vector3f(-2, 0, 5), 10);
	PointLight *pointLight2 = new PointLight(BaseLight(Vector3f(0, 0.5, 1), 0.8),
											 Attenuation(0, 0, 1), Vector3f(2, 0, 7), 10);
	m_pointLights += pointLight1;
	m_pointLights += pointLight2;
	phongShader->setPointLights(m_pointLights);

	SpotLight *spotLight1 = new SpotLight(
				PointLight(BaseLight(Vector3f(0, 1, 1), 0.8), Attenuation(0, 0, 0.1), Vector3f(-2, 0, 5), 30),
				Vector3f(1, 1, 1), 0.7);
	m_spotLights += spotLight1;
	phongShader->setSpotLights(m_spotLights);
}

TutorialScene::~TutorialScene()
{
	qDeleteAll(m_pointLights);
	qDeleteAll(m_spotLights);
	delete m_shader;
	delete m_material;
	delete m_texture;
	delete m_mesh;
}

static float temp = 0;
void TutorialScene::update(float dt)
{
	BaseTutorialScene::update(dt);

	temp += dt;

	m_transform->setTranslation(0, -1, 5);

	m_pointLights.at(0)->setPosition(Vector3f(3, 0, 8 * std::sin(temp) + 10));
	m_pointLights.at(1)->setPosition(Vector3f(7, 0, 8 * std::cos(temp) + 10));

	m_spotLights.at(0)->pointLight().setPosition(m_camera->position());
	m_spotLights.at(0)->setDirection(m_camera->forward());
}

void TutorialScene::render()
{
	RenderUtils::clearScreen(*this);

	m_shader->bind();
	m_shader->updateUniforms(m_transform->transformation(), m_transform->projectedTransformation(), *m_material);
	m_mesh->draw();
}
