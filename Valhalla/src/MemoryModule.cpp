/**
 * Brian Campuzano, Ryan Riley
 * ECEN 4593, Memory Simulation Project
 * Fall 2013, Professor Pleszkun
 * University of Colorado @ Boulder
 *
 * This file implements the interface described in MemoryModule.h
 */

#include <stddef.h>
#include <iostream>

#include "StdTypes.h"
#include "DefaultParameters.h"
#include "MemoryModule.h"

using namespace std;

#define MEMORY_MODULE_DEBUG 1
#ifdef MEMORY_MODULE_DEBUG
#define DEBUG_MODULE_COUT(m) cout << m << endl
#else
#define DEBUG_MODULE_COUT(m)
#endif //MEMORY_MODULE_DEBUG

namespace Valhalla
{
  MemoryModule::MemoryModule(void)
  {
    blockSize = 0;
    memorySize = 0;
    associativity = 0;
    hitPenalty = 0;
    transferPenalty = 0;
    nextMemoryModule = NULL;
    hitCount = 0;
    missCount = 0;
    memoryEntries = NULL;
  }

  MemoryModule::MemoryModule(uint32 newBlockSize, uint64 newMemorySize, uint64 newAssociativity, uint32 newHitPenalty,
                             uint32 newMissPenalty, uint32 newTransferPenalty, uint32 newBusWidthToNextMemoryModule,
                             MemoryModule * newNextMemoryModule)
  {
    blockSize = newBlockSize;
    memorySize = newMemorySize;
    associativity = newAssociativity;
    hitPenalty = newHitPenalty;
    transferPenalty = newMissPenalty + newTransferPenalty*(newBlockSize/newBusWidthToNextMemoryModule);
    nextMemoryModule = newNextMemoryModule;
    hitCount = 0;
    missCount = 0;
    if(!initalizeMemoryEntries())
      {
        cerr << "MemoryModule: Failed to initialize memory entries." << endl;
      }
  }

  uint64 MemoryModule::checkMemoryEntry(uint8 opcode, uint64 address, uint32 byteSize)
  {
    uint64 rv = 0;
    if(nextMemoryModule == NULL)
      {
        //Main memory, increment hit counter return 0
        hitCount++;
        return 0;
      }
    for(uint32 i = 0; i < byteSize; i += blockSize)
      {
        if(checkForCacheHit(address + i))
          {
            hitCount++;
            rv += hitPenalty;
          }
        else
          {
            missCount++;
            rv += transferPenalty + nextMemoryModule->checkMemoryEntry(opcode, address, blockSize);
          }
      }
    return rv;
  }

  bool MemoryModule::checkForCacheHit(uint64 address)
  {
    return false;
  }

  bool MemoryModule::initalizeMemoryEntries(void)
  {
    if(blockSize == 0 || associativity == 0)
      {
        cerr << "initalizeMemoryEntries: blockSize or associativity equals 0." << endl;
        return false;
      }
    rows = (memorySize/blockSize)/associativity;
    if(rows == 0)
      {
        cerr << "initalizeMemoryEntries: memory rows equals 0." << endl;
        return false;
      }

    memoryEntries = new MemoryEntry*[rows];
    for(uint64 i = 0; i < rows; i++)
      {
        memoryEntries[i] = new MemoryEntry[associativity];
        for(uint64 j = 0; j < associativity; j++)
          {
            memoryEntries[i][j].validBit = false;
            memoryEntries[i][j].tag = 0;
          }
      }

    return true;
  }
  
  void MemoryModule::printMemoryModuleSetup(void)
  {
#ifdef MEMORY_MODULE_DEBUG
    DEBUG_MODULE_COUT("Block Size: " << blockSize);
    DEBUG_MODULE_COUT("Memory Size: " << memorySize);
    DEBUG_MODULE_COUT("Associativity: " << associativity);
    DEBUG_MODULE_COUT("Hit Penalty: " << hitPenalty);
    DEBUG_MODULE_COUT("Transfer Penalty: " << transferPenalty);
    DEBUG_MODULE_COUT("Hit Count: " << hitCount);
    DEBUG_MODULE_COUT("Miss Count: " << missCount);
    DEBUG_MODULE_COUT("Hit Penalty: " << hitPenalty);
    if(nextMemoryModule == NULL)
      {
        DEBUG_MODULE_COUT("Next Memory Module Doesn't Exist");
      }
    else
      {
        DEBUG_MODULE_COUT("Next Memory Module Exists");
      }
    if(memoryEntries == NULL)
      {
        DEBUG_MODULE_COUT("Memory Entries are NULL");
      }
    else 
      {
        DEBUG_MODULE_COUT("Memory Entries not NULL");
        printMemoryEntries();
      }
#endif //MEMORY_MODULE_DEBUG
  }

  void MemoryModule::printMemoryEntries(void)
  {
#ifdef MEMORY_MODULE_DEBUG
    for(uint64 i = 0; i < rows; i++)
      {
        for(uint64 j = 0; j < associativity; j++)
          {
            DEBUG_MODULE_COUT("(" << i << "," << j<< ") Valid: " << memoryEntries[i][j].validBit << ", Tag: " << memoryEntries[i][j].tag);
          }
      }
#endif //MEMORY_MODULE_DEBUG
  }
}
