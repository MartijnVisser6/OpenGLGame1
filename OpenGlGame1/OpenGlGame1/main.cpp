#include <iostream>
using namespace std;

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GL/glfw3.h>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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
			"in vec3 position;									\n"
			"void main()									    \n"
			"{													\n"
			"	gl_Position = vec4(position,1.0f);				\n"
			"}													\n"
		};

		static const GLchar * fragment_shader_source[] =
		{
			"#version 330 core									\n"
			"													\n"
			"out vec4 color;                                    \n"
			"													\n"
			"void main()                                        \n"
			"{                                                  \n"
			"	color = vec4(0.3f, 0.0f, 0.0f, 1.0f);    		\n"
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
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}

		GLint fragmentsuccess;
		GLchar infoLog2[512];
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragmentsuccess);

		if (!fragmentsuccess)
		{
			glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog2);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog2 << endl;
		}
	}

	
	void Initialize()
	{
		compile_shaders();

		float data[] = {
			-0.25f, -0.25f, 0.0f,
			0.25f, 0.25f, 0.0f,
			0.25f, -0.25f, 0.0f,

			-0.25f, 0.25f, 0.0f,
			-0.25f, -0.25f, 0.0f,
			0.25f, 0.25f, 0.0f
		};
		
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}
	
	void Render()
	{
		
		glBindVertexArray(VAO);
		// Render
		// Clear the colorbuffer
		const GLfloat color[] = { /*sin(glfwGetTime()) * 0.5 + */0.5, 0.3f, 0.6f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
		glUseProgram(shader_program);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Swap the buffers
		glfwSwapBuffers(window);
	}
	
	// Is called whenever a key is pressed/released via GLFW
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		cout << key << endl;
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
private:

	GLFWwindow * window;
	GLuint shader_program;
	GLuint VAO;
	GLuint VBO;

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

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	//glfwSetKeyCallback(window, key_callback);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, 800, 600);

	Game1 game(window);
	
	return 0;
}