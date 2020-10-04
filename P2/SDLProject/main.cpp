#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include <cmath>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;
bool bounce_up = false;
bool bounce_down = false;
bool bounce_left = false;
bool bounce_right = false;

ShaderProgram program;
glm::mat4 viewMatrix, ballMatrix, projectionMatrix, player1Matrix, player2Matrix;

//initialization for ball
// Start at 0, 0, 0
glm::vec3 ball_position = glm::vec3(0, 0, 0);
// Don’t go anywhere (yet).
glm::vec3 ball_movement = glm::vec3(0, 0, 0);

float ball_speed = 0.5f;
GLuint ballTextureID;

//initialization for player1
glm::vec3 player1_position = glm::vec3(-2.96f, 0, 0);
// Don’t go anywhere (yet).
glm::vec3 player1_movement = glm::vec3(-2.96f, 0, 0);

float player1_speed = 1.0f;
GLuint player1TextureID;

//initialization for player2
glm::vec3 player2_position = glm::vec3(2.90f, 0, 0);
// Don’t go anywhere (yet).
glm::vec3 player2_movement = glm::vec3(2.90f, 0, 0);

float player2_speed = 1.0f;
GLuint player2TextureID;

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
	displayWindow = SDL_CreateWindow("Pong!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
	glewInit();
#endif

	glViewport(0, 0, 640, 480);

	program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");


	viewMatrix = glm::mat4(1.0f);
	ballMatrix = glm::mat4(1.0f);
	player1Matrix = glm::mat4(1.0f);
	player2Matrix = glm::mat4(1.0f);
	projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

	program.SetProjectionMatrix(projectionMatrix);
	program.SetViewMatrix(viewMatrix);

	glUseProgram(program.programID);

	glClearColor(0.40f, 0.60f, 0.00f, 0.5f);
	
	glEnable(GL_BLEND);
	// Good setting for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	ballTextureID = LoadTexture("football2.png");
	player1TextureID = LoadTexture("ctg.png");
	player2TextureID = LoadTexture("ctg.png");
}

void ProcessInput() {
	player1_movement = glm::vec3(0);
	player2_movement = glm::vec3(0);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
		case SDL_WINDOWEVENT_CLOSE:
			gameIsRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				break;
			}
			break; // SDL_KEYDOWN
		}
	}

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_UP]) {
		player2_movement.y = 1.0f;
	}
	else if (keys[SDL_SCANCODE_DOWN]) {
		player2_movement.y = -1.0f;
	}

	if (glm::length(player2_movement) > 1.0f) {
		player2_movement = glm::normalize(player2_movement);
	}

	if (keys[SDL_SCANCODE_W]) {
		player1_movement.y = 1.0f;
	}

	else if (keys[SDL_SCANCODE_S]) {
		player1_movement.y = -1.0f;
	}

	if (glm::length(player1_movement) > 1.0f) {
		player1_movement = glm::normalize(player1_movement);
	}
}

void ballMove() {
	if (bounce_up == false && bounce_down == false && bounce_left == false && bounce_right == false) {
		ball_movement.x = 1.0f;
		ball_movement.y = 1.0f;
	}
	else if (bounce_up == false && bounce_down == true && bounce_left == false && bounce_right == false) {
		ball_movement.x = 1.0f;
		ball_movement.y = -1.0f;
	}
	else if (bounce_up == true && bounce_left == true) {
		ball_movement.x = -1.0f;
		ball_movement.y = 1.0f;
	}
	else if (bounce_up == true && bounce_right == true) {
		ball_movement.x = 1.0f;
		ball_movement.y = 1.0f;
	}
	else if (bounce_down == true && bounce_left == true) {
		ball_movement.x = -1.0f;
		ball_movement.y = -1.0f;
	}
	else if (bounce_down == true && bounce_right == true) {
		ball_movement.x = 1.0f;
		ball_movement.y = -1.0f;
	}

	if (glm::length(ball_movement) < 1.0f) {
		ball_movement = glm::normalize(ball_movement);
	}
}

float lastTicks = 0.0f;

void Update() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float deltaTime = ticks - lastTicks;
	lastTicks = ticks;
	// Add (direction * units per second * elapsed time)
	
	//update for player1
	player1Matrix = glm::mat4(1.0f);
	player1Matrix = glm::scale(player1Matrix, glm::vec3(1.5f, 2.0f, 1.0f));

	if (player1_position.y <= 1.4 && player1_position.y >= -1.4) {
		player1_position += player1_movement * player1_speed * deltaTime;
		player1Matrix = glm::translate(player1Matrix, player1_position);
	}
	else {
		if(player1_position.y > 1.4){
			player1_position.y = 1.4;
		}
		else if (player1_position.y < -1.4) {
			player1_position.y = -1.4;
		}
		player1Matrix = glm::translate(player1Matrix, player1_position);
	}

	//update for player2
	player2Matrix = glm::mat4(1.0f);
	player2Matrix = glm::scale(player2Matrix, glm::vec3(1.5f, 2.0f, 1.0f));

	if (player2_position.y <= 1.4 && player2_position.y >= -1.4) {
		player2_position += player2_movement * player2_speed * deltaTime;
		player2Matrix = glm::translate(player2Matrix, player2_position);
	}
	else {
		if (player2_position.y > 1.4) {
			player2_position.y = 1.4;
		}
		else if (player2_position.y < -1.4) {
			player2_position.y = -1.4;
		}
		player2Matrix = glm::translate(player2Matrix, player2_position);
	}

	//update for ball
	ballMatrix = glm::mat4(1.0f);
	ballMatrix = glm::scale(ballMatrix, glm::vec3(0.5f, 0.5f, 1.0f));

	ballMove();

	if (ball_position.x > 4.5 || ball_position.x < -4.5) {
		gameIsRunning = false;
		return;
	}
	else {
		//check if the ball bounce the upper and lower bound of the screen
		if (ball_position.y <= 3.5 && ball_position.y >= -3.5) {
			ball_position += ball_movement * ball_speed * deltaTime;
			ballMatrix = glm::translate(ballMatrix, ball_position);
		}
		else{
			if (ball_position.y > 3.5) {
				ball_position.y = 3.5;
				bounce_down = true;
				bounce_up = false;
			}
			else if (ball_position.y < -3.5) {
				ball_position.y = -3.5;
				bounce_up = true;
				bounce_down = false;
			}
			ballMatrix = glm::translate(ballMatrix, ball_position);
		}

		//check if the ball bounce with player1
		float xdist1 = fabs(ball_position.x - player1_position.x) - 1.0;
		float ydist1 = fabs(ball_position.y - player1_position.y) - 1.25;

		float xdist2 = fabs(player2_position.x - ball_position.x) - 1.0;
		float ydist2 = fabs(player2_position.y - ball_position.y) - 1.25;

		if (xdist1 < 0 && ydist1 < 0) {
			bounce_right = true;
			bounce_left = false;
			ballMatrix = glm::translate(ballMatrix, ball_position);
		}

		else if (xdist2 < 0 && ydist2 < 0) {
			bounce_left = true;
			bounce_right = false;
			ballMatrix = glm::translate(ballMatrix, ball_position);
		}

		else {
			ball_position += ball_movement * ball_speed * deltaTime;
			ballMatrix = glm::translate(ballMatrix, ball_position);
		}
	}
}


void drawPlayer1() {
	program.SetModelMatrix(player1Matrix);
	glBindTexture(GL_TEXTURE_2D, player1TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawPlayer2() {
	program.SetModelMatrix(player2Matrix);
	glBindTexture(GL_TEXTURE_2D, player2TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawBall() {
	program.SetModelMatrix(ballMatrix);
	glBindTexture(GL_TEXTURE_2D, ballTextureID);
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
	drawBall();
	drawPlayer1();
	drawPlayer2();
	
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