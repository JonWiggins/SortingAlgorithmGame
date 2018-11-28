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
