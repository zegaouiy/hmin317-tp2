#include "camera.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <time.h>
#include <sys/time.h>
#include <iostream>

#include <QtCore>
#include <QtGui>
using namespace std;


Camera::Camera()
{
  etat = 0;
  rot_x = -45.0;
  rot_y = -45.0;
  ss = 1.0f;
}
  
void Camera::render_cam()
{
  glLoadIdentity();
  glScalef(ss,ss,ss);
  glRotatef(rot_x,1.0f,0.0f,0.0f);
  glRotatef(rot_y,0.0f,0.0f,1.0f);

  
}


void Camera::set_etat()
{
  ++etat %= 6;
}

void Camera::set_x(int s)
{
  rot_x += s*1.0f;
}

void Camera::set_y(int s)
{
  rot_y += s*1.0f;
}
  
void Camera::set_ss(int s)
{
  ss += s*0.10f;
}

int Camera::get_etat()
{
  return etat;
}
