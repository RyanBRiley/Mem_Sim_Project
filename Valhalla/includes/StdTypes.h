/**
 * Brian Campuzano, Ryan Riley
 * ECEN 4593, Memory Simulation Project
 * Fall 2013, Professor Pleszkun
 * University of Colorado @ Boulder
 *
 * This file defines standard varibable types and functions used
 * in the memory simulation project.
 */

#include <stdint.h>

#ifndef _STDTYPES_H_
#define _STDTYPES_H_

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned int uint16;
typedef signed int int16;
typedef unsigned long int uint32;
typedef signed long int int32;
typedef unsigned long long int uint64;
typedef signed long long int int64;

/*! \brief Enum for cache operations */
enum CacheOperation
  {
    CACHE_READ = 0,
    CACHE_WRITE,
    CACHE_OPERATION_MAX
  };

 #endif // _STDTYPES_H_
