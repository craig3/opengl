//C++
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
//OpenGL
#include <GL/glew.h>
#include <GL/glut.h>
//OpenCV
#include <opencv2/opencv.hpp>
//C
#include <cmath>
//my include file
#include "Texture.h"
#include "Ground.h"
#include "Light.h"
#include "Material.h"
//define
#define KEY_ESC 27

//instance
Texture::Texture texture;
Ground::Ground ground(-10, -10, 10, 10, 2);
Light::Light light;
Material::Material material;

char TITLE[] = "OpenGL";

//mouse
int xBegin = 0, yBegin = 0;
int mButton = 10;
int mState = 10;

//looking angle & positionn
double px = 0, py = 0, pz = 0;
double twist, elevation, azimuth;

//view
const float nearw = 0.1, farw = 30.0, fovy = 60.0;

//draw character
void *font = GLUT_BITMAP_HELVETICA_10;
void drawString(const std::string str, void *font, float x, float y)
{
    glWindowPos2f(x, y);
    int sz = str.size();
    for (int i = 0; i < sz; ++i)
    {
        glutBitmapCharacter(font, str[i]);
    }
}
//keyboard event
void keyboard( unsigned char key, int x, int y )
{
    if ( key == KEY_ESC ) exit( 0 );
    if ( key == 'w')
    {
        px += cos(azimuth) * 0.5;
        pz += sin(azimuth) * 0.5;
    }
}

//click event
void click( int button, int state, int x, int y )
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        mButton = button;
        mState = state;
        xBegin = x;
        yBegin = y;
        px += cos(azimuth) * 0.5;
        px = fmin(px, 10);
        px = fmax(px, -10);
        pz += sin(azimuth) * 0.5;
        pz = fmin(pz, 10);
        pz = fmax(pz, -10);
    }
    if (state == GLUT_UP)
    {
        mButton = 10;
        mState = 10;
    }
}

//drag event
void drag(int x, int y)
{
    int xDisp, yDisp;

    xDisp = x - xBegin;
    yDisp = y - yBegin;
    switch (mButton)
    {
    default:
        azimuth = fmod(azimuth + xDisp / 100.0, 2 * M_PI);
        elevation = fmax(elevation + yDisp / 100.0, -M_PI / 2.0);
        elevation = fmin(elevation + yDisp / 100.0, M_PI / 2.0);
        break;
    }
    xBegin = x;
    yBegin = y;
}

//motion event
void motion(int x, int y)
{
    int xDisp, yDisp;

    xDisp = x - xBegin;
    yDisp = y - yBegin;
    azimuth = fmod(azimuth + xDisp / 50.0, 2 * M_PI);
    elevation = fmax(elevation + yDisp / 50.0, -M_PI / 2.0);
    elevation = fmin(elevation + yDisp / 50.0, M_PI / 2.0);
    xBegin = x;
    yBegin = y;
}

//init
void init (char *progname)
{
    glutInitWindowPosition(0, 0);
    glutInitWindowSize( 400, 400);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (255 / 255.0, 255 / 255.0, 255 / 255.0, 1.0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(click);
    glutMotionFunc(drag);
    glutPassiveMotionFunc(motion);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_LIGHT0 );

    texture.loadTexture();
    light.setLight();
}

//reshape
void reshape(int width, int height)
{
    float aspect = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, nearw, farw);
    glMatrixMode(GL_MODELVIEW);
}
//timer
void timer(int flag)
{
    if (flag == 1)
    {
        if (mButton == GLUT_LEFT_BUTTON && mState == GLUT_DOWN)
        {
            px += cos(azimuth) * 0.5;
            px = fmin(px, 10);
            px = fmax(px, -10);
            pz += sin(azimuth) * 0.5;
            pz = fmin(pz, 10);
            pz = fmax(pz, -10);
        }
        glutPostRedisplay();
        glutTimerFunc(50, timer, 1);
    }
}


//display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    glEnable( GL_NORMALIZE);
    glEnable( GL_AUTO_NORMAL);
    {
        glPushMatrix();
        {
            gluLookAt( 0.0 + px , 2.5 + py , 0 + pz, px + cos(azimuth) * (cos(elevation) + 0.000001), 2.5 - sin(elevation) + py, pz + sin(azimuth) * (cos(elevation) + 0.000001), 0, 1, 0);
            //std::cout<<0.0 + px <<" "<< 2.5 + py <<" "<< 0 + pz<<" "<< px + cos(azimuth)*cos(elevation)<<" "<< 2.5 - sin(elevation) + py<<" "<<pz + sin(azimuth)*cos(elevation)<<std::endl;
            //gluLookAt( 0, 2.5, 0, 1, -10, 0, 0, 1, 0);

            ground.drawGroundTex(1, 2);
            glPushMatrix();

            //glTranslated(0, 3, 0);
            material.setMaterial(Material::gold);
            glutSolidTeapot(0.1);
            glPopMatrix();
        }
        glPopMatrix();

        glPushMatrix();
        glColor3d(1, 1, 1);
        drawString("px:" + boost::lexical_cast<std::string>(px) + " pz:" + boost::lexical_cast<std::string>(pz), font, 10, 5);
        glPopMatrix();
    }

    glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );

    glutSwapBuffers();
}

//main
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    init(TITLE);
    glewInit();
    glutReshapeFunc (reshape);
    glutDisplayFunc(display);
    glutTimerFunc(50, timer, 1);
    glutMainLoop();
    return 0;
}