#include "Scene.h"

void Scene::Initialize() {
	// Initialize Player
	state.player = new Entity();
	state.player->entityType = PLAYER;
	state.player->position = glm::vec3(5, 0, 0);
	state.player->movement = glm::vec3(0);
	state.player->acceleration = glm::vec3(0);
	state.player->speed = 3.0f;
	state.player->textureID = Util::LoadTexture("player.png");

	state.player->height = 1.0f;
	state.player->width = 1.0f;
}