#ifndef TORMODEL_H
#define TORMODEL_H
#include "modeltool.h"
#include "vector3.h"
#include <vector>

class TorModel: public Modeltool
{
public:
    double R;
    double r;
    int theta;
    int phi;
    std::vector <vector3> coords;
    TorModel(vector3 rotate = vector3(1,0,0),vector3 shift = vector3(0,0,0),vector3 scale = vector3(1,1,1),int angle = 0,double R = 1.0,double r = 0.2,int theta = 40,int phi = 25);
    void buildCoords();
};

#endif // TORMODEL_H
