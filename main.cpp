#include "gamewindow.h"

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





int main(int argc, char **argv)
{
    srand(time(NULL));
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    GameWindow win120(120),win60(60),win30(30),win1(1);
    win120.setFormat(format);
    win120.resize(640, 480);
    win120.show();

    win120.setAnimating(true);
    
    win60.setFormat(format);
    win60.resize(640, 480);
    win60.show();

    win60.setAnimating(true);
    
    win30.setFormat(format);
    win30.resize(640, 480);
    win30.show();

    win30.setAnimating(true);

    win1.setFormat(format);
    win1.resize(640, 480);
    win1.show();

    win1.setAnimating(true);
    

    return app.exec();
}



