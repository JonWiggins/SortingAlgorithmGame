/* CS 3505 A8: Educational Game
 *
 * Purpose: This class handles the backing physics engine, box2d, that is used to give the boxes onscreen a gravitational effect
 *
 *
 * @author Zak Bastiani, Alex Fritz, Conner Soule, Ryan Outtrim, Jonathan Wiggins, Will Stout, Ciaochuang Huang, and Mingqiu Zhang
 * @version 12/07/18
 */

#include "box2dhandler.h"
#include <iostream>

/*
 * Create a new Box2d world wherein there are boxes for each of the given vector elements
 *  Each box is a square with the sides being the length specified by the int
 *  The world is defined by the given width and height
*/
box2dhandler::box2dhandler(std::vector<int*> boxList, int width, int height)
{
    this->width = width;
    this->height = height;

    //define box2d world
    b2Vec2 gravity(0.0f, -10.0f);
    this->world = new b2World(gravity);

    //define ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);

    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(width, 50);

    groundBody->CreateFixture(&groundBox, 0.0f);

    //define dynamic boxes
    for(auto box: boxList)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;

        bodyDef.position.Set(box[1], box[2]);


        b2Body* body = world->CreateBody(&bodyDef); //Add these to vector

        b2PolygonShape dynamicBox;

        //value defines the size
        dynamicBox.SetAsBox(box[0], box[0]);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
        bodies.push_back(body);

    }

}

box2dhandler::~box2dhandler()
{
    for(b2Body* body : bodies)
    {
        body->DestroyFixture(body->GetFixtureList());
    }

    delete world;
}

/*
 * This method updates the B2d world, it should be called 60 times a second for nice 60fps gameplay
*/
void box2dhandler::updateWorld()
{
    int32 velocityIterations = 3;
    int32 positionIterations = 2;
    float32 timeStep = 3.0f / 60.0f; // 60fps
    (this->world)->Step(timeStep, velocityIterations, positionIterations);
}

/*
 * This method returns a vector of tuples containg information about each of the boxes.
 * The tuples are as follows:
 *  int: x position
 *  int: y position
 *  f32: angle
 *  int: size
*/
std::vector<std::tuple<int, int, float32, int>> box2dhandler::getBoxPositions()
{
    std::vector<std::tuple<int, int, float32, int>> toReturn;

    for(b2Body* body : bodies)
    {
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        //Note that this assumes that mass is the same as the size of the box
        //Note that the positions are adjusted so the cords are the center of the body
        toReturn.push_back(std::make_tuple(position.x - (sqrt(body->GetMass()) / 2), position.y - (sqrt(body->GetMass()) / 2), angle, (sqrt(body->GetMass()))));
    }

    return toReturn;
}


/*
 * This method moves a box when the user clicks on it
 * It works by finding a box that contains the given coordinate and moving it
 */
void box2dhandler::userMove(int xPos, int yPos)
{
    //to move a body, we remove it from the world, and read it again in the given position
    b2Body* toEdit = nullptr;
    uint toEditIndex = 0;
    int toEditSize = 0;
    for(int i=0; i < bodies.size(); i++)
    {
        b2Body * element = bodies[i];
        int pointx = element->GetPosition().x;
        int pointy = element->GetPosition().y;
        int size = sqrt(element->GetMass());

        if(pointx + size > xPos && pointx - size < xPos)
        {
            if(pointy + size > yPos && pointy - size < yPos)
            {
                toEdit = element;
                bodies[i] = bodies[0];
                bodies[0] = element;
                toEdit->SetType(b2_staticBody);
                b2Vec2 newPosition(xPos - size/2, yPos + size/2);
                toEdit->SetTransform(newPosition, 0.0f);

                toEdit->SetType(b2_dynamicBody);
                break;
            }
        }
    }
 }







