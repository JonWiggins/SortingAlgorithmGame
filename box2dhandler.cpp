#include "box2dhandler.h"
#include <iostream>

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

//This needs to be called 60 times a second
void box2dhandler::updateWorld()
{
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    float32 timeStep = 1.0f / 60.0f; // 60fps
    //std::cout << "Updating world" << std::endl;
    (this->world)->Step(timeStep, velocityIterations, positionIterations);
    //std::cout << "Done updating" << std::endl;
}

//This will be called each time the window is updated,
// it gives the needed info to the renderer to draw the boxes
std::vector<std::tuple<int, int, float32, int>> box2dhandler::getBoxPositions()
{
    std::vector<std::tuple<int, int, float32, int>> toReturn;

    for(b2Body* body : bodies)
    {
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        //Note that this assumes that mass is the same as the size of the box
        //Note that the positions are adjusted so the cords are the center of the body
        toReturn.push_back(std::make_tuple(position.x - (sqrt(body->GetMass()) / 2), position.y - (sqrt(body->GetMass()) / 2), angle, (sqrt(body->GetMass()) / 2)));
    }

    return toReturn;
}



void box2dhandler::userMove(int boxSize, int xPos, int yPos)
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
        int size = sqrt(element->GetMass()) / 2;

        if(pointx + size > xPos && pointx - size < xPos)
        {
            if(pointy + size > yPos && pointy - size < yPos)
            {
                toEdit = element;
                toEdit->SetType(b2_staticBody);
                b2Vec2 newPosition(xPos + size/2, yPos + size/2);
                toEdit->SetTransform(newPosition, 0.0f);

                toEdit->SetType(b2_dynamicBody);
                break;
            }
        }
    }
 }







