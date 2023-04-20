#ifndef CYLINDERMODEL_H
#define CYLINDERMODEL_H
#include "modeltool.h"
#include "vector3.h"
#include <vector>
class CylinderModel: public Modeltool
{
public:
    double h;
    double r;
    int partition;
    std::vector <vector3> coords;
    CylinderModel(vector3 rotate = vector3(1,0,0),vector3 shift = vector3(0,0,0),vector3 scale = vector3(1,1,1),int angle = 0,double h = 2.0,double r = 0.5,int partition = 36);
    void buildCoords();
};

#endif // CYLINDERMODEL_H
