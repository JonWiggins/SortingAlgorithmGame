#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>
#include <Box2DIncludes/Box2D/Collision/Shapes/b2Shape.h>
#include <Box2DIncludes/Box2D/Dynamics/b2Body.h>
#include <Box2D/Box2D.h>
#include "box2dhandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<int> boxes;
    boxes.push_back(50);
    boxes.push_back(30);
    world = new box2dhandler(boxes, 500, 500);

    // Size the texture
    texture.create(500, 400);
    sprite_texture.loadFromFile("/home/zachary/Desktop/a8-an-educational-app-f18-csconner1998/Test.jpg");
    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(200,100);
    sprite.setPosition(200,200);

    renderTexture();

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
