#ifndef BOX2DHANDLER_H
#define BOX2DHANDLER_H
#include <vector>
#include "Box2D/Box2D.h"
#include <cmath>


class box2dhandler
{
    std::vector<b2Body*> bodies;
    b2World* world;
    int width;
    int height;

public:
    box2dhandler(std::vector<int> boxList, int width, int height);
    ~box2dhandler();
    void updateWorld();

    //tuple: posx, posy, angle, size
    std::vector<std::tuple<int,int, float32, int>> getBoxPositions();

    //recreates the world, moving the box of the given size to the given position
    void userMove(int boxSize,int xPos, int yPos);


};

#endif // BOX2DHANDLER_H
