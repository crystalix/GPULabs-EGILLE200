//header files
#include <iostream>

//header for sdl2 functionality
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "Vertex.h"
#include "Shader.h"

//maths	headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets";
#else
const std::string ASSET_PATH = "assets";
#endif
const std::string SHADER_PATH = "/shaders";

//global variables go here

//pointer to SDL window
SDL_Window * window;

GLuint triangleVBO;
GLuint triangleEBO;
GLuint VAO;

GLuint	shaderProgram=0;

//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;

Vertex triangleData[]={
//Front
{ -0.5f, 0.5f, 0.5f,
 1.0f, 0.0f, 1.0f, 1.0f },// Top Left
{ -0.5f, -0.5f, 0.5f,
 1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left
{ 0.5f, -0.5f, 0.5f,
 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
{ 0.5f, 0.5f, 0.5f,
 1.0f, 0.0f, 1.0f, 1.0f },// Top Right

//back
{ -0.5f, 0.5f, -0.5f,
 1.0f, 0.0f, 1.0f, 1.0f },// Top Left
{ -0.5f, -0.5f, -0.5f,
 1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left
{ 0.5f, -0.5f, -0.5f,
 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
{ 0.5f, 0.5f, -0.5f,
 1.0f, 0.0f, 1.0f, 1.0f },// Top Right
};

GLuint indices[]={
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
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &triangleEBO);
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//function to initialise opengl
void initOpenGL()
{
	//Ask for ver 3.2 ofopengl
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

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

	glewExperimental = GLU_TRUE;
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
	
}

//Function to draw
void render()
{
	//set the clear colour bkground
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	//clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(VAO);

	//Make the new VBO active. Repeat here as a sanity check(may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

	glUseProgram(shaderProgram);
	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE,	0, NULL);
	GLint MVPLocation =	glGetUniformLocation(shaderProgram,	"MVP");
	mat4 MVP = projMatrix*viewMatrix*worldMatrix;
	glUniformMatrix4fv(MVPLocation,	1,	GL_FALSE,	glm::value_ptr(MVP));

	glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);

	//require to swap the front and back buffer
	SDL_GL_SwapWindow(window);

}

//function to update game state
void update()
{
	projMatrix = glm::perspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(vec3(0.0f,	0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = glm::translate(mat4(1.0f), vec3(0.0f,0.0f,0.0f));
}

void initGeometry()

{
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );
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

void createShader()
{
	GLuint vertexShaderProgram=0;
	std::string	vsPath	= ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	vertexShaderProgram	= loadShaderFromFile(vsPath, VERTEX_SHADER);
				
	GLuint	fragmentShaderProgram=0;
	std::string	fsPath	=	ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	fragmentShaderProgram	=loadShaderFromFile(fsPath,	FRAGMENT_SHADER);

	shaderProgram	=	glCreateProgram();
	glAttachShader(shaderProgram,	vertexShaderProgram);
	glAttachShader(shaderProgram,	fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);

	glBindAttribLocation(shaderProgram,	0,	"vertexPosition");
				
	//now	we	can	delete	the	VS	&	FS	Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
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
	createShader();
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