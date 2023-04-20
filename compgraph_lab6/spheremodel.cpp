#include "spheremodel.h"
#include <cmath>
SphereModel::SphereModel(vector3 rotate,vector3 shift,vector3 scale,int angle,double R,int slices, int stacks): Modeltool(rotate,shift,scale,angle)
{
  this->R = R;
    this->slices = slices;
    this->stacks = stacks;
    buildCoords();
}

void SphereModel::buildCoords(){
    coords.clear();
    float drho = (float)(3.141592653589) / (float) stacks;
    float dtheta = 2.0f * (float)(3.141592653589) / (float) slices;
    float ds = 1.0f / (float) slices;
    float dt = 1.0f / (float) stacks;
    float t = 1.0f;
    float s = 0.0f;
    int i, j;

     for (i = 0; i < stacks; i++)
    {
        float rho = (float)i * drho;
        float srho = (float)(sin(rho));
        float crho = (float)(cos(rho));
        float srhodrho = (float)(sin(rho + drho));
        float crhodrho = (float)(cos(rho + drho));

        s = 0.0f;
        for ( j = 0; j <= slices; j++)
        {
            float theta = (j == slices) ? 0.0f : j * dtheta;
            float stheta = (float)(-sin(theta));
            float ctheta = (float)(cos(theta));

            float x = stheta * srho;
            float y = ctheta * srho;
            float z = crho;

            coords.push_back(vector3(x * R, y * R, z * R));

            x = stheta * srhodrho;
        y = ctheta * srhodrho;
        z = crhodrho;
            s += ds;

            coords.push_back(vector3(x * R, y * R, z * R));
        }
        t -= dt;
    }
}
