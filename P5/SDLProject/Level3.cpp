#include "Level3.h"

#define LEVEL3_ENEMY_COUNT 1

#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
unsigned int level3_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3,
 3, 1, 2, 2, 1, 1, 1, 0, 1, 1, 1, 3, 3, 3,
 3, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 3, 3, 3
};

GLuint l3fontTextureID;

void Level3::Initialize() {

	state.nextScene = -1;

	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);

	Scene::Initialize();

	// Initialize Enemy
	state.enemies = new Entity();
	GLuint enemyTextureID = Util::LoadTexture("ctg.png");
	
	state.enemies->entityType = ENEMY;
	state.enemies->textureID = enemyTextureID;
	state.enemies->position = glm::vec3(9, -4, 0);
	state.player->movement = glm::vec3(0);
	state.player->acceleration = glm::vec3(0, -9.81f, 0);

	state.enemies->speed = 1.5;
	state.enemies->aiType = CHASER;
	state.enemies->aiState = WALKING;

	l3fontTextureID = Util::LoadTexture("font1.png");
}

void Level3::Update(float deltaTime) {
	if (state.player->lives == 0) return;
	if (state.player->position.x > 13) return;

	state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
	state.enemies->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
}

void Level3::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.player->Render(program);
	state.enemies->Render(program);

	if (state.player->position.x >= 13 && state.player->lives != 0) {
		Util::DrawText(program, l3fontTextureID, "You Win!", 1.0f, -0.6f, glm::vec3(13.0f, -2.0, 0));
		return;
	}
	if (state.player->lives == 0) {
		Util::DrawText(program, l3fontTextureID, "You Lose!", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}

	if (state.player->lives == 1) {
		Util::DrawText(program, l3fontTextureID, "Lives : 1", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}
	else if (state.player->lives == 2) {
		Util::DrawText(program, l3fontTextureID, "Lives : 2", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}
	else if (state.player->lives == 3) {
		Util::DrawText(program, l3fontTextureID, "Lives : 3", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}
}