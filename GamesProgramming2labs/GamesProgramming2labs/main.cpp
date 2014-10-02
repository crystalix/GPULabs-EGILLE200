//header files
#include <iostream>

//header for sdl2 functionality
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "Vertex.h"

//global variables go here

//pointer to SDL window
SDL_Window * window;

GLuint triangleVBO;
GLuint triangleEBO;

Vertex triangleData[] =
{
	//front
	{-0.5f, 0.5f, 0.5f, //x, y, z
	1.0f, 0.0f, 1.0f, 1.0f}, //r, g, b, a   Top left
	
	{-0.5f, -0.5f, 0.5f, //x, y, z
	1.0f, 1.0f, 0.0f, 1.0f}, //r, g, b, a  Bottom left

	{0.5f, -0.5f, 0.5f, //x, y, z
	0.0f, 1.0f, 1.0f, 1.0f}, //r, g, b, a  bottom right

	{0.5f, 0.5f, 0.5f,
	 1.0f, 0.0f, 1.0f, 1.0f}, //top right


	  /*left
	 {-0.5f, 0.5f, 0.5f,
	 1.0f, 0.0f, 1.0f, 1.0f}, //top left

	{-0.5f, -0.5f, 0.5f,
	1.0f, 0.0f, 1.0f, 1.0f}, // bottom left

	{ -0.5f, -0.5f, -0.5f,
    0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

    {-0.5f, 0.5f, -0.5f,
     1.0f, 0.0f, 1.0f, 1.0f },// Top Right


	 //right
	 {0.5f, 0.5f, 0.5f,
	 1.0f, 0.0f, 1.0f, 1.0f}, //top left

	{0.5f, -0.5f, 0.5f,
	1.0f, 0.0f, 1.0f, 1.0f}, // bottom left

	{ 0.5f, -0.5f, -0.5f,
    0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

    {0.5f, 0.5f, -0.5f,
     1.0f, 0.0f, 1.0f, 1.0f },// Top Right

	 
	 //bottom
	{-0.5f, -0.5f, -0.5f,
	 1.0f, 0.0f, 1.0f, 1.0f}, //top left

	{-0.5f, -0.5f, 0.5f,
	1.0f, 0.0f, 1.0f, 1.0f}, // bottom left

	{ 0.5f, -0.5f, 0.5f,
    0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

    {0.5f, -0.5f, -0.5f,
     1.0f, 0.0f, 1.0f, 1.0f },// Top Right

	 //top
	{-0.5f, 0.5f, -0.5f,
	 1.0f, 0.0f, 1.0f, 1.0f}, //top left

	{-0.5f, 0.5f, 0.5f,
	1.0f, 0.0f, 1.0f, 1.0f}, // bottom left

	{ 0.5f, 0.5f, 0.5f,
    0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

    {0.5f, 0.5f, -0.5f,
     1.0f, 0.0f, 1.0f, 1.0f },// Top Right*/


	//back
	{-0.5f, 0.5f, -0.5f,
	 1.0f, 0.0f, 1.0f, 1.0f}, //top left

	{-0.5f, -0.5f, -0.5f,
	1.0f, 0.0f, 1.0f, 1.0f}, // bottom left

	{ 0.5f, -0.5f, -0.5f,
    0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

    {0.5f, 0.5f, -0.5f,
     1.0f, 0.0f, 1.0f, 1.0f }// Top Right

};

GLuint indices[]=
{
	//front
 0,1,2,
 0,3,2,
 
 //left
 4,5,1,
 4,1,0,
 
 //right
 3,7,2,
 7,6,2,
 
 //bottom
 1,5,2,
 6,2,1,
 
 //top
 5,0,7,
 5,7,3,
 
 //back
 4,5,6,
 4,7,6
};

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
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
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

	GLenum err = glewInit();
	if ( GLEW_OK != err)
	{
		/*Problem: Glew Init failed, something is seriously wrong*/
		std::cout<< "Error: " <<glewGetErrorString(err) << std::endl;
	}
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

//Function to draw
void render()
{
	//set the clear colour bkground
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	//clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Make the new VBO active. Repeat here as a sanity check(may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

	// the 3 parameters are now filled out, the pipeline needs to know the size of each vertex
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);

	//The last parameter basically says that the colours start 3 floats into each element of the array
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));

	//Establish array contains vertices and colours
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT,0);

	//drawing stuff bit
	//switch to model view
	glMatrixMode(GL_MODELVIEW);
	//reset using identity matrix
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0f, 0.0, 1.0, 0.0); 

	//translate to -6f on z axis(set depth)
	glTranslatef(0.0f, 0.0f, -6.0f);

	glRotatef(45.0f,1.0f,1.0f,1.0f);

	//draw triangle

	glDrawArrays(GL_TRIANGLES,0,sizeof(triangleData) / (3*sizeof(float)));

	/*glTranslatef(0.0f, 3.0f, -6.0f);
	glDrawArrays(GL_TRIANGLES,0,sizeof(triangleData) / (3*sizeof(float)));*/

	//require to swap the front and back buffer
	SDL_GL_SwapWindow(window);

}

//function to update game state
void update()
{

}

void initGeometry()

{
	//create buffer
	glGenBuffers(1, &triangleVBO);
	//make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Copy vertex data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &triangleEBO);
	//make EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	//copy index data to EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
	initGeometry();

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

		update();
		render();

	}

	CleanUp();
	return -1;
}