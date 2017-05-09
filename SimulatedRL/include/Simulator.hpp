/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: Simulator.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_SIMULATEDRL_SIMULATOR_HPP_
#define SOCCERRL_SIMULATEDRL_SIMULATOR_HPP_

#include <boost/random/mersenne_twister.hpp>

namespace mr
{
    class Simulator
    {
    private:
        float distX;
        float distY;
        float velocity;
        boost::random::mt19937 gen;
    public:
        Simulator();
        float getDistX();
        float getDistY();
        float getVelocity();
        void move(int);
        void nextEpisode();
    };
}

#endif  // SOCCERRL_SIMULATEDRL_SIMULATOR_HPP_
