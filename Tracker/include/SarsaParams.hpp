#ifndef SOCCERRL_TRACKER_SARSAPARAMS_HPP_
#define SOCCERRL_TRACKER_SARSAPARAMS_HPP_

struct SarsaParams {
  
  SarsaParams() : alpha(0.1), gamma(0.9999), lambda(0.9){}
  
  double alpha;
  double gamma;
  double lambda;
};

#endif