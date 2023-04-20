#ifndef MODELTOOL_H
#define MODELTOOL_H
#include "vector3.h"

class Modeltool
{
public:
    Modeltool(vector3 rotate = vector3(1,0,0),vector3 shift = vector3(0,0,0),vector3 scale = vector3(1,1,1),int angle = 0);
    vector3 rotate;
    vector3 shift;
    vector3 scale;
    int angle = 0;

};

#endif // MODELTOOL_H
