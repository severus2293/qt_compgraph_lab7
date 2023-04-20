#ifndef CUBEMODEL_H
#define CUBEMODEL_H
#include "modeltool.h"
#include "vector3.h"
#include <vector>
class CubeModel: public Modeltool
{
public:
    double a;
    std::vector <vector3> coords;
    CubeModel(vector3 rotate = vector3(1,0,0),vector3 shift = vector3(0,0,0),vector3 scale = vector3(1,1,1),int angle = 0,double side = 0.5);
    void buildCoords();
};

#endif // CUBEMODEL_H
