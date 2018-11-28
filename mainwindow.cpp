#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>
#include <Box2DIncludes/Box2D/Collision/Shapes/b2Shape.h>
#include <Box2DIncludes/Box2D/Dynamics/b2Body.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Size the texture
    texture.create(500, 400);
    //sprite_texture.loadFromFile("/home/conner/Desktop/a8-an-educational-app-f18-csconner1998/Test.jpg");
    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(200,100);
    sprite.setPosition(200,200);
//    renderTexture();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::renderTexture);
    timer->start(1);

    //b2BodyDef myBodyDef;
    //myBodyDef.type = b2_dynamicBody;
    //myBodyDef.position.Set(20,20);
    //myBodyDef.angle = 45;

    //b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

    //b2PolygonShape boxShape;
    //boxShape.SetAsBox(1,1);
    //b2FixtureDef boxFixtureDef;
    //boxFixtureDef.shape = &boxShape;
    //boxFixtureDef.density = 1;
    //dynamicBody->SetTransform(b2Vec2 (20, 20), 45);
    //dynamicBody->SetAngularVelocity(90);


}


void MainWindow::renderTexture() {
    // Clear the whole texture with red color
    texture.clear(sf::Color::Red);
    sprite.rotate(1.0);
    // Draw stuff to the texture
    texture.draw(sprite);  // sprite is a sf::Sprite
//    texture.draw(shape);   // shape is a sf::Shape
//    texture.draw(text);    // text is a sf::Text
    // We're done drawing to the texture
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
