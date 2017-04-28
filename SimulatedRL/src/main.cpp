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
#include <SarsaParams.hpp>
#include <TrueOnlineSarsaUpdate.hpp>
#include <ActionValueFunction.hpp>

int main(int argc, char **argv)
{
    try
    {
        mr::Simulator simulator;
        mr::SarsaParams params;
        params.alpha = 0.2;
        params.gamma = 1;
        params.lambda = 0.99;
        mr::ActionValueFunction<int> vf(params);
        std::ofstream datafile;

        boost::mt19937 gen;
        boost::random::uniform_real_distribution<double> rDist(0, 1);
        boost::random::uniform_int_distribution<> iDist(-1, 1);

        datafile.open("/users/marcelruhf/Documents/data2.csv");

        datafile << "Episode,Accumulate Reward" << std::endl;

        for (int i = 0; i < mr::NUM_EPISODES; ++i)
        {
            std::valarray<float> s, sPrime;
            boost::optional<int> a, aPrime;
            int r;

            //std::cout << "================================" << std::endl;
            //std::cout << "Episode " << i+1 << " started..." << std::endl;
            //std::cout << "Press ENTER to start the next episode: ";
            //std::cin.get();
            //std::cout << "================================" << std::endl;

            auto start = std::chrono::high_resolution_clock::now();

            long accumulative_reward = 0;

            for (;;)
            {
                auto rightnow = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float> duration = rightnow - start;

                if (simulator.getDistX() == 0)
                {  // The robot blocked the ball...
                    std::cout << "Goal state reached, end of episode." << std::endl;
                    break;
                }
                else if (simulator.getDistY() == 0)
                {  // The ball reached the goal and the robot didn't catch it...
                    std::cout << "No, they scored!" << std::endl;
                    break;
                }

                // Set S In SARS'A'
                s = {static_cast<float>(simulator.getDistX()), static_cast<float>(simulator.getVelocity())};

                std::cout << "Getting *a: " << std::endl;
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
                        std::cout << "Taking non-random action: " << *a << std::endl;
                    }
                }
                else
                {
                    a = aPrime;
                }
                // END: Set A in SARS'A'

                std::cout << "Current distance: " << simulator.getDistX() << ", " << "ball velocity: " << simulator.getVelocity() << ", move " << *a << "... ";
                simulator.move(*a);  // Executes A in SARS'A'
                std::cout << "new distance: " << simulator.getDistX() << std::endl;

                r = -std::abs(simulator.getDistX());  // Get reward
                accumulative_reward += r;  // Add reward to episode total

                // Set S' in SARS'A'
                sPrime = {static_cast<float>(simulator.getDistX()), static_cast<float>(simulator.getVelocity())};

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

                std::cout << "Updating value function... ";
                std::cout << "S(" << std::to_string(s[0]) << ") A(" << *a << ") R(" << r << ") S'(" << std::to_string(sPrime[0]) << ") A'(" << *aPrime << ")" << std::endl;
                vf.update(s, *a, r, sPrime, *aPrime);  // updates action value function, end of iteration...
                std::cout << "done." << std::endl;

                /*
                if (timestep == 0)
                {
                    simulator.setNextState();
                    timestep = 1;
                }
                else
                {
                    //if (mr::EPSILON > 0.f) mr::EPSILON -= 0.1f;
                    simulator.setActionReward();
                    simulator.setNextState();
                }

                if (simulator.getDistX() == 0 && simulator.getDistY() == 0)
                {
                    std::cout << "Goal state reached, end of episode." << std::endl;
                    simulator.setActionReward(100);
                    double accumulate_reward = simulator.getAccumulativeReward();
                    datafile << i+1 << "," << accumulate_reward << std::endl;
                    std::cout << "Episode " << i+1 << " complete" << std::endl;
                    std::cout << "Accumulative reward: " << simulator.getAccumulativeReward() << std::endl;
                    simulator.nextEpisode();
                    //break;
                    inEpisode = false;
                }
                else if (duration.count() > 9 || simulator.getDistY() == 0)
                {
                    std::cout << "Time's up!" << std::endl;
                    simulator.setActionReward(-100);
                    double accumulate_reward = simulator.getAccumulativeReward();
                    datafile << i+1 << "," << accumulate_reward << std::endl;
                    std::cout << "Episode " << i+1 << " complete" << std::endl;
                    std::cout << "Accumulative reward: " << simulator.getAccumulativeReward() << std::endl;
                    simulator.nextEpisode();
                    inEpisode = false;
                }

                if (inEpisode)
                {
                    int action = simulator.getNextAction();
                    std::cout << simulator.getDistX() << ", " << "ball velocity: " << simulator.getVelocity() << ", move " << action << "... ";
                    simulator.move(action);
                    std::cout << "new distance: " << simulator.getDistX() << std::endl;
                }
                else
                {
                    simulator.move(0);
                }

                if (timestep != 0)
                {
                    std::cout << "Updating value function... ";
                    simulator.updateVf();
                    std::cout << "done." << std::endl;
                }
                */
            }

            datafile << i+1 << "," << accumulative_reward << std::endl;
            std::cout << "Episode " << i+1 << " complete" << std::endl;
            std::cout << "Accumulative reward: " << accumulative_reward << std::endl;
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
