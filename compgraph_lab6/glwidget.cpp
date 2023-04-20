#include "glwidget.h"
#include <QTextStream>
#include <QMouseEvent>
#include <cmath>
#include <QLabel>
GLWidget::GLWidget(QWidget * parent):QGLWidget(parent) // инициализируем базовые параметры
{
    this->cylindermodel_1 = new CylinderModel();
    this->cylindermodel_2 =  new CylinderModel(vector3(0,1,0),vector3(-2,0,-2),vector3(1,1,1),90);
    this->cylindermodel_3 =  new CylinderModel(vector3(0,1,0),vector3(0,-0.7,-1),vector3(1,1,1),30,0.3,0.2);
    this->cylindermodel_4 =  new CylinderModel(vector3(0,1,0),vector3(-0.3,0,-1.7),vector3(1,1,1),125,0.3,0.2);
    this->cylindermodel_5 =  new CylinderModel(vector3(1,0,0),vector3(2,1,0),vector3(1,1,1),60,0.5,0.2);
    this->splinemodel_1 = new SplineModel(vector3(1,0,0),vector3(2,0,0),vector3(1,1,1),0,720,0.1,20);
    this->splinemodel_2 = new SplineModel(vector3(0,1,0),vector3(0,2,0),vector3(1,1,1),220,720,0.15,20);
    this->splinemodel_3 = new SplineModel(vector3(0,1,0),vector3(1.4,1,-1.3),vector3(1,1,1),310,720,0.15,20);
    this->splinemodel_4 = new SplineModel(vector3(0,1,0),vector3(1,3.2,0),vector3(1,1,1),105,720,0.1,20);
    this->splinemodel_5 = new SplineModel(vector3(0,1,0),vector3(0,2,3),vector3(1,1,1),0,720,0.1,20);
    this->tormodel = new TorModel(vector3(0,1,1),vector3(2.2,0.4,2),vector3(1,1,1),340);
    this->cubemodel =  new CubeModel(vector3(0,1,0),vector3(1.0,-0.5,-1),vector3(1,1,1),217);
    this->spheremodel =  new SphereModel(vector3(1,0,0),vector3(0,-1.0,1.5));
    this->lightmodel =  new LightModel();
    this->axis_x = new CylinderModel(vector3(1,0,0),vector3(0,0,0),vector3(1,1,1),90,10.0,0.01,36);
    this->axis_y = new CylinderModel(vector3(0,1,0),vector3(0,0,0),vector3(1,1,1),90,10.0,0.01,36);
    this->axis_z = new CylinderModel(vector3(0,0,1),vector3(0,0,0),vector3(1,1,1),90,10.0,0.01,36);
    this->type_model = 0;
    this->type_num = 1;
     this->type_axis = 0;
    this->type_light_axis = 0;
    this->type = GL_POINTS;
connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
timer.start(100);
}


void GLWidget::clear() //очистить холст
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->paintGL();
}

GLWidget::~GLWidget()
{
    delete tormodel;
    delete cylindermodel_1;
    delete cylindermodel_2;
    delete cylindermodel_3;
    delete cylindermodel_4;
    delete cylindermodel_5;
    delete splinemodel_1;
    delete splinemodel_2;
    delete splinemodel_3;
    delete splinemodel_4;
    delete splinemodel_5;
    delete cubemodel;
    delete spheremodel;
    delete lightmodel;
}

void GLWidget::initializeGL() //задать базовый цвет для холста
{

    glClearColor(0.2,0.2,0.2,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    lightmodel->InitLight();
    glEnable(GL_COLOR_MATERIAL);
    float position[] = {0,0,1,0};
   // glLightfv(GL_LIGHT0,GL_POSITION,position);
}











void GLWidget::mousePressEvent(QMouseEvent * event) //событие нажатия на холст для отрисовки точки
{

        // границы окна OpenGL
        double x0 = -1.3;
        double y0 =  1.0;
        double x1 =  1.3;
        double y1 = -1.0;

        // переводим координаты окна в координаты окна OpenGL
        double xAtPress = double(event->x()) / this->geometry().size().width() * (x1 - x0) + x0;
        double yAtPress = double(event->y()) / this->geometry().size().height() * (y1 - y0) + y0;
        QTextStream out(stdout);

    out << xAtPress << endl;
    out << yAtPress  << endl;

}







void GLWidget::MoveCamera(){
    if(GetKeyState(VK_UP) < 0) xAlpha = ++xAlpha > 180 ? 180 : xAlpha;
    if(GetKeyState(VK_DOWN) < 0) xAlpha = --xAlpha < 0 ? 0 : xAlpha;
    if(GetKeyState(VK_LEFT) < 0) zAlpha++;
    if(GetKeyState(VK_RIGHT) < 0) zAlpha--;
    float angle = -zAlpha / 180*M_PI;
    float speed = 0;
    if(GetKeyState('W') < 0) speed = 0.2;
    if(GetKeyState('S') < 0) speed = -0.2;
    if(GetKeyState('A') < 0) {speed = 0.2; angle -= M_PI *0.5;}
    if(GetKeyState('D') < 0) {speed = 0.2; angle += M_PI *0.5;}
    if (speed != 0){
        pos.x += sin(angle) * speed;
        pos.y += cos(angle) * speed;
    }

    glLoadIdentity();
    glFrustum(-1,1,-1,1,2,80);
   // glOrtho(-1,1,-1,1,-1,1);
    glRotatef(-xAlpha,1,0,0);
    glRotatef(-zAlpha,0,0,1);
    glTranslatef(-pos.x,-pos.y,-3);
}

void GLWidget::Show_floor(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
      glNormal3f(0,0,1);
     glVertexPointer(3,GL_FLOAT,0,&floor);
     glNormalPointer(GL_FLOAT,0,&normal);
     for(int i = -5; i< 5;i++){
         for(int j = -5;j<5;j++){
             glPushMatrix();
             if((i+j) % 2 == 0) glColor3f(0,0,0);
             else glColor3f(1,1,1);
             glTranslatef(i*2,j*2,0);
             glDrawArrays(GL_TRIANGLE_FAN,0,4);
             glPopMatrix();
         }
     }
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::Draw_cube(CubeModel* objectmodel,vector<int> color){
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRotatef(objectmodel->angle,objectmodel->rotate.x,objectmodel->rotate.y,objectmodel->rotate.z);
    glTranslatef(objectmodel->shift.x,objectmodel->shift.y,objectmodel->shift.z);
    glScalef(objectmodel->scale.x,objectmodel->scale.y,objectmodel->scale.z);
    //первая окружность
    glColor3ub(color[0],color[1],color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,1.0);
    for (int i = 0;i < objectmodel->coords.size();i++) {
        glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,objectmodel->coords[i].z);
        glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z);
     }
    glVertex3d(objectmodel->coords[0].x, objectmodel->coords[0].y, objectmodel->coords[0].z);
    glEnd();
    //вторая окружность
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,1.0 + objectmodel->a);
    for (int i = 0;i < objectmodel->coords.size();i++) {
        glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,objectmodel->coords[i].z + objectmodel->a);
        glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z + objectmodel->a);
     }
    glNormal3f(objectmodel->coords[0].x,objectmodel->coords[0].y,objectmodel->coords[0].z + objectmodel->a);
    glVertex3d(objectmodel->coords[0].x,objectmodel->coords[0].y, objectmodel->coords[0].z + objectmodel->a);
    glEnd();
    //соединить
    glBegin(GL_TRIANGLE_STRIP);
    //glVertex3f(0,0,1.5);
    for (int i = 0;i < objectmodel->coords.size();i++) {
        glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,0);
        glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z);
        glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,objectmodel->coords[i].z + objectmodel->a);
        glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y,objectmodel->coords[i].z + objectmodel->a);
     }
    glNormal3f(objectmodel->coords[0].x,objectmodel->coords[0].y,objectmodel->coords[0].z);
    glVertex3d(objectmodel->coords[0].x, objectmodel->coords[0].y, objectmodel->coords[0].z);
    glNormal3f(objectmodel->coords[0].x,objectmodel->coords[0].y,objectmodel->coords[0].z + objectmodel->a);
    glVertex3d(objectmodel->coords[0].x, objectmodel->coords[0].y, objectmodel->coords[0].z + objectmodel->a);
    glEnd();
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLWidget::Draw_cylinder(CylinderModel* objectmodel,vector<int> color){
    glPushMatrix();
    glRotatef(objectmodel->angle,objectmodel->rotate.x,objectmodel->rotate.y,objectmodel->rotate.z);
    glTranslatef(objectmodel->shift.x,objectmodel->shift.y,objectmodel->shift.z);
    glScalef(objectmodel->scale.x,objectmodel->scale.y,objectmodel->scale.z);

    //первая окружность
    glColor3ub(color[0],color[1],color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,1.0);
    for (int i = 0;i < objectmodel->coords.size();i++) {
        glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,0);
        glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z);
     }
    glNormal3f(objectmodel->coords[0].x,objectmodel->coords[0].y,0);
    glVertex3d(objectmodel->coords[0].x, objectmodel->coords[0].y, objectmodel->coords[0].z);
    glEnd();
    //вторая окружность
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,1.0 + objectmodel->h);
    for (int i = 0;i < objectmodel->coords.size();i++) {
        glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,0 + objectmodel->h);
        glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z + objectmodel->h);
     }
    glNormal3f(objectmodel->coords[0].x,objectmodel->coords[0].y,0 + objectmodel->h);
    glVertex3d(objectmodel->coords[0].x, objectmodel->coords[0].y, objectmodel->coords[0].z + objectmodel->h);
    glEnd();
    //соединить
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0;i < objectmodel->coords.size();i++) {
        glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,0);
        glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z);
        glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,0 + objectmodel->h);
        glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z + objectmodel->h);
     }
     glNormal3f(objectmodel->coords[0].x,objectmodel->coords[0].y,0);
    glVertex3d(objectmodel->coords[0].x, objectmodel->coords[0].y,objectmodel->coords[0].z);
     glNormal3f(objectmodel->coords[0].x,objectmodel->coords[0].y,0 + objectmodel->h);
    glVertex3d(objectmodel->coords[0].x, objectmodel->coords[0].y, objectmodel->coords[0].z + objectmodel->h);
    glEnd();
    glPopMatrix();
}

void GLWidget::Draw_tor(TorModel* objectmodel,vector<int> color){

        glPushMatrix();
        glRotatef(objectmodel->angle,objectmodel->rotate.x,objectmodel->rotate.y,objectmodel->rotate.z);
        glTranslatef(objectmodel->shift.x,objectmodel->shift.y,objectmodel->shift.z);
        glScalef(objectmodel->scale.x,objectmodel->scale.y,objectmodel->scale.z);
        glColor3ub(color[0],color[1],color[2]);
        glBegin(GL_TRIANGLE_STRIP);

        for (int i = 0;i < objectmodel->coords.size();i++) {
            glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,objectmodel->coords[i].z);
            glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z);
         }
        glEnd();
        glPopMatrix();
}

void GLWidget::Draw_spline(SplineModel* objectmodel,vector<int> color){
        //нарисуем спираль
        glPushMatrix();
        glRotatef(objectmodel->angle,objectmodel->rotate.x,objectmodel->rotate.y,objectmodel->rotate.z);
        glTranslatef(objectmodel->shift.x,objectmodel->shift.y,objectmodel->shift.z);
        glScalef(objectmodel->scale.x,objectmodel->scale.y,objectmodel->scale.z);
        glRotatef(90,0,1,0);
        glColor3ub(color[0],color[1],color[2]);
        glBegin(GL_TRIANGLE_STRIP);

        for (int i = 0;i < objectmodel->coords.size();i++) {
            glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,objectmodel->coords[i].z);
            glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z);
            double p;
             double step =  360 / objectmodel->partition;
            for(int j = 0;j < objectmodel->partition; j++){
                p = step * j * 3.14 / 180;
                glNormal3f(objectmodel->coords[i].x + objectmodel->r * sin(p),objectmodel->coords[i].y +  objectmodel->r * cos(p),objectmodel->coords[i].z);
                glVertex3d(objectmodel->coords[i].x + objectmodel->r * sin(p) , objectmodel->coords[i].y +  objectmodel->r * cos(p), objectmodel->coords[i].z);
            }
         }
        glEnd();
        glPopMatrix();


}


void GLWidget::Draw_sphere(SphereModel* objectmodel,vector<int> color)
{
     glPushMatrix();
     glRotatef(objectmodel->angle,objectmodel->rotate.x,objectmodel->rotate.y,objectmodel->rotate.z);
     glTranslatef(objectmodel->shift.x,objectmodel->shift.y,objectmodel->shift.z);
     glScalef(objectmodel->scale.x,objectmodel->scale.y,objectmodel->scale.z);
     glColor3ub(color[0],color[1],color[2]);
     glBegin(GL_TRIANGLE_STRIP);

     for (int i = 0;i < objectmodel->coords.size();i++) {
         glNormal3f(objectmodel->coords[i].x,objectmodel->coords[i].y,objectmodel->coords[i].z);
         glVertex3d(objectmodel->coords[i].x, objectmodel->coords[i].y, objectmodel->coords[i].z);
      }
     glEnd();
     glPopMatrix();
}

void GLWidget::drawModels(){
    vector<int> color = {184,134,11};
    Draw_cylinder(cylindermodel_1,color);
    Draw_cylinder(cylindermodel_2,color); //крест из золотых
    Draw_cylinder(cylindermodel_3,color);
    Draw_spline(splinemodel_2,color);
    Draw_spline(splinemodel_3,color);
    color = {209,0,49};
    Draw_cylinder(cylindermodel_4,color);
    Draw_tor(tormodel,color);
    Draw_spline(splinemodel_1,color);
    color = {166,83,23};
    Draw_spline(splinemodel_4,color);
    Draw_sphere(spheremodel,color);
    color = {148,0,211};
    Draw_cylinder(cylindermodel_5,color);
    Draw_spline(splinemodel_5,color);
    Draw_cube(cubemodel,color);
    Draw_spline(splinemodel_1,color);
    color = {255,0,0};
    Draw_cylinder(axis_x,color);
    color = {0,255,0};
    Draw_cylinder(axis_y,color);
    color = {0,0,255};
    Draw_cylinder(axis_z,color);
}


void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // очистка буфера
    glPushMatrix();
    //glNormal3f(0,0,1);
    glPolygonMode(GL_FRONT_AND_BACK, type_draw);
    MoveCamera();
    Show_floor();
    lightmodel->Draw();
    drawModels();
     glPopMatrix();
    Sleep(1);


}

void GLWidget::resizeGL(int w, int h)
{
   glViewport(0,0,w,h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   updateGL();
}
