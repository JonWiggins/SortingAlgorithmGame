#include "paintsfmltexturewindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QTimer>

PaintSFMLTextureWindow::PaintSFMLTextureWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaintSFMLTextureWindow)
{
    ui->setupUi(this);
    // Size the texture
    texture.create(500, 400);
    sprite_texture.loadFromFile(":/images/Test.jpg");
    sprite_texture.setSmooth(true);
    // Create the sprite
    sprite.setTexture(sprite_texture);

    sprite.setOrigin(200,100);
    sprite.setPosition(200,200);
//    renderTexture();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PaintSFMLTextureWindow::renderTexture);
    timer->start(1);

}

void PaintSFMLTextureWindow::renderTexture() {
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

PaintSFMLTextureWindow::~PaintSFMLTextureWindow()
{
    delete ui;
}
