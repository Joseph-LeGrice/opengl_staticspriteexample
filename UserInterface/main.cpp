#include <iostream>
#include <SDL.h>
#include "Renderer.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_INIT Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_DisplayMode currentDisplayMode;
	if (SDL_GetCurrentDisplayMode(0, &currentDisplayMode) != 0)
	{
		std::cout << "SDL_GetCurrentDisplayMode Error:" << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	int width = 480;
	int height = 640;
	int screenX = (int)(0.5f * (currentDisplayMode.w - width));
	int screenY = (int)(0.5f * (currentDisplayMode.h - height));
	SDL_Window *window = SDL_CreateWindow("Tetris", screenX, screenY, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		std::cout << "SDL_GL_CreateContext Error:" << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Renderer *r = new Renderer();
	r->Render();
	SDL_GL_SwapWindow(window);
	SDL_Delay(3000);
	delete r;

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}