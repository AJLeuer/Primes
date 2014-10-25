//
//  OpenCLInit.h
//  Primes
//
//  Created by Adam James Leuer on 10/25/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef Primes_OpenCLInit_h
#define Primes_OpenCLInit_h

#include <iostream>

#include <OpenCL/OpenCL.h>

using namespace std ;

void runOpenCLKernel() ;

extern cl_device_id * currentDeviceID ;
extern char * currentDeviceName ;


#endif
