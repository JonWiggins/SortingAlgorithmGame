#ifndef BOX2DHANDLER_H
#define BOX2DHANDLER_H
#include <vector>
#include "Box2D/Box2D.h"


class box2dhandler
{
    std::vector<b2Body*> bodies;
    b2World world;

public:
    box2dhandler(std::vector<int> boxList);
    void updateWorld();

    //tuple: posx, posy, angle, size
    std::vector<std::tuple<int,int, float32, int>> getBoxPositions();
};

#endif // BOX2DHANDLER_H
