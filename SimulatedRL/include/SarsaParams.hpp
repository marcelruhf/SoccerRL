#ifndef SOCCERRL_SIMULATEDRL_SARSAPARAMS_HPP_
#define SOCCERRL_SIMULATEDRL_SARSAPARAMS_HPP_

namespace mr
{
    struct SarsaParams {

        SarsaParams() : alpha(0.1), gamma(0.9999), lambda(0.9) {}
        SarsaParams(double a, double g, double l) : alpha(a), gamma(g), lambda(l) {}

        double alpha;
        double gamma;
        double lambda;
    };
}  // namespace mr

#endif  // SOCCERRL_SIMULATEDRL_SARSAPARAMS_HPP_