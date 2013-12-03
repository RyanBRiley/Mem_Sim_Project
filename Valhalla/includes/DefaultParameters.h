/**
 * Brian Campuzano, Ryan Riley
 * ECEN 4593, Memory Simulation Project
 * Fall 2013, Professor Pleszkun
 * University of Colorado @ Boulder
 *
 * This file defines default parameter values for the memory simulation.
 */

#ifndef _DEFAULT_PARAMTERS_H_
#define _DEFAULT_PARAMTERS_H_

/** \brief These are the default values for the L1 Cache */
#define L1_BLOCK_SIZE			            32
#define L1_MEMORY_SIZE			            8192
#define L1_ASSOCIATIVITY		            1
#define L1_HIT_PENALTY			            1
#define L1_MISS_PENALTY		                1

/** \brief These are the default values for the L2 Cache */
#define L2_BLOCK_SIZE			            64
#define L2_MEMORY_SIZE			            65536
#define L2_ASSOCIATIVITY		            1
#define L2_HIT_PENALTY			            4
#define L2_MISS_PENALTY	    	            6
#define L2_TRANSFER_TIME                    6
#define L2_TRANSFER_WIDTH                   16

/** \brief These are the default values for Main Memory */
#define MAIN_MEMORY_SEND_ADDRESS_TIME       10
#define MAIN_MEMORY_READY_TIME              50
#define MAIN_MEMORY_CHUNK_SEND_TIME         20
#define MAIN_MEMORY_ADDRESS_WIDTH           16

#endif //_DEFAULT_PARAMTERS_H_
