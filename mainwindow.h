#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "box2dhandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    // Create a new render-texture
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    QTimer *timer;
    box2dhandler *world;
    float x;
    float y;
    void renderTexture();


};

#endif // MAINWINDOW_H
