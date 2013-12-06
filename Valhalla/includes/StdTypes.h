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

typedef uint_fast8_t uint8;
typedef int_fast8_t int8;
typedef uint_fast16_t uint16;
typedef int_fast16_t int16;
typedef uint_fast32_t uint32;
typedef int_fast32_t int32;
typedef uint_fast64_t uint64;
typedef int_fast64_t int64;

/*! \brief Enum for cache operations */
enum CacheOperation
  {
    CACHE_READ = 0,
    CACHE_WRITE,
    CACHE_OPERATION_MAX
  };

 #endif // _STDTYPES_H_
