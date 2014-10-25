//
//  PrimeNumbers.cpp
//  QuickBenchmark
//
//  Created by Adam James Leuer on 10/22/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "PrimeNumbers.h"

using namespace PrimeNumbers ;

using namespace std ;



SieveOfEratosthenes::SieveOfEratosthenes() {}

SieveOfEratosthenes::SieveOfEratosthenes(unsigned n) : n(n) {
    listConsecutiveIntegers() ; //fill in sieveList with integers up to n
}


void SieveOfEratosthenes::listConsecutiveIntegers() {
    sieveList.push_back({0, marked::marked}) ;
    for (auto i = 1 ; i < n ; i++) {
        markedInteger mi = {i, marked::notMarked} ;
        sieveList.push_back(mi) ;
    }
}

void SieveOfEratosthenes::markAllForCurrentP() {
    //unsigned p2 = p * p ;
    
    for (auto i = 2 ; (p * i) < n; i++) {
        auto mk = p * i ;
        mark(mk) ;
    }
}

const vector<unsigned> & SieveOfEratosthenes::run(const std::chrono::seconds & timeDuration) {
    
    while ((p + 1) < n) {
        
        markAllForCurrentP() ;
        
        currentlyChecking = p + 1 ;
        
        if (marked(currentlyChecking) == false) {
            p = currentlyChecking ;
            foundPrimes.push_back(p) ;
        }
        else {
            p++ ;
        }
    }
    
    return foundPrimes ;
}

void PrimeNumberFindingAlgorithm2::findNextPrime() {
    
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

const vector<unsigned> & PrimeNumberFindingAlgorithm2::run(const std::chrono::seconds & timeDuration) {
    Timer timer ;
    timer.startTimer() ;
    
    while (timer.checkTimeElapsed() < timeDuration) { //debug code, remove true and uncomment
        findNextPrime() ;
    }
    
    return foundPrimes ;
}


