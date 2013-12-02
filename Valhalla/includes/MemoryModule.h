/**
 * Brian Campuzano, Ryan Riley
 * ECEN 4593, Memory Simulation Project
 * Fall 2013, Professor Pleszkun
 * University of Colorado @ Boulder
 *
 * This file defines the interface for the Memory Module Class
 * This class simulates a memory check to see if a specific memory
 * access is in memory or not. If the value is a hit, the module
 * it returns its memory access time penalty. If it is a miss it
 * calls the next memory module, as well as adding its miss time
 * penalty.
 */

 #ifndef _MEMORY_MODULE_H_
 #define _MEMORY_MODULE_H_

 #include "StdTypes.h"

 namespace Valhalla
 {
     class MemoryModule
     {
        public:

            /** \brief Default contructor.
             *
             *  Sets all variables to 0, and all pointers to NULL.
             *
             * \param void
             *
             * \return new empty memory module
             */
            MemoryModule(void);

            /** \brief Partial constructor, sets most member variables
             *
             * Contructs new memory modules, fills most memeber variables.
             * Builds memory entry table based on parameters, sets all dirty
             * and valid bits.
             *
             * \param blockSize: Bytes of data in a memory entry
             * \param memorySize: Number of memory entries in memory module
             * \param associativity: Number of memory entries per block?
             * \param hitPenalty: Time to access memory entry if hit occurs
             * \param missPenalty: Time to check memory entry if miss occurs
             * \param transferPenalty: Time to transfer memory entry from next memory module
             *
             * \return new fully partially intialized memory module
             *
             */
            MemoryModule(uint32 blockSize, uint64 memorySize, uint64 associativity, uint32 hitPenalty,
                         uint32 missPenalty, uint32 transferPenalty);

            /** \brief Full constructor, sets all member variables
             *
             * Contructs new memory modules, fills all memeber variables.
             * Builds memory entry table based on parameters, sets all dirty
             * and valid bits.
             *
             * \param blockSize: Bytes of data in a memory entry
             * \param memorySize: Number of memory entries in memory module
             * \param associativity: Number of memory entries per block?
             * \param hitPenalty: Time to access memory entry if hit occurs
             * \param missPenalty: Time to check memory entry if miss occurs
             * \param transferPenalty: Time to transfer memory entry from next memory module
             * \param nextMemoryModule: Pointer to next memory module
             * \param busWidthToNextMemoryModule: Bus width between current memory module and next memory module
             *
             * \return new fully intialized memory module
             *
             */
            MemoryModule(uint32 blockSize, uint64 memorySize, uint64 associativity, uint32 hitPenalty,
                         uint32 missPenalty, uint32 transferPenalty, MemoryModule * nextMemoryModule,
                         uint32 busWidthToNextMemoryModule);

            /** \brief Sets the pointer to the next memory module
             *
             * \param nextMemoryModule: Pointer to next memory module
             * \param busWidthToNextMemoryModule: Bus width between current memory module and next memory module
             *
             */
            setNextMemoryModulePointer(MemoryModule * nextMemoryModule, uint32 busWidthToNextMemoryModule);

            checkMemoryEntry(uint8 referenceType, uint64 address);

        private:

            /** \brief Bytes of data in a memory entry */
            uint32 blockSize;

            /** \brief Number of memory entries in memory module */
            uint64 memorySize;

            /** \brief Number of memory entries per block?*/
            uint64 associativity;

            /** \brief Time to access memory entry if hit occurs */
            uint32 hitPenalty;

            /** \brief Time to check memory entry if miss occurs */
            uint32 missPenalty;

            /** \brief Time to transfer memory entry from next memory module */
            uint32 transferPenalty;

            /** \brief Pointer to next memory module */
            MemoryModule * nextMemoryModule;

            /** \brief Bus width between current memory module and next memory module */
            uint32 busWidthToNextMemoryModule;

            /*! \brief Struct for Holding Memory Entries */
            struct MemoryEntries
            {
            	bool * validArray;
            	uint8 * dirtyBits;
            	uint64 ** memoryEntries;
            } memoryEntries;
     };
 }

 #endif // _MEMORY_MODULE_H_
