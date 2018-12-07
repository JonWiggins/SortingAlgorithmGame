/* CS 3505 A8: Educational Game
 *
 * Purpose: This Qt window acts as the central hub for the game.
 *  It controls all of the user interactions and displays all the information to the user.
 *  It also handles interfacing with the SFML library as well as use of the box2dhandler
 *
 * @author Zak Bastiani, Alex Fritz, Conner Soule, Ryan Outtrim, Jonathan Wiggins, Will Stout, Ciaochuang Huang, and Mingqiu Zhang
 * @version 12/07/18
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "box2dhandler.h"
#include "sorts.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int currentSort;
    int currentIteration;
    std::vector<int> originState;
    int incorrectCounter;

public:
    explicit MainWindow(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
    bool checkVector(std::vector<int> originalOrder, int currentStep);
    std::vector<int> getBoxOrderVector();
    void createAndDisplayBoxes(std::vector<int> elements);
    std::vector<int> randomVector(int length, int maxSize, int minSize);
    ~MainWindow();


private slots:
    void on_mergeButton_clicked();

    void on_insertButton_clicked();

    void on_bubbleButton_clicked();

    void on_selectButton_clicked();

    void on_CheckButton_clicked();

    void on_NextButton_clicked();

    void on_Home_clicked();

    void on_actionGame_Information_triggered();

    void on_pushButton_clicked();

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
    int progressValue;
    int sortType;
    bool sortsCompleted[4];
    QFont font;
};

#endif // MAINWINDOW_H
