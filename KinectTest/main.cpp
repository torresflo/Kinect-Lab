#include <iostream>

#include <GL\glut.h>

#include <KinectCore\Kinect\Sensor.hpp>

GLuint textureID;

Kinect::Sensor sensor;
Kinect::Error lastError = Kinect::Error::NoError;

unsigned int width = 640;
unsigned int height = 480;

void infiniteRotateCamera()
{
	static double angle = 0.;
	static double radius = 7.;
	double x = radius*sin(angle);
	double z = radius*(1 - cos(angle)) - radius / 2;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, 0, z, 0, 0, radius / 2, 0, 1, 0);
	angle += 0.05;
}

void draw3DScene()
{
	unsigned char* color = reinterpret_cast<unsigned char*>(sensor.getColorImage().getData());
	GLfloat* vertex = reinterpret_cast<GLfloat*>(sensor.getDepthImage().getData());

	infiniteRotateCamera();
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < width*height; ++i)
	{
		glColor3ub(color[i * 3], color[i * 3 + 1], color[i * 3 + 2]);
		glVertex3f(vertex[i * 3], vertex[i * 3 + 1], vertex[i * 3 + 2]);
	}
	glEnd();
}

void drawColorImage()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)sensor.getColorImage().getData());
	glBegin(GL_QUADS);
	glColor3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -0.75f, 1.80f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -0.75f, 1.80f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 0.75f, 1.80f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 0.75f, 1.80f);
	glEnd();
}

void update()
{
	//Kinect
	lastError = sensor.update();
	if (lastError != Kinect::Error::NoError)
	{
		std::cout << "Return of update sensor: " << Kinect::toString(lastError) << std::endl;
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//drawColorImage();
		draw3DScene();

		glutSwapBuffers();
	}
}

int main(int argc, char** argv)
{
	/////////////// Kinect ///////////////
	lastError = sensor.init();
	std::cout << "Return of init sensor : " << Kinect::toString(lastError) << std::endl;

	if (lastError != Kinect::Error::NoError)
	{
		return 1;
	}

	////////// Window & GLUT ///////////

	//GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Kinect - OpenGL");
	glutDisplayFunc(update);
	glutIdleFunc(update);

	//OpenGL setup
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);

	//Textures
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Configure the camera
	GLdouble ratio = static_cast<GLdouble>(width) / height;
	GLdouble fov = 45.0;
	GLdouble nearValue = 0.1;
	GLdouble farValue = 150.0;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ratio, nearValue, farValue);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, 0.01, 0, 1, 0);

	glutMainLoop();
	return 0;
}