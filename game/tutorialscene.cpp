#include <cmath>
#include <QDebug>
#include <QList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <game/tutorialscene.h>
#include <engine/rendering/renderutils.h>
#include <engine/core/vector2f.h>
#include <engine/rendering/phongshader.h>
#include <engine/components/pointlight.h>

TutorialScene::TutorialScene(UserInput &userInput, QObject *parent) :
	BaseTutorialScene(userInput, parent),
	m_mesh(NULL),
	m_texture(NULL),
	m_material(NULL),
	m_shader(NULL)
{
	PointLight *pointLight1 = new PointLight(BaseLight(Vector3f(1, 0.5, 0), 0.8),
											 Attenuation(0, 0, 1), Vector3f(-2, 0, 5), 10);
	PointLight *pointLight2 = new PointLight(BaseLight(Vector3f(0, 0.5, 1), 0.8),
											 Attenuation(0, 0, 1), Vector3f(2, 0, 7), 10);
	m_pointLights += pointLight1;
	m_pointLights += pointLight2;

	SpotLight *spotLight1 = new SpotLight(
				PointLight(BaseLight(Vector3f(0, 1, 1), 0.8), Attenuation(0, 0, 0.1), Vector3f(-2, 0, 5), 30),
				Vector3f(1, 1, 1), 0.7);
	m_spotLights += spotLight1;
}

TutorialScene::~TutorialScene()
{
	qDeleteAll(m_pointLights);
	qDeleteAll(m_spotLights);
	if (m_shader != NULL) {
		delete m_shader;
		m_shader = NULL;
	}
	if (m_material != NULL) {
		delete m_material;
		m_material = NULL;
	}
	if (m_texture != NULL) {
		delete m_texture;
		m_texture = NULL;
	}
	if (m_mesh != NULL) {
		delete m_mesh;
		m_mesh = NULL;
	}
}

void TutorialScene::makeOpenGLDependentSetup()
{
	BaseTutorialScene::makeOpenGLDependentSetup();

	m_mesh = new Mesh(*m_openGLFunctions);
	QList<Vertex> vertices;
	QVector<unsigned int> indices;
	m_texture = new Texture(*m_openGLFunctions, "test.png");
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

	/*PhongShader *phongShader = new PhongShader(*m_openGLFunctions);
	phongShader->setAmbientLight(Vector3f(0.1, 0.1, 0.1));
	phongShader->setDirectionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0.1), Vector3f(1, 1, -1)));
	m_shader = phongShader;

	phongShader->setPointLights(m_pointLights);
	phongShader->setSpotLights(m_spotLights);*/
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
	BaseTutorialScene::render();

	//RenderUtils::clearScreen(*m_openGLFunctions);

	m_shader->bind();
	//m_shader->updateUniforms(m_transform->transformation(), m_transform->projectedTransformation(), *m_material);
	m_mesh->draw();
}
