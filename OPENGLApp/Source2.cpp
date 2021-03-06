//GLEW
//#define GLEW_STATIC
//#include <glew.h>
//GLAD
#include <glad\glad.h>
//GLFW
#include <glfw3.h>
#include <iostream>
//permite la compilacion externa de los shaders
#include "ShaderCompiler.h"

//permite la carga de texturas
#include "stb_image.h"

using namespace std;

float valor=0.5f;
void add() {
	valor = valor + 0.1f;
}

void sub() {
	valor = valor - 0.1f;
}

void clearGreen(GLFWwindow* window) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glfwSwapBuffers(window);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	/*if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}
	
	/*if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}*/
	if (key == GLFW_KEY_UP) {
		add();
	}

	if (key == GLFW_KEY_DOWN) {
		sub();
	}
	
	//Cuando un usuario presione la tecla de escape, WindowShouldClose se pondra en true
	//Cerrando la aplicacion

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearningOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glfwSetKeyCallback(window, key_callback);

	//glewExperimental = GL_TRUE;
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//Vertices del triangulo a dibujar
	/*GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f, //Top Right
		 0.5f, -0.5f, 0.0f, //Bottom Right
		-0.5f, -0.5f, 0.0f, //Bottom Left
		-0.5f,  0.5f, 0.0f	//Top Left
	};
	GLfloat vertices[] = {
		//posiciones         //Colores
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	GLfloat texCoord[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};
	*/
	GLfloat vertices[] = {
		//posiciones			//Colores		//Textura
		 0.5f,   0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,   0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f
	};
	/*
	GLfloat vertices[] = {
		 0.5f, -0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f 
	};
	*/
	/*GLfloat vertices[] = {
		//Primer Triangulo
		-0.25f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.1f, -0.5f, 0.0f,
		//Segundo Triangulo
		0.25f, 0.5f, 0.0f,
		0.1f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};*/

	GLuint indices[] = {
		0, 1, 3, //Primer triangulo (superior)
		1, 2, 3  //Segundo Triangulo (inferior)
	};

	//Creacion del buffer
	GLuint VBO1;
	//Genera un nombre o ID para el buffer
	glGenBuffers(1, &VBO1);

	GLuint VBO2;
	glGenBuffers(1, &VBO2);
	//VER CAST EN VAO
	//Binds a buffer to a buffer type
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Copia el contenido el array vertices al buffer VBO, siendo del mismo tamano
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Codigo del vertex shader en GLSL
	

	//Utilizaremos el ShaderCompiler que fue definido de manera anterior
	Shader shader("vertexShader.vs", "fragmentShader.fs");
	/*
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
//		"out vec4 vertexColor;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//		"vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
		"}\0";
*/
/*
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = vec4(position, 1.0f);\n"
		"ourColor = aColor;\n"
		"}\0";


/*	const GLchar* fragmentShaderSource1 = "#version 330 core\n"
//		"in vec4 vertexColor;\n"
		"out vec4 color;\n"
		"uniform vec4 uniColor;\n"
		"void main()\n"
		"{\n"
		"color = uniColor;\n"
		//"color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\0";

	const GLchar* fragmentShaderSource1 = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		"vertexColor = vec4(ourColor, 1.0f);\n"
		"}\0";
	const GLchar* fragmentShaderSource2 = "#version 330 core\n"
		"in vec4 vertexColor;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vertexColor;\n"
		//"color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\0";
	//Compilacion del VertexShader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Compilacion del Fragment Shader
	GLuint fragmentShader1;
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);

	GLuint fragmentShader2;
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	//Es necesario unir estos 2 shaders en un program
	GLuint shaderProgram1, shaderProgram2;
	shaderProgram1 = glCreateProgram();
	shaderProgram2 = glCreateProgram();
	
	//Adjuntamos los shaders antes programados al programa
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);

	//Linkeamos al programa
	glLinkProgram(shaderProgram1);
	glLinkProgram(shaderProgram2);

	//Borramos los shaders del program para evitar errores
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);
*/
	//Linking vertex attributes
	//Le decimos al VBO como interpretar los datos de la matriz de vertices
	//1. El primer parametro es el vertex attribute que vamos a utilizar, en este caso es el 0 dado por location=0 en el vertex shader
	//2. Este parametro muestra el tamano del vertex attribute, en este caso es 3 por vec3 dado en el vertex shader
	//3. Tipo de datos a utilizar, es float por defecto en vec
	//4. Permite determinar si queremos normalizar los datos o no
	//5. Muestra el "stride", que es el tamano entre los diferentes datos que son pasados. En este caso se utiliza 3 porque son 3 flotantes.
	//6. Es el "offset" de donde comienza los datos en el buffer. Para este caso es 0 ya que no tiene offset. Necesita ese cast raro de GLvoid*
	//VER CAST EN VAO
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	//Creamos un VAO - Vertex Array Object que permite hacer un bind para que todos los subsiguientes llamadas a las VBO se guarden en dicho array
	GLuint VAO1;
	glGenVertexArrays(1, &VAO1);

	//GLuint VAO2;
	//glGenVertexArrays(1, &VAO2);
	//HAcemos el Bind del VAO (Vertex Array Object)
	glBindVertexArray(VAO1);

	//Esta parte estaba hecha antes, cuando no se utilizaba un VAO
	//En este caso se utiliza el VAO para evitar llamadas para cada objeto a dibujar.

	//Primero se realiza el bind del Vertex Buffer Object
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Luego se realiza el bind del Element Buffer Objects EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Realizamos los atributos del VAO para la lectura de los datos y su posterior envio hacia el vertex shader
		//Atributos: location, int size, tipoDato, Normalizado?, Stride, Offset

		//Para el location 0, utilizamos 3 datos (vertices del triangulo), de tipo float, con normalizacion falsa,
		//el sizeof(float) es 6 ya que tenemos 6 datos (3 vertices y 3 colores) y el offset es 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//location es 1 (para los colores) y el offset es de 3 (ya que para cada vertex set, los primeros 3 datos son de vertices
		//y el segundo es de colores)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//location 2 es para las texturas 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);


		

	//Unbind el VAO
	glBindVertexArray(0);
/*
	glBindVertexArray(VAO2);

		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	*/
	//Creamos el objeto de texturas
	GLuint texture1, texture2;

	glGenTextures(1, &texture1);
	glGenTextures(1, &texture2);

	//------------------------------TEXTURA 1

	//Bindeamos el objeto al tipo GL_texture_2d
	glBindTexture(GL_TEXTURE_2D, texture1);

	//Seteamos los parametros para la textura
	//Para el eje X
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//Para el eje Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Este color unicamente se define si CLAMP_TO_BORDER ha sido implementado
	float borderColor[] = {
		1.0f, 0.0f, 0.0f, 0.0f
	};
	//Pasamos el color a los parametros de la textura
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	//utilizamos stb_image para cargar las texturas

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("container1.jpg", &width, &height, &nrChannel, 0);

	//Generamos la textura mediante glteximage2d
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//generamos el Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	//------------------------------TEXTURA 2
	
	glBindTexture(GL_TEXTURE_2D, texture2);
	//Seteamos los parametros para la textura
	//Para el eje X
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//Para el eje Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	data = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//generamos el Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	
	shader.use();
	//shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	while (!glfwWindowShouldClose(window))
	{
		//Chequea si exitieron eventos (botones, cambios en el porte)
		glfwPollEvents();
		//Comandos para el rendering
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat time = glfwGetTime();

		//valor = (sin(time) / 2) + 0.5;
		//GLfloat rojo = (sin(time) / 2) + 0.5;
		//cout << rojo << endl;
		//Unicolor es un uniform. Es decir, es un atributo del shader que puede ser accedido desde afuera del shader.
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram1, "uniColor");
		//Para actualizar el valor del uniform, es necesario utilizar primero el programa
		//glUseProgram(shaderProgram1);
		//Se actualiza el uniform mediante la funcion Uniform, la cual es una funcion sobrecargada (es necesario tener en cuenta)
		//el tipo de dato que tendremos que mandar.
		//glUniform4f(vertexColorLocation, rojo, rojo, rojo, 1.0f);

		
		shader.use();
		//shader.setFloat("offset", 0.25f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		glBindVertexArray(VAO1);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
/*
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glBindVertexArray(0);
*/
		glfwSetKeyCallback(window, key_callback);

		shader.setFloat("visible", valor);
		//Intercambio de buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}
