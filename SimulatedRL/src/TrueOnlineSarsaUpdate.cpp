#include <TrueOnlineSarsaUpdate.hpp>

/* This algorithm is an implementation of
 *
 * Seijen, Harm V., and Rich Sutton. "True Online Temporal-Difference Learning"
 * Arxiv available from http://arxiv.org/abs/1512.04087
 *
 */

#include <sstream>
#include <stdexcept>

namespace mr
{
    void updateE(float alpha, float gamma, float lambda, const std::valarray<float> &psi, std::valarray<float> &e)
    {
        if (e.size() == 0)
        {
            e.resize(psi.size());
        }
        if (psi.size()>0)
        {
            if (psi.size() != e.size())
            {
                std::stringstream errorm;
                errorm << "true online sarsa update e: e and psi have different sizes - e.size() " << e.size() << " psi.size() " << psi.size();
                throw new std::runtime_error(errorm.str());
            }
            e = gamma * lambda * e + psi - alpha * gamma * lambda * (e * psi).sum() * psi;
        }
        else
        {
            e *= gamma * lambda;
        }
        return;
    }

    void updateTheta(float alpha, float delta, float q_hat, float q_hat_old, const std::valarray<float> &e, const std::valarray<float> &psi, std::valarray<float> &theta)
    {
        if (e.size()==0 && psi.size()==0)
        {
            return;
        }
        else if (e.size() > 0 && psi.size()==0)
        {
            if (theta.size() != e.size())
            {
                std::stringstream errorm;
                errorm << "true online sarsa update theta: e and theta have different sizes - e.size(): ";
                errorm << e.size() << " theta.size(): " << theta.size();
                throw new std::runtime_error(errorm.str());
            }
            theta += alpha * (delta + q_hat - q_hat_old) * e;
        }
        else if (e.size() == 0 && psi.size() >0)
        {
            if (theta.size() != psi.size())
            {
                std::stringstream errorm;
                errorm << "true online sarsa update theta: psi and theta have different sizes - psi.size(): ";
                errorm << psi.size() << " theta.size(): " << theta.size();
                throw new std::runtime_error(errorm.str());
            }
            theta += -alpha * (q_hat - q_hat_old) * psi;
        }
        else  // both present
        {
            if(e.size() != theta.size() || psi.size() != theta.size())
            {
                std::stringstream errorm;
                errorm << "true online sarsa update theta: psi,theta, and e have different sizes - psi.size(): ";
                errorm << psi.size() << " theta.size(): " << theta.size();
                errorm << psi.size() << " e.size(): " << e.size();
                throw new std::runtime_error(errorm.str());
            }
            theta += alpha * (delta + q_hat - q_hat_old) * e - alpha * (q_hat - q_hat_old) * psi;
        }
        return;
    }
}
