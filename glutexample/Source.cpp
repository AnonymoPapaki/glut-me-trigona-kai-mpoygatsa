#include "GL\glew.h"
#include "GL\glut.h"

class Model
{
	//perigrafh toy vertexbuffer
	GLuint vertexBuffer;
	int start, count;
	//idiotites tou model
	float rotateZ;
	float posx, posy;
	float whateva;
	//...
public:
	Model(GLuint thisIsTheGPURamPointer, int start, int count)
	{
		this->vertexBuffer = thisIsTheGPURamPointer;
		this->start = start;
		this->count = count;
		rotateZ = posx = posy = whateva = 0;
	}
	void MoveLeft()
	{
		posx -= 0.1;
	}
	void MoveRight()
	{
		posx += 0.1;
	}
	void MoveUp() {
		//...
	}
	void RotateLeft()
	{
		rotateZ -= 1;
	}
	void RotateRight()
	{
		rotateZ += 1;
	}
	//whateva..

	void Draw()
	{
		//arxh ths pipeline

		//setaroume se on auto gia gia na paiksoume me vertex buffers
		glEnableVertexAttribArray(0);

		//epilegoume ton buffer me ton opoion tha doylepsoyme (o opoios prepei nanai sth VRAM)
		glBindBuffer(GL_VERTEX_ARRAY, this->vertexBuffer);
		//perigrafoume ton buffer to ti exei
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//efarmozoyme to transformation tou model
		//panta se diko tou matrix
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(this->posx, this->posy, 0);
		glRotatef(this->rotateZ, 0, 0, 1);
		

		//kaloyme thn draw h opoia trexei ton vertex kai pixel shader
		glDrawArrays(GL_TRIANGLES, this->start, this->count);
		glPopMatrix();




	}
};


GLuint parallelogramMesh;

Model *model1, *model2, *selected;


void init();
void render();
void idle();
void resize(int, int);
void keyboard(unsigned char,int,int);

int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Breakwhateva");
	glewInit();
	glutReshapeFunc(resize);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	init();
	glutMainLoop();
	return 0;
}

void init()
{
	//load from file..
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	glGenBuffers(1, &parallelogramMesh);
	glBindBuffer(GL_ARRAY_BUFFER, parallelogramMesh);
	//transfer to gpu ram
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// ftiaxnoume ta model mas
	model1 = new Model(parallelogramMesh, 0, 3);
	model2 = new Model(parallelogramMesh, 0, 3);
	selected = model1;
	//ta opoia exoyn to idio mesh
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//vazoyme to modelview (oxi oti to theloyme sto context mas, alla etsi paei to world view projection)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//kaloume ta models mas
	model1->Draw();
	model2->Draw();
	//...

	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void resize(int, int)
{
	glViewport(0, 0, 600, 600);
}



void keyboard(unsigned char key, int, int)
{

	switch (key)
	{
	case 'a': selected->MoveLeft(); break;
	case 'd': selected->MoveRight(); break;
	case 'z': selected->RotateLeft(); break;
	case 'x': selected->RotateRight(); break;
	case '1': selected = model1; break;
	case '2': selected = model2; break;

	default:
		break;
	}
}
