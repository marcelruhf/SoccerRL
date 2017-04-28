/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: Simulator.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <iostream>
#include <string>
#include <Simulator.hpp>
#include <Functions.hpp>

namespace mr
{
    Simulator::Simulator()
    {
        //boost::random::uniform_int_distribution<> dist(-20, 20);
        distX = 20;
        //boost::random::uniform_int_distribution<> yDist(5, 20);
        distY = 1000;
        velocity = 0;
        //while (velocity == 0) velocity = dist(gen);
    }

    int Simulator::getDistX()
    {
        return distX;
    }

    int Simulator::getDistY()
    {
        return distY;
    }

    int Simulator::getVelocity()
    {
        return velocity;
    }

    void Simulator::move(int robotVelocity)
    {
        distX += (velocity - robotVelocity);
        if (distX < -20) distX  = -20;
        if (distX > 20)  distX  = 20;
        if (distY > 0)   distY -= 1;
        if (distY < 0)   distY  = 0;
    }

    void Simulator::nextEpisode()
    {
        //boost::random::uniform_int_distribution<> dist(-20, 20);
        distX = 20;
        //while (distX == 0) distX = dist(gen);
        //boost::random::uniform_int_distribution<> yDist(5, 20);
        distY = 1000;
        velocity = 0;
        //while (velocity == 0) velocity = dist(gen);
    }

}