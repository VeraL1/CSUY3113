#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, playerMatrix, projectionMatrix, sunMatrix, cloud1Matrix, cloud2Matrix;

//initialization for player
float player_x = 0;
float player_y = 2;
GLuint playerTextureID;

//initialization for sun
float sun_x = -3.5;
float sun_y = 2.5;
float sun_rotate = 0;
GLuint sunTextureID;

//initialization for cloud1
float cloud1_x = -2;
float cloud1_y = 2;
GLuint cloud1TextureID;

//initialization for cloud2
float cloud2_x = 3.5;
float cloud2_y = 2.5;
GLuint cloud2TextureID;

GLuint LoadTexture(const char* filePath) {
	int w, h, n;
	unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);

	if (image == NULL) {
		std::cout << "Unable to load image. Make sure the path is correct\n";
		assert(false);
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(image);
	return textureID;
}

void Initialize() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Sky!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
	glewInit();
#endif

	glViewport(0, 0, 640, 480);

	program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");


	viewMatrix = glm::mat4(1.0f);
	playerMatrix = glm::mat4(1.0f);
	sunMatrix = glm::mat4(1.0f);
	cloud1Matrix = glm::mat4(1.0f);
	cloud2Matrix = glm::mat4(1.0f);
	projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

	program.SetProjectionMatrix(projectionMatrix);
	program.SetViewMatrix(viewMatrix);

	glUseProgram(program.programID);

	glClearColor(0.53f, 0.81f, 0.98f, 0.5f);
	
	glEnable(GL_BLEND);
	// Good setting for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	playerTextureID = LoadTexture("parachute.png");
	sunTextureID = LoadTexture("sun.png");
	cloud1TextureID = LoadTexture("cloud.png");
	cloud2TextureID = LoadTexture("cloud.png");
}

void ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			gameIsRunning = false;
		}
	}
}

float lastTicks = 0.0f;

void Update() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float deltaTime = ticks - lastTicks;
	lastTicks = ticks;
	
	//updates for the player
	player_y -= 0.3f * deltaTime;

	playerMatrix = glm::mat4(1.0f); 
	playerMatrix = glm::scale(playerMatrix, glm::vec3(1.5f, 1.5f, 1.0f));
	playerMatrix = glm::translate(playerMatrix, glm::vec3(player_x, player_y, 0.0f));

	//update for the sun
	sun_rotate += 45.0f * deltaTime;

	sunMatrix = glm::mat4(1.0f);
	sunMatrix = glm::translate(sunMatrix, glm::vec3(sun_x, sun_y, 0.0f));
	sunMatrix = glm::rotate(sunMatrix, glm::radians(sun_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	sunMatrix = glm::scale(sunMatrix, glm::vec3(1.5f, 1.5f, 1.0f));

	//update for cloud 1
	cloud1_x += 0.5f * deltaTime;
	cloud1Matrix = glm::mat4(1.0f);
	cloud1Matrix = glm::translate(cloud1Matrix, glm::vec3(cloud1_x, cloud1_y, 0.0f));
	cloud1Matrix = glm::scale(cloud1Matrix, glm::vec3(2.0f, 2.0f, 1.0f));

	//update for cloud2
	cloud2_x -= 0.5f * deltaTime;
	cloud2Matrix = glm::mat4(1.0f);
	cloud2Matrix = glm::translate(cloud2Matrix, glm::vec3(cloud2_x, cloud2_y, 0.0f));
	cloud2Matrix = glm::scale(cloud2Matrix, glm::vec3(2.5f, 2.5f, 1.0f));
}

void drawSun() {
	program.SetModelMatrix(sunMatrix);
	glBindTexture(GL_TEXTURE_2D, sunTextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawPlayer() {
	program.SetModelMatrix(playerMatrix);
	glBindTexture(GL_TEXTURE_2D, playerTextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawCloud1() {
	program.SetModelMatrix(cloud1Matrix);
	glBindTexture(GL_TEXTURE_2D, cloud1TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawCloud2() {
	program.SetModelMatrix(cloud2Matrix);
	glBindTexture(GL_TEXTURE_2D, cloud2TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
	float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program.positionAttribute);
	glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program.texCoordAttribute);

	//draw objects
	drawSun();
	drawPlayer();
	drawCloud1();
	drawCloud2();
	
	glDisableVertexAttribArray(program.positionAttribute);
	glDisableVertexAttribArray(program.texCoordAttribute);

	SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	Initialize();

	while (gameIsRunning) {
		ProcessInput();
		Update();
		Render();
	}

	Shutdown();
	return 0;
}