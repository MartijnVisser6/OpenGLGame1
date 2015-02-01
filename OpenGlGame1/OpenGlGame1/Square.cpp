#include "Square.h"
Square::Square(float x, float y, float width, float height)
{

}

Square::~Square()
{

}

void Square::Update()
{

}

void Square::Draw(GLuint program)
{

}

void Square::CreateVAO(float x, float y, float width, float height)
{
	float data[] =
	{
		x, y, 0.0f,
		x, y - height, 0.0f,
		x + width, y, 0.0f,

		x + width, y, 0.0f,
		x, y - height, 0.0f,
		x + width, y - height, 0.0f
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}