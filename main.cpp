/* CS 3505 A8: Educational Game
 *
 * Purpose: This educational game is made to teach users how sorting algorithms work
 *
 *
 * @author Zak Bastiani, Alex Fritz, Conner Soule, Ryan Outtrim, Jonathan Wiggins, Will Stout, Ciaochuang Huang, and Mingqiu Zhang
 * @version 12/07/18
 */

#include "mainwindow.h"
#include <QApplication>
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include <QtGui>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
