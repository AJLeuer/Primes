//
//  main.cpp
//  QuickBenchmark
//
//  Created by Adam James Leuer on 10/21/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include <iostream>
#include <ostream>
#include <sstream>

#include <vector>

#include "Timer.hpp"

using namespace std ;

static unsigned potentialPrime = 1 ; //the integer we're currently testing to see if prime

vector<unsigned> foundPrimes ;

void findNextPrime() {
    unsigned divisor ;
    
    if (potentialPrime != 1) {
        divisor = ((potentialPrime + 1) / 2) ;
        if ((divisor % 2) == 0) {
            divisor-- ;
        }
    }
    else {
        divisor = potentialPrime ;
    }
    
    while (divisor >= 1) {
        if ((divisor != 1) && ((potentialPrime % divisor) == 0)) {
            break ; //this one isn't prime
        }
        else if (divisor == 1) { //we've tested everything down to 1: it's a prime
            foundPrimes.push_back(potentialPrime) ;
            break ;
        }
        else {
            divisor = divisor - 2 ;
        }
    }
    
    potentialPrime += 2 ; //increment potentialPrime for next time it's called
}

/**
 * Finds as many primes as possible in the time allowed by timeDuration
 *
 * @param writeTo The output stream to be written
 * @param timeDuration How long the function should run, in seconds
 */
void findPrimesBenchmark(ostream & writeTo, const std::chrono::seconds & timeDuration) {
    Timer timer ;
    timer.startTimer() ;
    
    while (timer.checkTimeElapsed() < timeDuration) { //debug code, remove true and uncomment
        findNextPrime() ;
    }
    
    for (auto i = 0 ; i < foundPrimes.size() ; i++) {
        writeTo << foundPrimes.at(i) << ' ' ;
    }
    
    writeTo << endl << endl << "Benchmark Score: " << foundPrimes.size() << endl ;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    stringstream ss ;
    
    std::chrono::seconds time(10) ;
    
    findPrimesBenchmark(ss, time) ;
    
    string primesBenchm = ss.str() ;
    
    cout << primesBenchm ;
    
    return 0;
}
