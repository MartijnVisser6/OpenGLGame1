#include <gl\glew.h>
#include "GL/glfw3.h"
#include <vector>
class Square
{
public:
	
	Square();

	Square(float x, float y, float width, float height);
	
	~Square();

	void Update(float deltaTime);

	void Draw(GLuint shader_program);

	float positionX, positionY;
	float velocityX, velocityY;
private:

	GLuint VAO, VBO;

	void CreateVAO(float width, float height);

	std::vector<float> color;

	float m_width, m_height;
};