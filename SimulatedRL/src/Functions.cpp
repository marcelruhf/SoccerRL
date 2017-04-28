/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: Functions.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <cmath>
#include <string>
#include <Tiles.hpp>
#include <Constants.hpp>
#include <Functions.hpp>

namespace mr
{
    std::valarray<float> features(double distance, double velocity)
    {
        const int num_tiles = 64+32;

        const int tilings1 = 64;
        const int tilings2 = 32;
        //const int tilings2 = 16;

        const int mem_size = 256;
        //const int mem_size = 2048;

        //the tiles will go here
        std::valarray<int> tiles_array(num_tiles);

        //the tiles assume a range 0 to 1, so they need to be scaled
        const int num_of_variables = 2;
        float scaled[num_of_variables];

        //resolution 10
        scaled[0] = distance / 10.f;
        scaled[1] = velocity / 10.f;

        //here the parameters are: array in which the tiles will go,
        // number of tilings, memory size, input variables, number of
        //input variables
        tiles(&tiles_array[0],tilings1,mem_size,scaled,num_of_variables);

        //resolution 4
        scaled[0] = distance / 4.f;
        scaled[1] = velocity / 4.f;

        //same things, but note how we want to start writing
        //into the array at the end of where we left off
        //from the call before
        tiles(&tiles_array[tilings1],tilings2,mem_size,scaled,num_of_variables);

        //we finally find out which ones of the 128 tiles (compressed) are activated:
        std::valarray<float> feat(mem_size);

        for (int i=0, size = tiles_array.size(); i<size; ++i) {
            feat[tiles_array[i]] = 1;
        }

        return feat;
    }
}