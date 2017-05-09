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
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <Simulator.hpp>
#include <Functions.hpp>

namespace mr
{
    Simulator::Simulator()
    {
        boost::random::uniform_int_distribution<> dist(-20, 20);
        distX = dist(gen);
        while (distX == 0) distX = dist(gen);
        distY = 50;
        velocity = dist(gen);
        while (velocity == 0) velocity = dist(gen);
    }

    float Simulator::getDistX()
    {
        return distX;
    }

    float Simulator::getDistY()
    {
        return distY;
    }

    float Simulator::getVelocity()
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
        boost::random::uniform_int_distribution<> dist(-20, 20);
        distX = dist(gen);
        while (distX == 0) distX = dist(gen);
        distY = 50;
        velocity = dist(gen);
        while (velocity == 0) velocity = dist(gen);
    }

}