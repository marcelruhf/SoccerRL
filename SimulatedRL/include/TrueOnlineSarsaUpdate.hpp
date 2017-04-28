#ifndef SOCCERRL_TRACKER_TRUEONLINESARSAUPDATE_HPP_
#define SOCCERRL_TRACKER_TRUEONLINESARSAUPDATE_HPP_

/* This algorithm is an implementation of
 *
 * Seijen, Harm V., and Rich Sutton. "True Online Temporal-Difference Learning"
 * Arxiv available from http://arxiv.org/abs/1512.04087
 *
 */

#include <valarray>

namespace mr
{
	void updateE(float alpha, float gamma, float lambda, const std::valarray<float>& psi, std::valarray<float>& e);
	void updateTheta(float alpha, float delta, float q_hat, float q_hat_old, const std::valarray<float>& e, const std::valarray<float>& psi, std::valarray<float>& theta);
}

#endif
