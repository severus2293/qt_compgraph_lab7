#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QGLWidget>
#include <vector>
#include <QOpenGLShaderProgram>
#include <QTime>
#include <QOpenGLTexture>
#include "vector3.h"
#include "modeltool.h"
#include "cubemodel.h"
#include "cylindermodel.h"
#include "tormodel.h"
#include "spheremodel.h"
#include "splinemodel.h"
#include "lightmodel.h"
using namespace std;
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    vector <float> m_vertices = {-1.0,-1.0,0.0,-1.0,1.0,0.0,1.0,1.0,0.0,1.0,-1.0,0.0};
    vector <float> m_textures = {1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,};
    vector <vector3> sphere;
    float floor[12] = {1,1,0,1,-1,0,-1,-1,0,-1,1,0};
    float normal[12] = {1,1,3,1,-1,3,-1,-1,3,-1,1,3};
    float xAlpha = 70;
    float zAlpha = -30;
    int type_model;
    GLenum type_draw = GL_FILL;
    int type_axis;
    int type_light_axis;
    int type_num;
    SplineModel* splinemodel_1;
    SplineModel* splinemodel_2;
    SplineModel* splinemodel_3;
    SplineModel* splinemodel_4;
    SplineModel* splinemodel_5;
    CylinderModel* cylindermodel_1;
    CylinderModel* cylindermodel_2;
    CylinderModel* cylindermodel_3;
    CylinderModel* cylindermodel_4;
    CylinderModel* cylindermodel_5;
    LightModel* lightmodel;
    CylinderModel* axis_x;
    CylinderModel* axis_y;
    CylinderModel* axis_z;
    TorModel* tormodel;
    CubeModel* cubemodel;
    SphereModel* spheremodel;
    POINTFLOAT pos = {-3,-5};
    unsigned int type; // тип примитива
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();
    double N(int q,int k,double u);
    void clear(); //очистка холста
    void initializeGL() override;
    void paintGL() override; // отрисовка примитивов
    void resizeGL(int w, int h) override;
    void Show_floor();
    void MoveCamera();
    void Draw_cylinder(CylinderModel* objectmodel,vector<int> color);
    void Draw_tor(TorModel* objectmodel,vector<int> color);
    void Draw_sphere(SphereModel* objectmodel,vector<int> color);
    void Draw_cube(CubeModel* objectmodel,vector<int> color);
    void Draw_spline(SplineModel* objectmodel,vector<int> color);
    void drawModels();

    HDC hDC;
private:
    QTimer timer;
protected:
    void mousePressEvent(QMouseEvent * event) override; // эвент нажатия мыши по холсту
};

#endif // GLWIDGET_H
