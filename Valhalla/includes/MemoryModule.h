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

#include <list>
#include <string>

#include "StdTypes.h"

namespace Valhalla
{
  class MemoryModule
  {

    /*! \brief Struct for holding a memory entry */
    struct MemoryEntry
    {
      bool validBit;
      bool dirtyBit;
      uint64 tag;
    };

    typedef std::list<MemoryEntry> MemoryList;

  public:

    /** \brief Default contructor.
     *
     *  Sets all variables to 0, and all pointers to NULL.
     *
     * \param void
     *
     * \return new default memory module
     */
    MemoryModule(void);

    /** \brief Full constructor, sets all member variables
     *
     * Contructs new memory modules, fills all memeber variables.
     * Builds memory entry table based on parameters, sets all dirty
     * and valid bits.
     *
     * \param moduleName: Name for memory module
     * \param blockSize: Bytes of data in a memory entry
     * \param memorySize: Number of memory entries in memory module
     * \param associativity: Number of memory entries per block?
     * \param hitPenalty: Time to access memory entry if hit occurs
     * \param missPenalty: Time to check memory entry if miss occurs
     * \param transferPenalty: Time to transfer memory entry from next memory module
     * \param nextMemoryModule: Pointer to next memory module
     * \param nameNextMemoryModule: name of the next memory module
     * \param busWidthToNextMemoryModule: Bus width between current memory module and next memory module
     *
     * \return new fully intialized memory module
     *
     */
    MemoryModule(std::string newModuleName, uint32 newBlockSize, uint64 newMemorySize, uint64 newAssociativity, uint32 newHitPenalty,
                 uint32 newMissPenalty, uint32 newTransferPenalty, uint32 newBusWidthToNextMemoryModule,
                 MemoryModule * newNextMemoryModule, std::string newNameNextMemoryModule);

    /** \brief Checks memory module for memory entry
     *
     * \param referenceType: Decoded reference type
     * \param address: Decoded memory address
     *
     * This is the main function used to check if an address is contained in memory. If nextMemoryModule
     * is null, module assumes it is main memory and just sends the hit delay. If nextMemoryModule is not
     * null AND the memory address is not contained in the module's memory entries, it calls
     * nextMemoryModule->checkMemoryEntry().
     *
     * \return uint64 time for memory lookup
     */
    uint64 checkMemoryEntry(CacheOperation operation, uint64 address, uint32 byteSize);

    /** \brief debug print function for setup of memory module */
    void printMemoryModuleSetup(void);

    /** \brief debug print function for memory module */
    void printMemoryEntries(void);

  private:

    /** \brief Name of Memory Module */
    std::string moduleName;

    /** \brief Bytes of data in a memory entry */
    uint32 blockSize;

    /** \brief Number of memory entries in memory module */
    uint64 memorySize;

    /** \brief Number of memory entries per block?*/
    uint64 associativity;

    /** \brief Time to access memory entry if hit occurs */
    uint32 hitPenalty;

    /** \brief Time to access memory entry if miss occurs */
    uint32 missPenalty;

    /** \brief Time to transfer memory entry from next memory module */
    uint32 transferPenalty;

    /** \brief Pointer to next memory module */
    MemoryModule * nextMemoryModule;

    /** \brief Name of next memory module */
    std::string nameNextMemoryModule;

    /*! \brief array of lists for memory entries */
    MemoryList * memoryEntries;

    /** \brief Number of hits for memory module */
    uint64 hitCount;

    /** \brief Number of misses for memory module */
    uint64 missCount;

    /** \brief Number of rows in memoryEntries */
    uint64 rows;

    /** \brief Bitmask for tag field of the address */
    uint64 tagBitMask;
            
    /** \brief Bitmask for the index field of the address */
    uint64 indexBitMask;

    /** \brief Tag shift amount */
    uint16 tagShiftAmount;

    /** \brief Tag shift amount */
    uint16 indexShiftAmount;

    /** \brief Intializes memoryEntries based on module's blockSize, memorySize, and associativity.
     *
     * \return boolean value based on success of operation
     */
    bool initalizeMemoryEntries(void);
            
  };
}

#endif // _MEMORY_MODULE_H_
