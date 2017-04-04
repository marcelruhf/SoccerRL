#ifndef SOCCERRL_TRACKER_ACTIONVALUEFUNCTION_HPP_
#define SOCCERRL_TRACKER_ACTIONVALUEFUNCTION_HPP_

#include <TrueOnlineSarsaUpdate.hpp>

#include "SarsaParams.h"

#include <vector>
#include <valarray>
#include <map>
#include <functional>
#include <istream>
#include <iterator>
#include <stdexcept>
#include <sstream>

// #include <iostream>

template <typename ActionType,
         typename ActionComparator = std::less<ActionType>,
         typename ActionEquality = std::equal_to<ActionType> >
struct ActionValueFunction {

    ActionValueFunction ( const SarsaParams p ) :
        alpha ( p.alpha ), gamma ( p.gamma ),lambda ( p.lambda ) {}

    double valueOf ( const std::valarray<float> &s, const ActionType &a ) const;
		
		std::vector< std::pair<ActionType, double> > valueOf ( const std::valarray<float> &s ) const;

    void update ( const std::valarray<float> &s,
                  const ActionType &a,
                  double r,
                  const std::valarray<float> &s_prime,
                  const ActionType &a_prime );

    void update ( const std::valarray<float> &s,
                  const ActionType &a,
                  double r );

    void clearE();

    void readFrom ( std::istream &fromStream );
    void writeTo ( std::ostream &toStream );

    typedef std::map< ActionType, std::valarray<float>, ActionComparator> ActionWeightsMap;

private:

    void update ( const std::valarray<float> &s,
                  const ActionType &a,
                  double r,
                  double q_hat_prime );

    ActionWeightsMap theta;
    ActionWeightsMap e;

    float gamma;
    float lambda;
    float alpha;

    double q_hat_old;

};


template<typename A,typename AC,typename AE>
double ActionValueFunction<A,AC,AE>::valueOf ( const std::valarray< float > &s,
        const A &a ) const
{

    typename ActionWeightsMap::const_iterator theta_i= theta.find ( a );

    if ( theta_i == theta.end() ) {
        return 0.;    // the default theta, when one is not prsent, is all zeros.
    }

    if ( theta_i->second.size() != s.size() ) {
        throw std::runtime_error ( "ActionValueFunction::valueOf: s and theta had different sizes" );
    }

    return ( theta_i->second * s ).sum(); //dot product
}

template<typename A,typename AC,typename AE>
std::vector< std::pair<A, double> > ActionValueFunction<A,AC,AE>::
																					valueOf ( const std::valarray<float> &s ) const {

	std::vector< std::pair<A, double> >  result;
	
	typename ActionWeightsMap::const_iterator theta_i = theta.begin();
	for(; theta_i != theta.end(); ++theta_i)
		result.push_back(std::pair<A, double>(theta_i->first, valueOf(s,theta_i->first)));
	
	return result;
}

template<typename A,typename AC,typename AE>
void ActionValueFunction<A,AC,AE>::update ( const std::valarray<float> &psi,
        const A &a,
        double r,
        double q_hat_prime )
{

// 		std::cout << "before" << std::endl;
//
// 		typename ActionWeightsMap::const_iterator epIt = e.begin();
// 		for(;epIt != e.end(); ++epIt) {
// 			std::copy(&epIt->second[0],&epIt->second[0]+epIt->second.size(),std::ostream_iterator<float>(std::cout, " "));
// 			std::cout << std::endl;
// 		}
// 		std::cout << "--" << std::endl;
// 				typename ActionWeightsMap::const_iterator tpIt = theta.begin();
// 		for(;tpIt != theta.end(); ++tpIt) {
// 			std::copy(&tpIt->second[0],&tpIt->second[0]+tpIt->second.size(),std::ostream_iterator<float>(std::cout, " "));
// 			std::cout << std::endl;
// 		}

    double q_hat = valueOf ( psi,a );

    float delta = r + gamma * q_hat_prime - q_hat;

    //at least ensure the existance of the theta we are going to modify
    if ( theta.find ( a ) == theta.end() ) {
        theta[a].resize ( psi.size() );
    }

//     float alpha = this->alpha/ ( std::max ( e.size(),theta.size() ) * psi.size() );

    //uppdate e

    AE isSameAction;

    typename ActionWeightsMap::iterator eIt = e.begin();

    for ( ; eIt != e.end(); ++eIt ) {

        if ( !isSameAction ( eIt->first,a ) ) {
            //then psi is all zeros
            true_online_sarsa::updateE ( alpha,gamma,lambda,std::valarray<float>(),eIt->second );
        }
    }

    //even if it didn't exist before, it has to be created here
    true_online_sarsa::updateE ( alpha,gamma,lambda,psi,e[a] );

    //update theta

    //this two loops could be merged, but I find it more readable this way

    typename ActionWeightsMap::iterator theta_element = theta.begin();

    for ( ; theta_element != theta.end(); ++theta_element ) {
        std::valarray<float> &e_i = e[theta_element->first];

        if ( !isSameAction ( theta_element->first, a ) ) {
            //then psi is all zeros
            true_online_sarsa::updateTheta ( alpha,delta,q_hat,q_hat_old,e_i,std::valarray<float>(),
                                             theta_element->second );
        }

    }

    true_online_sarsa::updateTheta ( alpha,delta,q_hat,q_hat_old,e[a],psi,
                                     theta[a] );

    q_hat_old = q_hat_prime;

// 				std::cout << "after" << std::endl;
//
// 		epIt = e.begin();
// 		for(;epIt != e.end(); ++epIt) {
// 			std::copy(&epIt->second[0],&epIt->second[0]+epIt->second.size(),std::ostream_iterator<float>(std::cout, " "));
// 			std::cout << std::endl;
// 		}
//
// 		std::cout << "--" << std::endl;
//
// 		tpIt = theta.begin();
// 		for(;tpIt != theta.end(); ++tpIt) {
// 			std::copy(&tpIt->second[0],&tpIt->second[0]+tpIt->second.size(),std::ostream_iterator<float>(std::cout, " "));
// 			std::cout << std::endl;
// 		}

}

template<typename A,typename AC,typename AE>
void ActionValueFunction<A,AC,AE>::update ( const std::valarray< float > &psi,
        const A &a, double r,
        const std::valarray< float > &psi_prime,
        const A &a_prime ) {

    double q_hat_prime = valueOf ( psi_prime,a_prime );

    update ( psi,a,r,q_hat_prime );

}

template<typename A,typename AC,typename AE>
void ActionValueFunction<A,AC,AE>::update ( const std::valarray<float> &s,
        const A &a,
        double r ) {

    update ( s,a,r,0. );
}


template<typename A,typename AC,typename AE>
void ActionValueFunction<A,AC,AE>::clearE() {
    e.clear();
}

template<typename A,typename AC,typename AE>
void ActionValueFunction<A,AC,AE>::readFrom ( std::istream &fromStream ) {
	
    theta.clear();

    while ( fromStream.good() &&  !fromStream.eof() ) {

        std::string actionLine;
        std::getline ( fromStream,actionLine );

        if ( !actionLine.empty() ) {

            std::string vectorLine;
            std::getline ( fromStream,vectorLine );
            std::stringstream numbers ( vectorLine );

            std::vector<float> values;
            std::copy ( std::istream_iterator<float> ( numbers ),std::istream_iterator<float>(),back_inserter ( values ) );
            std::valarray<float> theta_i ( &values[0], values.size() );

            theta.insert ( make_pair ( actionLine ,theta_i ) );
        }

    }
}

template<typename A,typename AC,typename AE>
void ActionValueFunction<A,AC,AE>::writeTo ( std::ostream &toStream ) {

    typename ActionWeightsMap::iterator actionIt = theta.begin();

    for ( ; actionIt != theta.end(); ++actionIt ) {
        toStream << actionIt->first << std::endl;
        std::copy ( &( actionIt->second )[0], ( &(actionIt->second)[actionIt->second.size()-1] ) +1,
										std::ostream_iterator<float> ( toStream, " " ) );
        toStream << std::endl;
    }
}


#endif

