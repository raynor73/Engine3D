#include <game/tutorialscenemonkey.h>
#include <engine/rendering/renderutils.h>
#include <cmath>

TutorialSceneMonkey::TutorialSceneMonkey(UserInput &userInput, QObject *parent) :
	BaseTutorialScene(userInput, parent),
	m_mesh(NULL),
	m_material(NULL),
	m_shader(NULL)
{
//	m_material = new Material(Vector3f(0, 1, 0));
}

TutorialSceneMonkey::~TutorialSceneMonkey()
{
	if (m_shader != NULL) {
		delete m_shader;
		m_shader = NULL;
	}

	if (m_mesh != NULL) {
		delete m_mesh;
		m_mesh = NULL;
	}

	delete m_material;
}

void TutorialSceneMonkey::makeOpenGLDependentSetup()
{
	BaseTutorialScene::makeOpenGLDependentSetup();

	m_mesh = new Mesh(*m_openGLFunctions, "monkey.obj");

	/*PhongShader *phongShader = new PhongShader(*m_openGLFunctions, m_camera);
	phongShader->setAmbientLight(Vector3f(0.1, 0.1, 0.1));
	phongShader->setDirectionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0.8), Vector3f(1, 1, -1)));
	m_shader = phongShader;*/
}

//static float temp = 0;
void TutorialSceneMonkey::update(float dt)
{
	BaseTutorialScene::update(dt);

	/*temp += dt;
	float sinValue = std::sin(temp);*/

	/*m_transform->setTranslation(sinValue * 2, -1, 5);
	m_transform->setRotation(0, sinValue * 180, 0);*/
}

void TutorialSceneMonkey::render()
{
	BaseTutorialScene::render();

	//RenderUtils::clearScreen(*m_openGLFunctions);

	m_shader->bind();
//	m_shader->updateUniforms(m_transform->transformation(), m_transform->projectedTransformation(), *m_material);
	m_mesh->draw();
}
