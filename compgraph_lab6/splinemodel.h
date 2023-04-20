#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H
#include <QOpenGLWidget>
#include "vector3.h"
#include <vector>
#include "modeltool.h"
class SplineModel: public Modeltool
{
public:
    double r;
    double h;
    int partition;
    SplineModel(vector3 rotate = vector3(1,0,0),vector3 shift = vector3(0,0,0),vector3 scale = vector3(1,1,1),int angle = 0,double h = 720,double r = 0.5,int partition = 36);
    void buildCoords();
    std::vector<vector3> coords;
};

#endif // SPLINEMODEL_H
