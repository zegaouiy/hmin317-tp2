#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "openglwindow.h"
#include "camera.h"

struct point
{
    float x, y ,z;
};



class GameWindow : public OpenGLWindow
{
  Q_OBJECT
public:
    GameWindow(int fps);
    ~GameWindow();

    void initialize();
    void render();
    bool event(QEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void displayTriangles();
    void displayLines();
    void displayTrianglesC();
    void displayPoints();
    void displayTrianglesTexture();

    void displayColor(float);

    void turn_pause();

    void loadMap(QString localPath);
    
    public slots :    
    void rotate_scene();
private:
    Camera* cam;
    
    int m_frame;
    QImage m_image;
    point *p;
    short pause = 1;

    int carte=1;


};


#endif // GAMEWINDOW_H
