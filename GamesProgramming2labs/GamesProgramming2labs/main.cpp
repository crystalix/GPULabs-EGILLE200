//header files
#include <iostream>

//header for sdl2 functionality
#include <SDL.h>

//global variables go here

//pointer to SDL window
SDL_Window * window;

//constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480; 

void InitWindow(int width, int height, bool fullscreen)
{
	//create a window
	window = SDL_CreateWindow("Lab 1", //window title
		SDL_WINDOWPOS_CENTERED, // x pos centred
		SDL_WINDOWPOS_CENTERED, //y pos centred
		width, //width in pixels
		height, //height in pixels
		SDL_WINDOW_OPENGL // flags(control how window is created
		);

}

void CleanUp()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Main method-entry point

int main(int argc, char * arg[])
{
	//init everything-sdl if non zero we have a problem

	if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;
	}

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);
	CleanUp();
	return -1;
}