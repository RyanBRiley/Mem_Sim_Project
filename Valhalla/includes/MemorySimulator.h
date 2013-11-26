/**
 * Brian Campuzano, Ryan Riley
 * ECEN 4593, Memory Simulation Project
 * Fall 2013, Professor Pleszkun
 * University of Colorado @ Boulder
 *
 * This file defines the interface for the Memory Simulator Class
 * This class simulates a memory check to see if a specific memory
 * access is in memory or not. If the value is a hit, the simulator
 * it returns its memory access time penalty. If it is a miss it
 * calls the next memory simulator, as well as adding its miss time
 * penalty.
 */

 #ifndef _MEMORY_SIMULATOR_H_
 #define _MEMORY_SIMULATOR_H_


 namespace Valhalla
 {
     class MemorySimulator
     {
        public:
            MemorySimulator(void);
     };
 }

 #endif // _MEMORY_SIMULATOR_H_
