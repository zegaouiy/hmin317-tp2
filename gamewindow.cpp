#include "gamewindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QTimer>
#include <QtCore/qmath.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <time.h>
#include <sys/time.h>
#include <iostream>

#include <QtCore>
#include <QtGui>
using namespace std;


GameWindow::GameWindow(int fps)
{
  cam = new Camera();
  QTimer *timer = new QTimer(this);
  QTimer *rotat = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(renderNow()));
  timer->start(1000/fps);
  connect(rotat,SIGNAL(timeout()),this,SLOT(rotate_scene()));
  rotat->start(5);
}

GameWindow::~GameWindow()
{
  delete cam;
}

void GameWindow::turn_pause()
{
  pause = !pause;
}

void GameWindow::rotate_scene()
{
  if(!pause)
    {
      cam->set_y(1);
      cam->set_x(1);
    }
}

void GameWindow::initialize()
{
  const qreal retinaScale = devicePixelRatio();


  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);

  loadMap(":/heightmap-2.png");
}

void GameWindow::loadMap(QString localPath)
{

  if (QFile::exists(localPath)) {
    m_image = QImage(localPath);
  }


  uint id = 0;
  p = new point[m_image.width() * m_image.height()];
  QRgb pixel;
  for(int i = 0; i < m_image.width(); i++)
    {
      for(int j = 0; j < m_image.height(); j++)
        {

	  pixel = m_image.pixel(i,j);

	  id = i*m_image.width() +j;

	  p[id].x = (float)i/(m_image.width()) - ((float)m_image.width()/2.0)/m_image.width();
	  p[id].y = (float)j/(m_image.height()) - ((float)m_image.height()/2.0)/m_image.height();
	  p[id].z = 0.001f * (float)(qRed(pixel));
        }
    }
}

void GameWindow::render()
{
  cam->render_cam();

  glClear(GL_COLOR_BUFFER_BIT);

  switch(cam->get_etat())
    {
    case 0:
      displayPoints();
      break;
    case 1:
      displayLines();
      break;
    case 2:
      displayTriangles();
      break;
    case 3:
      displayTrianglesC();
      break;
    case 4:
      displayTrianglesTexture();
      break;
    case 5:

      displayTrianglesTexture();
      displayLines();
      break;
    default:
      displayPoints();
      break;
    }

  ++m_frame;
}

bool GameWindow::event(QEvent *event)
{
  switch (event->type())
    {
    case QEvent::UpdateRequest:

      renderNow();
      return true;
    default:
      return QWindow::event(event);
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
  switch(event->key())
    {
    case 'Z':
      cam->set_ss(1);
      break;
    case 'S':
      cam->set_ss(-1);
      break;
    case 'A':
      cam->set_x(1);
      break;
    case 'E':
      cam->set_x(-1);
      break;
    case 'Q':
      cam->set_y(1);
      break;
    case 'D':
      cam->set_y(-1);
      break;
    case 'W':
      cam->set_etat();
      break;
    case 'C' :
      turn_pause();
      break;
    case 'X':
      carte ++;
      if(carte > 3)
	carte = 1;
      QString depth (":/heightmap-");
      depth += QString::number(carte) ;
      depth += ".png" ;
      
      loadMap(depth);
      break;
    }
  // renderNow();
}


void GameWindow::displayPoints()
{
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_POINTS);
  uint id = 0;
  for(int i = 0; i < m_image.width(); i++)
    {
      for(int j = 0; j < m_image.height(); j++)
        {
	  id = i*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);

        }
    }
  glEnd();
}


void GameWindow::displayTriangles()
{
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  uint id = 0;

  for(int i = 0; i < m_image.width()-1; i++)
    {
      for(int j = 0; j < m_image.height()-1; j++)
        {

	  id = i*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = i*m_image.width() +(j+1);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);



	  id = i*m_image.width() +(j+1);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j+1;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
        }
    }

  glEnd();
}

void GameWindow::displayTrianglesC()
{
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  uint id = 0;

  for(int i = 0; i < m_image.width()-1; i++)
    {
      for(int j = 0; j < m_image.height()-1; j++)
        {
	  glColor3f(0.0f, 1.0f, 0.0f);
	  id = i*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = i*m_image.width() +(j+1);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);


	  glColor3f(1.0f, 1.0f, 1.0f);
	  id = i*m_image.width() +(j+1);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j+1;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
        }
    }
  glEnd();
}


void GameWindow::displayLines()
{
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  uint id = 0;

  for(int i = 0; i < m_image.width()-1; i++)
    {
      for(int j = 0; j < m_image.height()-1; j++)
        {

	  id = i*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = i*m_image.width() +(j+1);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);

	  id = (i+1)*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = i*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);

	  id = (i+1)*m_image.width() +j;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = i*m_image.width() +(j+1);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);

	  id = i*m_image.width() +(j+1);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j+1;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);

	  id = (i+1)*m_image.width() +j+1;
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);

	  id = (i+1)*m_image.width() +(j);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
        }
    }

  glEnd();
}

void GameWindow::displayTrianglesTexture()
{
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  uint id = 0;

  for(int i = 0; i < m_image.width()-1; i++)
    {
      for(int j = 0; j < m_image.height()-1; j++)
        {

	  id = i*m_image.width() +j;
	  displayColor(p[id].z);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = i*m_image.width() +(j+1);
	  displayColor(p[id].z);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j;
	  displayColor(p[id].z);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);



	  id = i*m_image.width() +(j+1);
	  displayColor(p[id].z);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j+1;
	  displayColor(p[id].z);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
	  id = (i+1)*m_image.width() +j;
	  displayColor(p[id].z);
	  glVertex3f(
		     p[id].x,
		     p[id].y,
		     p[id].z);
        }
    }
  glEnd();
}


void GameWindow::displayColor(float alt)
{
  if (alt > 0.2)
    {
      glColor3f(01.0f, 1.0f, 1.0f);
    }
  else     if (alt > 0.1)
    {
      glColor3f(alt, 1.0f, 1.0f);
    }
  else     if (alt > 0.05f)
    {
      glColor3f(01.0f, alt, alt);
    }
  else
    {
      glColor3f(0.0f, 0.0f, 1.0f);
    }

}
