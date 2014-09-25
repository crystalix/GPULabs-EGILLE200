//header files
#include <iostream>

//header for sdl2 functionality
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>

//global variables go here

//pointer to SDL window
SDL_Window * window;

//constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480; 
bool running = true;
//SDL GL Context
SDL_GLContext glContext = NULL;



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
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//function to initialise opengl
void initOpenGL()
{
	//create opengl content
	glContext = SDL_GL_CreateContext(window);
	//something went wrong in creating the context if its still null
	if(!glContext)
	{
		std::cout << "Error creating GL context" <<SDL_GetError() << std::endl;
	}
	//smooth shading
	glShadeModel(GL_SMOOTH);

	//clear bkground to black
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	//clear depth buffer to 1
	glClearDepth(1.0f);

	//enable depth testing
	glEnable(GL_DEPTH_TEST);

	//the depth test to use
	glDepthFunc(GL_LEQUAL);

	//turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ratio
	GLfloat ratio;
	
	//make sure height is always above 0
	if(height == 0)
	{
		height=1;
	}

	//calculate screen ratio
	ratio = (GLfloat) width / (GLfloat) height;

	//setup viewport
	glViewport(0,0,(GLsizei)width, (GLsizei)height);

	//change to project matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//calculate perspective matrix, using glu library functions
	gluPerspective(45.0f,ratio,0.1f, 100.0f);

	//switch to model view
	glMatrixMode(GL_MODELVIEW);

	//reset using identity matrix
	glLoadIdentity();
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

	//call our init opengl function
	initOpenGL();

	//set our viewport
	setViewport(WINDOW_WIDTH,WINDOW_HEIGHT);

	SDL_Event event;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			//get event type
			if(event.type ==SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//sets game loop bool to false
				running= false;
			}

		}

	}

	CleanUp();
	return -1;
}