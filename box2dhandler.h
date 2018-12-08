/* CS 3505 A8: Educational Game
 *
 * Purpose: This class handles the backing physics engine, box2d, that is used to give the boxes onscreen a gravitational effect
 *
 *
 * @author Zak Bastiani, Alex Fritz, Conner Soule, Ryan Outtrim, Jonathan Wiggins, Will Stout, Ciaochuang Huang, and Mingqiu Zhang
 * @version 12/07/18
 */

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
    bool isMoving;

public:
    box2dhandler(std::vector<int*> boxList, int width, int height);
    ~box2dhandler();
    void updateWorld();

    //tuple: posx, posy, angle, size
    std::vector<std::tuple<int,int, float32, int>> getBoxPositions();

    //recreates the world, moving the box of the given size to the given position
    void userMove(int xPos, int yPos);


};

#endif // BOX2DHANDLER_H
