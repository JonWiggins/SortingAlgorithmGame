#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // Create a new render-texture
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    QTimer *timer;


    void renderTexture();


};

#endif // MAINWINDOW_H
