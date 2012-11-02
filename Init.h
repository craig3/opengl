#include <vector>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <opencv2/opencv.hpp>

namespace Init{
	class Init
	{
	public:
		Init();
		~Init();
		void init(std::string title);
	};
	Init::Init(){
	}
	Init::~Init(){
	}
	void Init::init(std::string title){
		glutInitWindowPosition(0, 0);
		glutInitWindowSize( 400, 400);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutCreateWindow(progname);
		glClearColor (1.0, 0.0, 0.0, 1.0);
		glutKeyboardFunc(keyboard);
		glutMouseFunc(click);
		glutMotionFunc(drag);
		glutPassiveMotionFunc(motion);
		glShadeModel( GL_SMOOTH );
		glEnable( GL_LIGHT0 );
		if(!texture.loadTexture("./texture/zzzz.jpeg",1)){
			std::cout<<"LoadGLTextures error\n";
			exit(1);
		}
		if(!texture.loadTexture("./texture/dc.jpeg",2)){
			std::cout<<"LoadGLTextures error\n";
			exit(1);
		}
	}
}