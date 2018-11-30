#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>
#include <Box2DIncludes/Box2D/Collision/Shapes/b2Shape.h>
#include <Box2DIncludes/Box2D/Dynamics/b2Body.h>
#include <Box2D/Box2D.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Size the texture
    texture.create(500, 400);
    sprite_texture.loadFromFile("/home/zachary/Desktop/a8-an-educational-app-f18-csconner1998/Test.jpg");
    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(200,100);
    sprite.setPosition(200,200);

    renderTexture();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::renderTexture);
    timer->start(100);



}


void MainWindow::renderTexture() {
    // Clear the whole texture with red color
    texture.clear(sf::Color::White);

    sf::RectangleShape square(sf::Vector2f(50, 50));
    square.setFillColor(sf::Color::Black);
    square.setPosition(300,300);
    square.rotate(45);
    texture.draw(square);   // shape is a sf::Shape

    texture.display();

    // Set to a QImage
    QImage qi(texture.getTexture().copyToImage().getPixelsPtr(), 500, 400, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();

       ui->label->setPixmap(QPixmap::fromImage(qi));
}

MainWindow::~MainWindow()
{
    delete ui;
}
