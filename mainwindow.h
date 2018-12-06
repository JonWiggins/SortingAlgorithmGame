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


private slots:
    void on_mergeButton_clicked();

    void on_insertButton_clicked();

    void on_bubbleButton_clicked();

    void on_selectButton_clicked();

    void on_Home_4_clicked();

    void on_Home_3_clicked();

    void on_Home_2_clicked();

    void on_Home_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_NextButton_clicked();

    void on_NextButton_2_clicked();

    void on_NextButton_3_clicked();

    void on_NextButton_4_clicked();

private:
    Ui::MainWindow *ui;
    // Create a new render-texture
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    std::vector<sf::RectangleShape> boxes;
    QTimer *timer;
    box2dhandler *world;
    float x;
    float y;
    void renderTexture();


};

#endif // MAINWINDOW_H
