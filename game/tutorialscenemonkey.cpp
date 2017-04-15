#include <game/tutorialscenemonkey.h>
#include <engine/rendering/phongshader.h>
#include <engine/rendering/renderutils.h>
#include <cmath>

TutorialSceneMonkey::TutorialSceneMonkey(CoreEngine &coreEngine, UserInput &userInput, QObject *parent) :
	BaseTutorialScene(coreEngine, userInput, parent)
{
	m_mesh = new Mesh(*this, "monkey.obj", true);
	m_material = new Material(Vector3f(0, 1, 0));

	PhongShader *phongShader = new PhongShader(*this, m_camera);
	phongShader->setAmbientLight(Vector3f(0.1, 0.1, 0.1));
	phongShader->setDirectionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0.8), Vector3f(1, 1, -1)));
	m_shader = phongShader;
}

TutorialSceneMonkey::~TutorialSceneMonkey()
{
	delete m_shader;
	delete m_material;
	delete m_mesh;
}

static float temp = 0;
void TutorialSceneMonkey::update(float dt)
{
	BaseTutorialScene::update(dt);

	temp += dt;
	float sinValue = std::sin(temp);

	m_transform->setTranslation(sinValue * 2, -1, 5);
	m_transform->setRotation(0, sinValue * 180, 0);
}

void TutorialSceneMonkey::render()
{
	RenderUtils::clearScreen(*this);

	m_shader->bind();
	m_shader->updateUniforms(m_transform->transformation(), m_transform->projectedTransformation(), *m_material);
	m_mesh->draw();
}
