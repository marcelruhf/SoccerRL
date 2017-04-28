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

namespace mr
{
    class Simulator
    {
    private:
        int distX;
        int distY;
        int velocity;
    public:
        Simulator();
        int getDistX();
        int getDistY();
        int getVelocity();
        void move(int);
        void nextEpisode();
    };
}

#endif  // SOCCERRL_SIMULATEDRL_SIMULATOR_HPP_
