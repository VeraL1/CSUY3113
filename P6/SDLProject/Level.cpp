#include "Level.h"

#define LEVEL1_ENEMY_COUNT 4
#define LEVEL1_MASK_COUNT 2

#define LEVEL1_WIDTH 27
#define LEVEL1_HEIGHT 27
unsigned int level1_data[] =
{
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1,
 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1,
 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1,
 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1,
 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1,
 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1,
 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

GLuint l1fontTextureID;

void Level::Initialize() {

	state.nextScene = -1;

	GLuint mapTextureID = Util::LoadTexture("tree.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 1, 1);

	Scene::Initialize();

	// Initialize Enemy
	state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
	GLuint enemyTextureID = Util::LoadTexture("elf.png");
	GLuint enemyTextureID2 = Util::LoadTexture("mononoke.png");

	state.enemies[0].entityType = ENEMY;
	state.enemies[0].textureID = enemyTextureID;
	state.enemies[0].position = glm::vec3(14, -4, 0);
	state.player[0].movement = glm::vec3(0);

	state.enemies[0].speed = 1;
	state.enemies[0].aiType = ELF1;
	state.enemies[0].aiState = WALKING;

	state.enemies[1].entityType = ENEMY;
	state.enemies[1].textureID = enemyTextureID;
	state.enemies[1].position = glm::vec3(14, -12, 0);
	state.player[1].movement = glm::vec3(0);

	state.enemies[1].speed = 1;
	state.enemies[1].aiType = ELF2;
	state.enemies[1].aiState = WALKING;

	state.enemies[2].entityType = ENEMY;
	state.enemies[2].textureID = enemyTextureID2;
	state.enemies[2].position = glm::vec3(21.5, -9, 0);
	state.player[2].movement = glm::vec3(0);

	state.enemies[2].speed = 1;
	state.enemies[2].aiType = MONONOKE;
	state.enemies[2].aiState = WALKING;

	state.enemies[3].entityType = ENEMY;
	state.enemies[3].textureID = enemyTextureID;
	state.enemies[3].position = glm::vec3(14, -18, 0);
	state.player[3].movement = glm::vec3(0);

	state.enemies[3].speed = 1;
	state.enemies[3].aiType = ELF3;
	state.enemies[3].aiState = WALKING;

	state.masks = new Entity[LEVEL1_MASK_COUNT];
	GLuint maskTextureID = Util::LoadTexture("mask.png");

	state.masks[0].entityType = MASK;
	state.masks[0].textureID = maskTextureID;
	state.masks[0].position = glm::vec3(9, -24, 0);

	state.masks[1].entityType = MASK;
	state.masks[1].textureID = maskTextureID;
	state.masks[1].position = glm::vec3(13, -11, 0);

	l1fontTextureID = Util::LoadTexture("font1.png");
}

void Level::Update(float deltaTime) {
	if (state.player->lives == 0) return;
	if (state.player->foundMask == 2) return;
	state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
	for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
		state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
	}
	for (int i = 0; i < LEVEL1_MASK_COUNT; i++) {
		state.masks[i].Update(deltaTime, state.player, state.masks, LEVEL1_MASK_COUNT, state.map);
	}
}

void Level::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.player->Render(program);
	for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
		state.enemies[i].Render(program);
	}

	for (int i = 0; i < LEVEL1_MASK_COUNT; i++) {
		state.masks[i].Render(program);
	}

	if (state.player->lives == 0) {
		Util::DrawText(program, l1fontTextureID, "You Lose!", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
	}

	if (state.player->foundMask == 2) {
		Util::DrawText(program, l1fontTextureID, "You Win!", 1.0f, -0.6f, glm::vec3(1.5f, -2.0, 0));
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

	if (state.player->foundMask == 0) {
		Util::DrawText(program, l1fontTextureID, "foundMask : 0", 1.0f, -0.6f, glm::vec3(1.5f, -3.0, 0));
	}
	if (state.player->foundMask == 1) {
		Util::DrawText(program, l1fontTextureID, "foundMask : 1", 1.0f, -0.6f, glm::vec3(1.5f, -3.0, 0));
	}
	else if (state.player->foundMask == 2) {
		Util::DrawText(program, l1fontTextureID, "foundMask : 2", 1.0f, -0.6f, glm::vec3(1.5f, -3.0, 0));
	}
}