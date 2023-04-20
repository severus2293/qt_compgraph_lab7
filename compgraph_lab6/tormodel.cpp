#include "tormodel.h"
#include <cmath>


TorModel::TorModel(vector3 rotate,vector3 shift,vector3 scale,int angle,double R,double r,int theta,int phi):
    Modeltool(rotate,shift,scale,angle)
{
 this->R = R;
 this->r = r;
 this->theta = theta;
 this->phi = phi;
  buildCoords();
}

void TorModel::buildCoords(){
    coords.clear();
    double majorStep = 2.0f * 3.14159265358979323846 / theta;
        double minorStep = 2.0f * 3.14159265358979323846 / phi;
        int i, j;

        for (i = 0; i < theta; ++i)
        {
                double a0 = i * majorStep;
                double a1 = a0 + majorStep;
                float x0 = (float) cos(a0);
                float y0 = (float) sin(a0);
                float x1 = (float) cos(a1);
                float y1 = (float) sin(a1);

            for (j=0; j<=phi; ++j)
            {
                double b = j * minorStep;
                float x = (float) cos(b);
                float y = r * x + R ;
                float z = r * (float) sin(b); //r * (float) sin(b)

                // Первая точка
                coords.push_back(vector3(x0*y, y0*y, z));
                coords.push_back(vector3(x1*y, y1*y, z));
            }
        }
}
