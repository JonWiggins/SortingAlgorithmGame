#include "box2dhandler.h"

box2dhandler::box2dhandler(std::vector<int> boxList, int width, int height)
{
    this->width = width;
    this->height = height;

    grabbed = nullptr;

    //define box2d world
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    this->world = &world;

    //define ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    //define dynamic boxes
    int position = 10;
    for(int box : boxList)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;

        //TODO these positions will need to be staggered by index
        // this is done crudley right now
        bodyDef.position.Set(0.0f, position);
        position += 50;

        b2Body* body = world.CreateBody(&bodyDef); //Add these to vector

        bodies.push_back(body);

        b2PolygonShape dynamicBox;

        //value defines the size
        dynamicBox.SetAsBox(box, box);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
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
    float32 timeStep = 1.0f / 60.0f;

    world->Step(timeStep, velocityIterations, positionIterations);

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
        toReturn.push_back(std::make_tuple(position.x, position.y, angle, body->GetMass()));
    }

    return toReturn;
}

void box2dhandler::userGrab(int xPos, int yPos)
{
    //search bodies for one near the given location

    for(b2Body* body : bodies)
    {
        //again uses the assumption that the mass is equal to the size
        //Note: this size cast is okay becuase only int sizes are made
        int size = static_cast<int>(body->GetMass());
        b2Vec2 bodyPosition = body->GetPosition();

        //Note: these cast sare okay, just rounding to the nearest pixel
        int xDif = abs(xPos - static_cast<int>(bodyPosition.x));
        int yDif = abs(yPos - static_cast<int>(bodyPosition.y));

        if(xDif < (size / 2) &&  yDif < (size / 2))
        {
            //can grab
            grabbed = body;
            return;
        }
    }
}

void box2dhandler::userMove(int xPos, int yPos)
{
    if(grabbed == nullptr)
        return;


    //force cords to be within the frame
    if(xPos > this->width)
        xPos = this->width;

    if(xPos < 0)
        xPos =0;

    if(yPos < this->height)
        yPos = this->height;

    if(yPos < 0)
        yPos = 0;


    grabbed->SetTransform(b2Vec2(xPos,yPos),grabbed->GetAngle());
}

void box2dhandler::userPlace()
{
    grabbed = nullptr;
}



