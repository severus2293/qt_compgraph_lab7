#include "splinemodel.h"
#include <cmath>
SplineModel::SplineModel(vector3 rotate,vector3 shift,vector3 scale,int angle,double h,double r,int partition):
    Modeltool(rotate,shift,scale,angle)
{
    this->h = h;
    this->r = r;
    this->partition = partition;
    buildCoords();
}


void SplineModel::buildCoords(){
    coords.clear();
    double step =  h / partition;
    double p;
    double cur = 0;
    for (int i = 0;i < partition;i++) {
        p = step * i * 3.14 / 180;
        cur += 0.1;
        coords.push_back(vector3(r * sin(p),r * cos(p),cur));
    }
}
