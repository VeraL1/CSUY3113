#include "MainPage.h"

#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
unsigned int mainpage_data[] =
{
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

GLuint fontTextureID;

void MainPage::Initialize() {

	state.nextScene = -1;

	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, mainpage_data, mapTextureID, 1.0f, 4, 1);

	Scene::Initialize();

	fontTextureID = Util::LoadTexture("font1.png");
}

void MainPage::Update(float deltaTime) {
	state.player->Update(deltaTime, state.player, NULL, 0, state.map);
}

void MainPage::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.player->Render(program);
	Util::DrawText(program, fontTextureID, "George's Adventure!", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
}