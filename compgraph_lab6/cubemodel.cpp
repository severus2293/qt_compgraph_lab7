#include "cubemodel.h"
#include <cmath>
CubeModel::CubeModel(vector3 rotate,vector3 shift,vector3 scale,int angle,double side):
    Modeltool(rotate,shift,scale,angle)
{
 this->a = side;
    buildCoords();
}

void CubeModel::buildCoords(){
    coords.clear();
    int Num_cylinder = 4;
    double step = 360 / Num_cylinder;
    double p;
    for (int i = 0;i < Num_cylinder;i++) {
        p = step * i * 3.14 / 180;

        coords.push_back(vector3(a * cos(p),a * sin(p),1.0));
    }
}
