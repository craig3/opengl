#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <boost/assign.hpp>

namespace Material
{
enum material { emerald, jade, obsidian, gold, silver, copper, bronze, black_plastic, red_plastic };
class Material
{
    std::map<material, std::vector<float> > ambient =
        boost::assign::map_list_of
        (emerald, std::vector<float> {0.0215, 0.1745, 0.0215, 1})
        (jade, std::vector<float> {0.135, 0.2225, 0.1575})
        (obsidian, std::vector<float> {0.05375, 0.05, 0.06625})
        (gold, std::vector<float> {0.24725, 0.1995, 0.0745})
        (silver, std::vector<float> {0.19225, 0.19225, 0.19225})
        (copper, std::vector<float> {0.19125, 0.0735, 0.0225})
        (bronze, std::vector<float> {0.2125, 0.1275, 0.054})
        (black_plastic, std::vector<float> {0.0, 0.0, 0.0, 1.0})
        (red_plastic, std::vector<float> {0.0, 0.0, 0.0, 0.0});

    std::map<material, std::vector<float> > diffuse =
        boost::assign::map_list_of
        (emerald, std::vector<float> {0.07568, 0.61424, 0.07568, 1})
        (jade, std::vector<float> {0.54, 0.89, 0.63, 1.0})
        (obsidian, std::vector<float> {0.18275, 0.17, 0.22525, 1.0})
        (gold, std::vector<float> {0.75164, 0.60648, 0.22648, 1.0})
        (silver, std::vector<float> {0.50754, 0.50754, 0.50754, 1.0})
        (copper, std::vector<float> {0.7038, 0.27048, 0.0828, 1.0})
        (bronze, std::vector<float> {0.714, 0.4284, 0.18144, 1.0})
        (black_plastic, std::vector<float> {0.01, 0.01, 0.01, 1.0})
        (red_plastic, std::vector<float> {0.5, 0.0, 0.0, 1.0});

    std::map<material, std::vector<float> > specular =
        boost::assign::map_list_of
        (emerald, std::vector<float> {0.633, 0.727811, 0.633})
        (jade, std::vector<float> {0.316228, 0.316228, 0.316228, 1.0})
        (obsidian, std::vector<float> {0.332741, 0.328634, 0.346435, 1.0})
        (gold, std::vector<float> {0.628281, 0.555802, 0.366065, 1.0})
        (silver, std::vector<float> {0.508273, 0.508273, 0.508273, 1.0})
        (copper, std::vector<float> {0.256777, 0.137622, 0.086014, 1.0})
        (bronze, std::vector<float> {0.393548, 0.271906, 0.166721, 1.0})
        (black_plastic, std::vector<float> {0.50, 0.50, 0.50, 1.0})
        (red_plastic, std::vector<float> {0.7, 0.6, 0.6, 1.0});

    std::map<material, std::vector<float> > emission =
        boost::assign::map_list_of
        (emerald, std::vector<float> {0, 0, 0, 1})
        (jade, std::vector<float> {0, 0, 0, 1})
        (obsidian, std::vector<float> {0, 0, 0, 1})
        (gold, std::vector<float> {0, 0, 0, 1})
        (silver, std::vector<float> {0, 0, 0, 1})
        (copper, std::vector<float> {0, 0, 0, 1})
        (bronze, std::vector<float> {0, 0, 0, 1})
        (black_plastic, std::vector<float> {0, 0, 0, 1})
        (red_plastic, std::vector<float> {0, 0, 0, 1});

    std::map<material, int > shininess =
        boost::assign::map_list_of
        (emerald, 76.8)
        (jade, 12.8)
        (obsidian, 38.4)
        (gold, 51.2)
        (silver, 51.2)
        (copper, 12.8)
        (bronze, 25.8)
        (black_plastic, 32)
        (red_plastic, 32);

public:
    Material();
    ~Material();

    void setMaterial(material m);

};
Material::Material()
{

}
Material::~Material()
{

}
void Material::setMaterial(material m)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &ambient[m][0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &diffuse[m][0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &specular[m][0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &emission[m][0]);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess[m]);

}
}