#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H
#include <QOpenGLWidget>
#include "vector3.h"
#include <vector>
#include "modeltool.h"
class LightModel: public Modeltool
{
public:

    double h;
    double r;
    int partition;
    int spot_exponent = 0; // интенсивность света
    float spot_cutoff = 180.0f; // угол разброса
    float kc = 1.0f;
    float kl = 0.0f;
    float kq = 0.0f;
    vector3 shift_direction = vector3(0,0,-1);
    int shininess = 0;
    GLenum type_edge = GL_FRONT;
    int local_viewer = GL_FALSE;
    int two_side_model = GL_FALSE;
    std::vector <vector3> coords;
    QColor ambient_color = QColor(0,0,0,255);
    QColor diffuse_color = QColor(255,255,255,255);
    QColor specular_color = QColor(255,255,255,255);
    QColor ambient_material = QColor();
    QColor diffuse_material = QColor();
    QColor specular_material = QColor(0,0,0,255);
    QColor emission_material = QColor(0,0,0,255);
    QColor global_ambient = QColor();
    GLenum model_control = GL_SINGLE_COLOR;
    LightModel(vector3 rotate = vector3(0,1,0),vector3 shift = vector3(0,0,1),vector3 scale = vector3(0.1,0.1,0.1),int angle = 90,double h = 1,double r = 0.5,int partition = 10);
    void InitLight();
    void Draw();
    void BuildCoords();
    void BuildModel();
    void LightSettings();
};

#endif // LIGHTMODEL_H
