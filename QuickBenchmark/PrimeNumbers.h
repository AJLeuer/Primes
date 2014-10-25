//
//  Header.h
//  QuickBenchmark
//
//  Created by Adam James Leuer on 10/22/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef QuickBenchmark_Header_h
#define QuickBenchmark_Header_h

#include <iostream>
#include <ostream>
#include <sstream>

#include <vector>
#include <utility>

#include "Timer.hpp"

using namespace std ;

enum class marked {
    marked,
    notMarked,
};

/**
 * Represents a natural number marked either true or false, depending on whether it is prime
 */
typedef std::pair<unsigned, marked> markedInteger ;

/**
 * @brief Provides methods for finding prime numbers
 */
namespace PrimeNumbers {
    

/**
 * Base class defining an interface for classes that provide a prime number finding
 * algorithm. Implementing classes will provide a run() method (or alternatively the use
 * of the call operator, both have identical functionality) in order to execute that
 * class's particular prime number finding method
 */
class PrimeNumberFindingAlgorithm {
    
protected:
    
    /**
     * Inheriting classes will typically store found primes in this container (though they are not required to)
     */
    vector<unsigned> foundPrimes ;
    
public:
    
    /**
     * Executes this prime number-finding algorithm
     *
     * @return All found primes
     */
    virtual const vector<unsigned> & run(const std::chrono::seconds & timeDuration) = 0 ;
    
    /**
     * Function call operator overload. Same as run().
     *
     * @see run()
     */
    virtual const vector<unsigned> & operator ()(const std::chrono::seconds & timeDuration) { return run(timeDuration) ; }
    
};

    

    

/**
 * @brief Implements the Sieve of Eratosthenes, an algorithm for finding prime numbers.
 *
 * @note Call the run() method, or use the call operator on an instance 
 */
class SieveOfEratosthenes : public PrimeNumberFindingAlgorithm {
    
protected:
    
    unsigned p = 2 ;
    
    unsigned n = 10000 ;
    
    unsigned currentlyChecking = 1 ;
    
    vector<markedInteger> sieveList ;
    
    void mark(unsigned index) { sieveList.at(index).second = marked::marked ; }
    
    bool marked(unsigned index) { return (sieveList.at(index).second == marked::marked) ; }
    
    /**
     * Helper function for sieve. Fills in list based on current values of p and n
     */
    void listConsecutiveIntegers() ;
    
    /**
     * Runs through the sieveList for the current p. Helper function for sieveOfEratosthenes.
     */
    void markAllForCurrentP() ;
    
public:
    
    SieveOfEratosthenes() ;
    
    /**
     * Finds primes up to integer n
     */
    SieveOfEratosthenes(unsigned n) ;
    
    /**
     * Executes this prime number-finding algorithm
     *
     * @note Uses an implementation of the Sieve of Eratosthenes, an centuries-old algorithm for finding prime numbers.
     *
     * @see <a href="http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes"> Wikipedia: Sieve of Eratosthenes</a>
     * 
     * @return All found primes
     */
    const vector<unsigned> & run(const std::chrono::seconds & timeDuration) ;
    
    
};
    
    
/**
* @brief Uses an essentially brute-force algorithm for finding primes
*
* @note Call run() method or call operator on an instance to use
*/
class PrimeNumberFindingAlgorithm2 : public PrimeNumberFindingAlgorithm {
    
protected:
    
    /**
     * Used by findNextPrime()
     */
    unsigned potentialPrime = 1 ; //the integer we're currently testing to see if prime
    

    /**
     * @brief Finds the next prime in sequence
     */
    void findNextPrime() ;
    
    
public:
    
    /**
     * Executes this prime number-finding algorithm
     *
     * @return All found primes
     */
    const vector<unsigned> & run(const std::chrono::seconds & timeDuration) ;
    
};
    
    
    
}
    
    
    
    
#endif
