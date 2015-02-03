#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GL/glfw3.h>

#include "Square.h"
#include <vector>

class Game1
{
public:
	Game1(GLFWwindow * renderwindow)
	{
		window = renderwindow;

		Initialize();

		// Program loop
		while (!glfwWindowShouldClose(window))
		{
			// Check and call events
			glfwPollEvents();

			Render();
		}

		glfwTerminate();
	}

	void compile_shaders()
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		static const GLchar * vertex_shader_source[] =
		{
			"#version 330 core									\n"
			"                                                   \n"
			"layout (location = 0) in vec3 position;			\n"
			"uniform vec4 color;								\n"
			"uniform vec3 offset;                               \n"
			"out vec4 vs_color;									\n"
			"void main()									    \n"
			"{													\n"
			"	gl_Position = vec4(position + offset,1.0f);		\n"
			"	vs_color = color;								\n"
			"}													\n"
		};

		static const GLchar * fragment_shader_source[] =
		{
			"#version 330 core									\n"
			"in  vec4 vs_color;									\n"
			"out vec4 color;                                    \n"
			"													\n"
			"void main()                                        \n"
			"{                                                  \n"
			"	color = vs_color;					    		\n"
			"}													\n"
		};

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		shader_program = glCreateProgram();
		glAttachShader(shader_program, vertex_shader);
		glAttachShader(shader_program, fragment_shader);
		glLinkProgram(shader_program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		GLint vertexsuccess;
		GLchar infoLog[512];
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertexsuccess);

		if (!vertexsuccess)
		{
			glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		GLint fragmentsuccess;
		GLchar infoLog2[512];
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragmentsuccess);

		if (!fragmentsuccess)
		{
			glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog2);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog2 << std::endl;
		}
	}
	
	void Initialize()
	{
		compile_shaders();
	}
	
	void Render()
	{
		const GLfloat color[] = { 0.0, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
		
		//Calculate the time between the previous loop call and this loop call
		float time = glfwGetTime();
		float deltaTime = time - previoustime;
		previoustime = time;

		timer += deltaTime;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			
			squares.push_back(Square((x/1024 - .5) *2, (y/768 -.5) * -2, 0.005, 0.005));
		}

		for (int i = 0; i < squares.size(); ++i)
		{			
			//Update and draw the squares
			squares[i].Update(deltaTime);
			squares[i].Draw(shader_program);
		}

		// Swap the buffers
		glfwSwapBuffers(window);
	}
	
	
private:

	GLFWwindow * window;
	GLuint shader_program;
	GLuint VAO;
	GLuint VBO;

	std::vector<Square> squares;
	
	float previoustime = glfwGetTime();
	float timer;
};

// The MAIN function, from here we start our application and run our Program/Game loop
int main()
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "LearnOpenGL", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, 1024, 768);

	Game1 game(window);
	
	return 0;
}