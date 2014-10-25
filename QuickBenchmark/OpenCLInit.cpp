//
//  OpenCLInit.cpp
//  Primes
//
//  Created by Adam James Leuer on 10/25/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "OpenCLInit.h"

using namespace std ;

cl_device_id * currentDeviceID = (cl_device_id *)malloc(sizeof(cl_device_id)) ;
char * deviceName = (char*)malloc(100 * sizeof(char)) ;

/* Handles OpenCL initialization */
void runOpenCLKernel() {
    
    cl_platform_id platformID ;
    uint32_t actualTotalPlatformsAvailable = 2 ;
    
    
    clGetPlatformIDs(5, & platformID, & actualTotalPlatformsAvailable) ;
    
    size_t platformInfoStringSize = (1000 * sizeof(char)) ;
    char * platformProfile = (char *)malloc(platformInfoStringSize) ;
    size_t platformProfileActualSize  = 1 ;
    
    clGetPlatformInfo(platformID, CL_PLATFORM_PROFILE, platformInfoStringSize, platformProfile, & platformProfileActualSize) ;
    
    char * platformVersion = (char *)malloc(platformInfoStringSize) ;
    size_t platformVersionActualSize = 1 ;
    
    clGetPlatformInfo(platformID, CL_PLATFORM_VERSION, platformInfoStringSize, platformVersion, & platformVersionActualSize) ;
    
    char * platformName = (char *)malloc(platformInfoStringSize) ;
    size_t platformNameActualSize = 1 ;
    
    clGetPlatformInfo(platformID, CL_PLATFORM_NAME, platformInfoStringSize, platformName, & platformNameActualSize) ;
    
    char * platformVendor = (char *)malloc(platformInfoStringSize) ;
    size_t platformVendorActualSize = 1 ;
    
    clGetPlatformInfo(platformID, CL_PLATFORM_VENDOR, platformInfoStringSize, platformVendor, & platformVendorActualSize) ;
    
    char * platformExtensions = (char *)malloc(platformInfoStringSize) ;
    size_t platformExtensionsActualSize = 1 ;
    
    clGetPlatformInfo(platformID, CL_PLATFORM_EXTENSIONS, platformInfoStringSize, platformExtensions, & platformExtensionsActualSize) ;
    
    
    cl_device_id allDeviceIDs[10] ;
    cl_device_id * gpuID = (cl_device_id *)malloc(sizeof(cl_device_id)) ;
    cl_device_id * acceleratorID = (cl_device_id *)malloc(sizeof(cl_device_id)) ;
    cl_device_id * defaultDeviceID = (cl_device_id *)malloc(sizeof(cl_device_id)) ;
    
    uint32_t numberDevicesFound = 1 ;
    
    clGetDeviceIDs(platformID, CL_DEVICE_TYPE_ALL, 10, allDeviceIDs, & numberDevicesFound) ; //get a list of all devices
    clGetDeviceIDs(platformID, CL_DEVICE_TYPE_GPU, 10, gpuID, & numberDevicesFound) ;//get the gpu
    clGetDeviceIDs(platformID, CL_DEVICE_TYPE_ACCELERATOR, 10, acceleratorID, & numberDevicesFound) ;
    clGetDeviceIDs(platformID, CL_DEVICE_TYPE_DEFAULT, 10, defaultDeviceID, & numberDevicesFound) ;//get the default device (as a fallback when there's no gpu or accelerator)
    
    size_t actualSize = 1 ;
    
    cl_bool gpuAvailable = CL_FALSE ;
    cl_bool accelAvailable = CL_FALSE ;
    cl_bool defaultAvailable = CL_FALSE ;
    
    clGetDeviceInfo(*gpuID, CL_DEVICE_AVAILABLE, sizeof(cl_bool), & gpuAvailable, & actualSize) ;
    clGetDeviceInfo(*acceleratorID, CL_DEVICE_AVAILABLE, sizeof(cl_bool), & accelAvailable, & actualSize) ;
    clGetDeviceInfo(*defaultDeviceID, CL_DEVICE_AVAILABLE, sizeof(cl_bool), & defaultAvailable, & actualSize) ;
    
    if (gpuAvailable == CL_TRUE) {
        currentDeviceID = gpuID ;
        clGetDeviceInfo(*gpuID, CL_DEVICE_NAME, (100 * sizeof(char)), deviceName, & actualSize) ;
        
        free(acceleratorID) ;
        free(defaultDeviceID) ;
    }
    else if (accelAvailable == CL_TRUE) { //first fallback
        currentDeviceID = acceleratorID ;
        clGetDeviceInfo(*acceleratorID, CL_DEVICE_NAME, (100 * sizeof(char)), deviceName, & actualSize) ;
        
        free(gpuID) ;
        free(defaultDeviceID) ;
    }
    else if (defaultAvailable == CL_TRUE) { //our last resort
        currentDeviceID = defaultDeviceID ;
        clGetDeviceInfo(*defaultDeviceID, CL_DEVICE_NAME, (100 * sizeof(char)), deviceName, & actualSize) ;
        
        free(gpuID) ;
        free(acceleratorID) ;
    }
    else {
        //um... I dunno. Phone a friend?
    }
    
    
    free(platformProfile) ;
    free(platformVersion) ;
    free(platformName) ;
    free(platformVendor) ;
    free(platformExtensions) ;
}