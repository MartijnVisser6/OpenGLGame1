#include "GL/glfw3.h"
#include <gl\glew.h>
class Square
{
public:
	
	Square(float x, float y, float width, float height);
	
	~Square();

	void Update();

	void Draw(GLuint program);

private:

	GLuint VAO, VBO;

	void CreateVAO(float x, float y, float width, float height);
};