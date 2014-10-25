//
//  main.cpp
//  QuickBenchmark
//
//  Created by Adam James Leuer on 10/21/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//



#include <iostream>
#include <sstream>


#include "PrimeNumbers.h"
#include "ParallelSquare.cl.h"
#include "OpenCLInit.h"

using namespace std ;






int main(int argc, const char * argv[]) {

    runOpenCLKernel() ;
    
    /*
    stringstream primes ;
    
    std::chrono::seconds time(10) ;
    
    PrimeNumbers::PrimeNumberFindingAlgorithm *  primeNumberGen = new PrimeNumbers::PrimeNumberFindingAlgorithm2() ;
    
    auto & primesList = primeNumberGen->run(std::chrono::seconds(10)) ;
    
    cout << primes.rdbuf() ; */
    
    return 0;
}
