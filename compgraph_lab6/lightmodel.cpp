#include "lightmodel.h"
#include <cmath>


LightModel::LightModel(vector3 rotate, vector3 shift, vector3 scale, int angle, double h, double r, int partition): Modeltool(rotate,shift,scale,angle)
{
    this->h = h;
    this->r = r;
    this->partition = partition;
    BuildCoords();
}

void LightModel::InitLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
   // glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,45.0);// угол пропускания - 45
    //glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,4.0);// значение Е
    BuildCoords();
    ambient_material.setRgbF(0.2,0.2,0.2,1.0);
    diffuse_material.setRgbF(0.8,0.8,0.8,1.0);
    global_ambient.setRgbF(0.2,0.2,0.2,1.0);
}

void LightModel::BuildCoords(){
    coords.clear();
    double step =  360 / partition;
    double p;
    for (int i = 0;i < partition;i++) {
        p = step * i * 3.14 / 180;

        coords.push_back(vector3(r * sin(p),r * cos(p),1.0));
    }
}

void LightModel::LightSettings(){
    float position[] = {(float)shift.x,(float)shift.y,(float)shift.z,0.0};
    float ambient_color_arr[] = {(float)ambient_color.redF(),(float)ambient_color.greenF(),(float)ambient_color.blueF(),1.0};
    float diffuse_color_arr[] = {(float)diffuse_color.redF(),(float)diffuse_color.greenF(),(float)diffuse_color.blueF(),1.0};
    float specular_color_arr[] = {(float)specular_color.redF(),(float)specular_color.greenF(),(float)specular_color.blueF(),1.0};
    float ambient_material_arr[] = {(float)ambient_material.redF(),(float)ambient_material.greenF(),(float)ambient_material.blueF(),1.0};
    float ambient_global_arr[] = {(float)global_ambient.redF(),(float)global_ambient.greenF(),(float)global_ambient.blueF(),1.0};
    float diffuse_material_arr[] = {(float)diffuse_material.redF(),(float)diffuse_material.greenF(),(float)diffuse_material.blueF(),1.0};
    float specular_material_arr[] = {(float)specular_material.redF(),(float)specular_material.greenF(),(float)specular_material.blueF(),1.0};
    float specular_emission_arr[] = {(float)emission_material.redF(),(float)emission_material.greenF(),(float)emission_material.blueF(),1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    GLfloat dir[]={(float) shift_direction.x,(float)shift_direction.y,(float)shift_direction.z,0.0};// направление прожектора
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dir);
    glLighti(GL_LIGHT0,GL_SPOT_EXPONENT,spot_exponent); // задаём интенсивность света
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,spot_cutoff); // задаём угол разброса
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_color_arr); // задаём цвет фонового освещения
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_color_arr); // задаём цвет диффузного освещения
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular_color_arr); // задаём цвет зеркального отражения
    glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,kc);  // постоянный коэффициент затухания
    glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,kl);  // линейный коэффициент затухания
    glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,kq); // квадратичный коэффициент затухания
    glMaterialfv(type_edge,GL_AMBIENT,ambient_material_arr); // рассеяный цвет материала
    glMaterialfv(type_edge,GL_DIFFUSE,diffuse_material_arr); // диффузное отражение материала
    glMaterialfv(type_edge,GL_SPECULAR,specular_material_arr); // зеркальное отражение материала
    glMaterialf(type_edge,GL_SHININESS,shininess); // степень зеркального отражения
   glMaterialfv(type_edge,GL_EMISSION,specular_emission_arr); // интенсивность излучаемого света материала
   glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,local_viewer); // локальная или удалённая точка наблюдения
   glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,two_side_model); // закрашивание обоих сторон
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_global_arr); // глобальный фоновый цвет
   glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,model_control); // отделение зеркальной составляющей

}
void LightModel::BuildModel(){
    glPushMatrix();
    glRotatef(angle,rotate.x,rotate.y,rotate.z);
    glTranslatef(shift.x,shift.y,shift.z);
    glScalef(scale.x,scale.y,scale.z);
    LightSettings();
    //первая окружность
    glColor3f(0,0,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,1.0);
    for (int i = 0;i < coords.size();i++) {
        glVertex3d(coords[i].x, coords[i].y, coords[i].z);
     }
    glVertex3d(coords[0].x,coords[0].y, coords[0].z);
    glEnd();
    //вторая окружность
    double  coef = (r + 1)/r;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,1.0 + h);
    for (int i = 0;i < coords.size();i++) {
        glVertex3d(coords[i].x *coef, coords[i].y*coef, coords[i].z*coef + h);
     }
    glVertex3d(coords[0].x*coef,coords[0].y*coef, coords[0].z*coef + h);
    glEnd();
    //соединить
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0;i < coords.size();i++) {
        glVertex3d(coords[i].x, coords[i].y, coords[i].z);
        glVertex3d(coords[i].x*coef, coords[i].y*coef, coords[i].z*coef +h);
     }
    glVertex3d(coords[0].x, coords[0].y,coords[0].z);
    glVertex3d(coords[0].x*coef, coords[0].y* coef, coords[0].z*coef + h);
    glEnd();
    glPopMatrix();
}


void LightModel::Draw()
{

    glPushMatrix();

    //glTranslatef(0,0,1);
   // glScalef(0.1,0.1,0.1);
    BuildModel();


    glPopMatrix();
}
