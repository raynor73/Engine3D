#include <game/terrainscene.h>
#include <engine/rendering/renderutils.h>
#include <utils.h>
#include <engine/rendering/directionallight.h>
#include <engine/rendering/phongshader.h>

TerrainScene::TerrainScene(UserInput &userInput, QObject *parent) :
	BaseTutorialScene(userInput, parent)
{
	m_material = new Material(Vector3f(1, 1, 1));

	m_camera->setPosition(Vector3f(-166, 538, -112));
}

TerrainScene::~TerrainScene()
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

void TerrainScene::makeOpenGLDependentSetup()
{
	BaseTutorialScene::makeOpenGLDependentSetup();

	m_mesh = new Mesh(*m_openGLFunctions, "terrain0.obj", true);
	PhongShader *phongShader = new PhongShader(*m_openGLFunctions, m_camera);
	phongShader->setAmbientLight(Vector3f(0.1, 0.1, 0.1));
	phongShader->setDirectionalLight(DirectionalLight(BaseLight(Vector3f(1, 1, 1), 0.8),
													  Vector3f(1, 1, -1)));
	m_shader = phongShader;
}

void TerrainScene::render()
{
	BaseTutorialScene::render();

	//RenderUtils::clearScreen(*m_openGLFunctions);

	m_shader->bind();
	m_shader->updateUniforms(m_transform->transformation(), m_transform->projectedTransformation(),
							 *m_material);
	m_mesh->draw();
}
