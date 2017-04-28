/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: Functions.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_TRACKER_FUNCTIONS_HPP_
#define SOCCERRL_TRACKER_FUNCTIONS_HPP_

#include <string>
#include <valarray>

namespace mr
{
    template <typename T> bool isnan(T x) { return (T(x) != T(x)); }
    std::valarray<float> features(double distance, double velocity);
}

#endif  // SOCCERRL_TRACKER_FUNCTIONS_HPP_
