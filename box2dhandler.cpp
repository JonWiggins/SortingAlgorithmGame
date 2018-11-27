#include "box2dhandler.h"

box2dhandler::box2dhandler(std::vector<int> boxList)
{

    //define box2d world
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    this->world = world;

    //define ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    //define dynamic boxes
    //TODO repeat this for every box in the box list
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef); //Add these to vector

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

}

void box2dhandler::updateWorld()
{
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    float32 timeStep = 1.0f / 60.0f;

    world.Step(timeStep, velocityIterations, positionIterations);

}

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


