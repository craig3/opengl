#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <opencv2/opencv.hpp>
#include <cmath>

namespace Light
{
class Light
{
    int light_num = 1;
    std::vector<int > light {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
    std::vector<std::vector<float> > ambient {{0, 0, 0, 1}};
    std::vector<std::vector<float> > diffuse {{ 1, 1, 1, 1}};
    std::vector<std::vector<float> > specular {{1, 1, 1, 1}};

    std::vector<std::vector<float> > position {{0, 5, 0, 1}};

    std::vector<std::vector<float> > spot_direction {{0, 0, 0}};
    std::vector<int > spot_exponent {0};
    std::vector<int > spot_cutoff {90};

    std::vector<int > constant_attenuation {1};
    std::vector<int > liner_attenution {0};
    std::vector<int > quadratic_attenution {0};
public:
    Light();
    ~Light();

    void setLight();
};
Light::Light()
{

}
Light::~Light()
{

}
void Light::setLight()
{
    for (int i = 0; i < light_num; ++i)
    {
        glEnable(light[i]);
        glLightfv(light[i], GL_AMBIENT, &ambient[i][0]);
        glLightfv(light[i], GL_DIFFUSE, &diffuse[i][0]);
        glLightfv(light[i], GL_SPECULAR, &specular[i][0]);

        glLightfv(light[i], GL_POSITION, &position[i][0]);

        glLightfv(light[i], GL_SPOT_DIRECTION, &spot_direction[i][0]);
        glLighti(light[i], GL_SPOT_EXPONENT, spot_exponent[i]);
        glLighti(light[i], GL_SPOT_CUTOFF, spot_cutoff[i]);


        glLighti(light[i], GL_CONSTANT_ATTENUATION, constant_attenuation[i]);
        glLighti(light[i], GL_LINEAR_ATTENUATION, liner_attenution[i]);
        glLighti(light[i], GL_QUADRATIC_ATTENUATION, quadratic_attenution[i]);
    }
}
}