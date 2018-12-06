#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>
#include <Box2DIncludes/Box2D/Collision/Shapes/b2Shape.h>
#include <Box2DIncludes/Box2D/Dynamics/b2Body.h>
#include <Box2D/Box2D.h>
#include <QDebug>
#include <QMouseEvent>
#include <iostream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);

    // Size the texture
    texture.create(800, 500);

    //Copy Test.jpg from the project folder into the build folder
    sprite_texture.loadFromFile("Test.jpg");

    //create array elements and give them to boxmaker
    std::vector<int> elements;
    elements.push_back(50);
    elements.push_back(60);
    elements.push_back(70);
    createAndDisplayBoxes(elements);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::renderTexture);

    //16 millis means 60fps
    timer->start(16);

    progressValue = 0;
}

void MainWindow::createAndDisplayBoxes(std::vector<int> elements)
{
    int biggestBoxSize = 0;
    for(int element : elements)
    {
        if(element > biggestBoxSize)
        {
            biggestBoxSize = element;
        }
    }

    //draw each box, with the size of the biggest box + 60
    int paddingsize = biggestBoxSize + 60;

    int currentPos = 100;

    std::vector<int*> boxInfo;


    for(int element : elements)
    {
        int* toAdd = new int[3]{element, currentPos, 250};
        currentPos += paddingsize + element;
        boxInfo.push_back(toAdd);

    }

    this->world = new box2dhandler(boxInfo, 800, 500);

}

void MainWindow::renderTexture() {
    // Clear the whole texture with red color
    texture.clear(sf::Color::White);
    auto position = world->getBoxPositions();

    this->world->updateWorld();

    std::vector<std::tuple<int,int, float32, int>> boxLocations = world->getBoxPositions();
    for(int counter = 0; counter < boxLocations.size(); counter++)
    {
        std::tuple<int, int, float32, int> location = boxLocations.at(counter);
        sf::RectangleShape square(sf::Vector2f(std::get<3>(location), std::get<3>(location)));
        square.setFillColor(sf::Color::Black);
        square.setPosition(std::get<0>(location), 500 - (std::get<1>(location) + std::get<3>(location)));
        square.rotate(std::get<2>(location));

        texture.draw(square);   // shape is a sf::Shape

        square.setPosition(x,y);
    }

    texture.display();

    // Set to a QImage
    QImage qi(texture.getTexture().copyToImage().getPixelsPtr(), 800,500, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

       ui->label->setPixmap(QPixmap::fromImage(qi));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    float tempX = event ->x() - ui->label->x();
    float tempY = event ->y() - ui->label->y();

    world->userMove(0, tempX, 500 - tempY);

}

std::vector<int> MainWindow::getBoxOrderVector(){
    std::vector<int> toReturn;

    std::vector<std::tuple<int,int, float32, int>> boxLocations = world->getBoxPositions();

    std::vector<int> xPositions;
    for(auto box : boxLocations)
        xPositions.push_back(std::get<0>(box));

    //this sort happens inscope so it does not effect anything else
    std::sort(xPositions.begin(), xPositions.end());

    for(int xPos : xPositions){
        //find the associated box and add it to the toReturn vector
        for(auto box : boxLocations){
            if(std::get<0>(box) == xPos)
                toReturn.push_back(std::get<3>(box));
        }
    }

    return toReturn;
}



void MainWindow::on_mergeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_insertButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_bubbleButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_selectButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_Home_4_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Home_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Home_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Home_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_CheckButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
     ui->mergeButton->setStyleSheet("background-color: rgb(0, 255, 0);");
     progressValue += 25;
     ui->progressBar->setValue(progressValue);
}

void MainWindow::on_CheckButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
     ui->insertButton->setStyleSheet("background-color: rgb(0, 255, 0);");
     progressValue += 25;
     ui->progressBar->setValue(progressValue);
}

void MainWindow::on_CheckButton_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
     ui->bubbleButton->setStyleSheet("background-color: rgb(0, 255, 0);");
     progressValue += 25;
     ui->progressBar->setValue(progressValue);
}

void MainWindow::on_CheckButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
     ui->selectButton->setStyleSheet("background-color: rgb(0, 255, 0);");
     progressValue += 25;
     ui->progressBar->setValue(progressValue);
}

void MainWindow::on_NextButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_NextButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_NextButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_NextButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}
