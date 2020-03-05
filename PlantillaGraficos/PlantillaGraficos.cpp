// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Vertice.h"
#include <vector>

using namespace std;

//Cada elemeto que queramos renderear necesita un vertex array y un buffer
vector<vertice> triangulo;
GLuint vertexArrayTriangulo;
GLuint bufferTrianguloID;

//Instancia del shader
Shader *shader;
//Identificadores para mapeo de atributos de entradea del vertex shader
GLuint posicionID;
GLuint colorID;

void inicializarTriangulo() {
	vertice v1 = {
		vec3(0.0f, 0.3f, 0.0f),
		vec4(0.8f, 0.1f, 0.0f, 1.0f)
	};
	vertice v2 = {
		vec3(-0.3f, -0.3f, 0.0f),
		vec4(0.8f, 0.1f, 0.0f, 1.0f)
	};
	vertice v3 = {
		vec3(0.3, -0.3, 0.0f),
		vec4(0.8f, 0.1f, 0.0f, 1.0f)
	};
	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
}

void dibujar() {

}

int main()
{
	//declarar una ventana
	GLFWwindow* window;

	//Si no se pudo iniciar glfw
	//terminamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo inicial glfw
	//inicializamos la ventana
	window = glfwCreateWindow(800, 600, "Ventana", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto se activan las funciones "modernas" (GPU)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK)
	{
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	inicializarTriangulo();

	const char* rutaVertexShader = "VertexShader.Shader";
	const char* rutaFragmentShader = "FragmentShader.Shader";
	shader = new Shader(rutaVertexShader, rutaFragmentShader);

	//ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(0.9, 0.2, 0.5, 1);
		//Borrar!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Actualizar valores y dibujar
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despues del ciclo de dibujo
	//Eliminamos ventana y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}

