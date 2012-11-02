#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <opencv2/opencv.hpp>
#include <cmath>

namespace Texture
{
class Texture
{
    bool loadtexture(std::string file, int i);
public:
    Texture();
    ~Texture();
    void loadTexture();
    void setTexture(int i);
};

Texture::Texture()
{
}

Texture::~Texture()
{

}

bool Texture::loadtexture(std::string file, int i)
{
    IplImage *image1 = cvLoadImage(file.c_str(), CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

    if (image1 == NULL)
        return false;

    cvCvtColor(image1, image1, CV_BGR2RGB);
    cvFlip(image1, NULL, 0);

    //glGenTextures(i, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, i);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->width, image1->height, GL_RGB, GL_UNSIGNED_BYTE, image1->imageData);

    cvReleaseImage( &image1 );
    return true;
}

void Texture::loadTexture()
{
    if (!loadtexture("./texture/zzzz.jpeg", 1))
    {
        std::cout << "LoadGLTextures error\n";
        exit(1);
    }
    if (!loadtexture("./texture/dc.jpeg", 2))
    {
        std::cout << "LoadGLTextures error\n";
        exit(1);
    }
}
void Texture::setTexture(int i)
{
    glBindTexture(GL_TEXTURE_2D, i);
}
}