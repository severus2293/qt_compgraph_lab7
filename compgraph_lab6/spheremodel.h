#ifndef SPHEREMODEL_H
#define SPHEREMODEL_H
#include "modeltool.h"
#include "vector3.h"
#include <vector>

class SphereModel: public Modeltool
{
public:
    double R;
    int slices;
    int stacks;
    std::vector <vector3> coords;
    SphereModel(vector3 rotate = vector3(1,0,0),vector3 shift = vector3(0,0,0),vector3 scale = vector3(1,1,1),int angle = 0,double R = 0.5,int slices = 13, int stacks = 26);
    void buildCoords();
};

#endif // SPHEREMODEL_H
