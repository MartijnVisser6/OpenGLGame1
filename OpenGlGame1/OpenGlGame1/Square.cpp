#include "Square.h"

Square::Square()
{

}

Square::Square(float x, float y, float width, float height)
{
	//Compute random color;
	color = { static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
		static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
		static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
		1.0f };

	//Set the position of the square
	positionX = x;
	positionY = y;

	//Set the velocitys of the square
	velocityX = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))-0.5) / 1;
	velocityY = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))-0.5) / 1;

	//Set width and height of the square
	m_width = width;
	m_height = height;
	//Creat a vertex array object
	CreateVAO(width, height);
}

Square::~Square()
{
}

void Square::Update(float deltaTime)
{
	positionX += deltaTime * velocityX;
	positionY += deltaTime * velocityY;

	if (m_width + positionX >= 1 || positionX <= -1)
		velocityX = -velocityX;
	if (m_height + positionY >= 1 || positionY <= -1)
		velocityY = -velocityY;
}

void Square::Draw(GLuint shader_program)
{
	glUseProgram(shader_program);
	glBindVertexArray(VAO);

	GLuint offsetLocation = glGetUniformLocation(shader_program, "offset");	
	float offsetData[] = { positionX, positionY, 0.0f };
	glUniform3fv(offsetLocation, 1, offsetData);

	GLuint colorLocation = glGetUniformLocation(shader_program, "color");
	float scolor[] = { (float)color[0], (float)color[1], (float)color[2], (float)color[3] };
	glUniform4fv(colorLocation, 1, scolor);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Square::CreateVAO(float width, float height)
{
	float data[] =
	{
		0.0f, 0.0f, 0.0f,
		0.0f, height, 0.0f,
		width, 0.0f, 0.0f,

		width, 0.0f, 0.0f,
		0.0f, height, 0.0f,
		width, height, 0.0f
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