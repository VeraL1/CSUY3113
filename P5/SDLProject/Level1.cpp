#include "Level1.h"

#define LEVEL1_ENEMY_COUNT 1

#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
unsigned int level1_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

GLuint l1fontTextureID;

void Level1::Initialize() {

	state.nextScene = -1;

	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);

	Scene::Initialize();

	// Initialize Enemy
	state.enemies = new Entity();
	GLuint enemyTextureID = Util::LoadTexture("ctg.png");

	state.enemies->entityType = ENEMY;
	state.enemies->textureID = enemyTextureID;
	state.enemies->position = glm::vec3(14, -4, 0);
	state.player->movement = glm::vec3(0);
	state.player->acceleration = glm::vec3(0, -9.81f, 0);

	state.enemies->speed = 1;
	state.enemies->aiType = WALKER;
	state.enemies->aiState = WALKING;

	l1fontTextureID = Util::LoadTexture("font1.png");
}

void Level1::Update(float deltaTime) {
	if (state.player->lives == 0) return;
	state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
	state.enemies->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);

	if (state.player->position.x >= 13 && state.player->lives != 0) {
		state.nextScene = 2;
	}
}

void Level1::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.player->Render(program);
	state.enemies->Render(program);

	if (state.player->lives == 0) {
		Util::DrawText(program, l1fontTextureID, "You Lose!", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}

	if (state.player->lives == 1) {
		Util::DrawText(program, l1fontTextureID, "Lives : 1", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}
	else if (state.player->lives == 2) {
		Util::DrawText(program, l1fontTextureID, "Lives : 2", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}
	else if (state.player->lives == 3) {
		Util::DrawText(program, l1fontTextureID, "Lives : 3", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}
}