/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: main.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <valarray>
#include <chrono>
#include <cmath>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/optional.hpp>
#include <Simulator.hpp>
#include <Functions.hpp>
#include <Constants.hpp>
#include <Globals.hpp>
#include <SarsaParams.hpp>
#include <TrueOnlineSarsaUpdate.hpp>
#include <ActionValueFunction.hpp>
#include <Tiles.hpp>

namespace mr
{
    double EPSILON = 0.2;
}

std::valarray<float> features(float distance, float velocity) {
    const int num_tiles = 64;
    const int tilings1 = 64;

    const int mem_size = 4096;

    std::valarray<int> tiles_array(num_tiles);

    const int num_of_variables = 2;
    float scaled[num_of_variables];
    scaled[0] = distance / 4.f;
    scaled[1] = velocity / 4.f;

    tiles(&tiles_array[0],tilings1,mem_size,scaled,num_of_variables);

    std::valarray<float> feat(mem_size);

    for (int i=0, size = tiles_array.size(); i<size; ++i) {
        feat[tiles_array[i]] = 1;
    }

    /*
    std::cout << "Tiles array size: " << tiles_array.size() << std::endl;

    std::cout << "Tiles index: ";
    for (int i = 0; i < tiles_array.size(); ++i)
    {
        std::cout << tiles_array[i] << " ";
    }
    std::cout << std::endl;
     */

    return feat;
}

int main(int argc, char **argv)
{
    mr::Simulator simulator;
    mr::SarsaParams params;
    params.alpha = 0.3/4096;
    params.gamma = 0.9;
    params.lambda = 0.99;
    mr::ActionValueFunction<int> vf(params);

    //---------------------
    //initialization of the tiling code

    int dummy_tiles[1];
    float dummy_vars[1];

    srand(0);
    tiles(dummy_tiles,1,1,dummy_vars,0); // initialize the tiling hashing
    // consistently before srand is set

    //---------------------

    //initializing the seed of the random number generator
    srand((unsigned) time(NULL) * getpid());

    try
    {
        std::ofstream datafile;

        boost::mt19937 gen((unsigned) time(NULL) * getpid());
        boost::random::uniform_real_distribution<double> rDist(0, 1);
        boost::random::uniform_int_distribution<> iDist(-20, 20);

        datafile.open("/users/marcelruhf/Documents/new4_data11.csv");

        datafile << "Episode,Accumulative Reward" << std::endl;

        for (int i = 0; i < mr::NUM_EPISODES; ++i)
        {
            boost::optional<int> a, aPrime;
            double r;

            //std::cout << "================================" << std::endl;
            //std::cout << "Episode " << i+1 << " started..." << std::endl;
            //std::cout << "Press ENTER to start the next episode: ";
            //std::cin.get();
            //std::cout << "================================" << std::endl;

            //auto start = std::chrono::high_resolution_clock::now();

            long accumulative_reward = 0;

            for (;;)
            {
                //auto rightnow = std::chrono::high_resolution_clock::now();
                //std::chrono::duration<float> duration = rightnow - start;

                if (simulator.getDistX() == 0 && simulator.getDistX() == 0)
                {  // The robot blocked the ball...
                    //std::cout << "Goal state reached, end of episode." << std::endl;
                    break;
                }
                else if (simulator.getDistY() == 0)
                {  // The ball reached the goal and the robot didn't catch it...
                    //std::cout << "No, they scored!" << std::endl;
                    break;
                }

                // Set S In SARS'A'
                float distX = simulator.getDistX();
                float velocity = simulator.getVelocity();
                std::valarray<float> s = features(distX, velocity);

                // START: Set A in SARS'A'
                if (!aPrime)
                {
                    if (rDist(gen) < mr::EPSILON)
                    {
                        a = iDist(gen);
                    }
                    else
                    {
                        if (!vf.allEqual(s))
                        {
                            a = vf.bestAction(s);
                        }
                        else
                        {
                            a = iDist(gen);
                        }
                        //std::cout << "Taking non-random action: " << *a << std::endl;
                    }
                }
                else
                {
                    a = aPrime;
                }
                // END: Set A in SARS'A'

                //std::cout << "Current distance: " << simulator.getDistX() << ", " << "ball velocity: " << simulator.getVelocity() << ", move " << *a << "... ";
                simulator.move(*a);  // Executes A in SARS'A'
                //std::cout << "new distance: " << simulator.getDistX() << std::endl;

                // Set S' in SARS'A'
                float distXPrime = simulator.getDistX();
                float velocityPrime = simulator.getVelocity();
                std::valarray<float> sPrime = features(distXPrime, velocityPrime);

                // START: Set A' in SARS'A'
                if (rDist(gen) < mr::EPSILON)
                {
                    //std::cout << "Taking random action (epsilon-greedy): ";
                    aPrime = iDist(gen);
                    //std::cout << aPrime << std::endl;
                }
                else
                {
                    if (!vf.allEqual(sPrime))
                    {
                        aPrime = vf.bestAction(sPrime);
                    }
                    else
                    {
                        aPrime = iDist(gen);
                    }
                }
                // END: Set A' in SARS'A'

                // Set R in SARS'A'
                r = -std::abs(simulator.getDistX());
                accumulative_reward += r;  // Add reward to episode total

                vf.update(s, *a, r, sPrime, *aPrime);  // updates action value function, end of iteration...
            }

            if (i < 500)
            {
                mr::EPSILON -= (mr::EPSILON/1500);
            }
            else
            {
                mr::EPSILON = 0;
            }

            datafile << i+1 << "," << accumulative_reward << std::endl;
            //std::cout << "Episode " << i+1 << " complete" << std::endl;
            //std::cout << "Accumulative reward: " << accumulative_reward << std::endl;
            simulator.nextEpisode();
            vf.clearE();
        }

        datafile.close();

        return 0;
    }
    catch (const std::runtime_error* &re)
    {
        std::cout << re->what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "An exception has occurred!" << std::endl;
        std::cout << e.what() << std::endl;
    }
}