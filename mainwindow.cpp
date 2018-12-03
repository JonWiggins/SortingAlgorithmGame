#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>
#include <Box2DIncludes/Box2D/Collision/Shapes/b2Shape.h>
#include <Box2DIncludes/Box2D/Dynamics/b2Body.h>
#include <Box2D/Box2D.h>
#include <QDebug>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);
    // Size the texture
    texture.create(800, 500);
    sprite_texture.loadFromFile("/home/zachary/Desktop/A8/a8-an-educational-app-f18-csconner1998/Test.jpg");
    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);
    x = 200;
    y = 200;
    sprite.setOrigin(200,100);
    sprite.setPosition(x,y);


    renderTexture();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::renderTexture);
    timer->start(100);



}


void MainWindow::renderTexture() {
    // Clear the whole texture with red color
    texture.clear(sf::Color::White);

    std::vector<std::tuple<int,int, float32, int>> boxLocations = world->getBoxPositions();
    for(int counter = 0; counter < boxLocations.size(); counter++)
    {
        std::tuple<int, int, float32, int> location = boxLocations.at(counter);
        sf::RectangleShape square(sf::Vector2f(std::get<3>(location), std::get<3>(location)));
        square.setFillColor(sf::Color::Black);
        square.setPosition(std::get<0>(location),std::get<1>(location));
        square.rotate(std::get<2>(location));
        texture.draw(square);   // shape is a sf::Shape
    }

    sf::RectangleShape square(sf::Vector2f(50, 50));
    square.setFillColor(sf::Color::Black);
    square.setPosition(x,y);

    square.rotate(45);
    texture.draw(square);   // shape is a sf::Shape

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
    x = event ->x() - ui->label->x();
    y = event ->y()- ui->label->y() - 150;

}
