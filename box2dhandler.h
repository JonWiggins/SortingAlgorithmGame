#ifndef BOX2DHANDLER_H
#define BOX2DHANDLER_H
#include <vector>
#include "Box2D/Box2D.h"
#include <cmath>


class box2dhandler
{
    std::vector<b2Body*> bodies;
    b2World* world;
    b2Body* grabbed;
    int width;
    int height;

public:
    box2dhandler(std::vector<int> boxList, int width, int height);
    ~box2dhandler();
    void updateWorld();

    //tuple: posx, posy, angle, size
    std::vector<std::tuple<int,int, float32, int>> getBoxPositions();

    //finds the box that is being grabbed
    void userGrab(int xPos, int yPos);

    //moves the grabbed body to the given positon
    void userMove(int xPos, int yPos);

    //sets down the box
    void userPlace();

};

#endif // BOX2DHANDLER_H
