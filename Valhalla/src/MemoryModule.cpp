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
#include <list>

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
    indexBitMask = 0;
    tagBitMask = 0;
    tagShiftAmount = 0;
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
    tagShiftAmount = 0;
    uint64 rowsHold = rows;
    while(rowsHold != 1)
      {
        tagShiftAmount++;
        rowsHold >>= 1;
      }

    indexBitMask = rows - 1;
    tagBitMask = ~indexBitMask; 
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
    uint64 index = address & indexBitMask;
    uint64 tag = (address & tagBitMask) >> tagShiftAmount;
    for(MemoryList::iterator it = memoryEntries[index].begin(); it != memoryEntries[index].end(); it++)
      {
        if((it->validBit == true) && (it->tag == tag))
          {
            //cache hit, LRU bump
            //unsure if this will create a copy...
            MemoryEntry hit = MemoryEntry((*it));
            memoryEntries[index].push_front(hit);
            memoryEntries[index].erase(it);
            return true;
          }
      }
    //cache miss write it to cache via LRU
    MemoryEntry missed = MemoryEntry();
    missed.validBit = true;
    missed.tag = tag;
    memoryEntries[index].pop_back();
    memoryEntries[index].push_front(missed);
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
    MemoryEntry temp;
    memoryEntries = new MemoryList[rows];
    for(uint64 i = 0; i < rows; i++)
      {
        for(uint64 j = 0; j < associativity; j++)
          {
            temp = MemoryEntry();
            temp.validBit = false;
            temp.tag = 0;
            memoryEntries[i].push_back(temp);
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
    DEBUG_MODULE_COUT("Index Bit Mask: 0x" << hex << indexBitMask);
    DEBUG_MODULE_COUT("Tag Bit Mask: 0x" << hex << tagBitMask << dec);
    DEBUG_MODULE_COUT("Tag Shift Amount: " << tagShiftAmount);
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
        //printMemoryEntries();
      }
#endif //MEMORY_MODULE_DEBUG
  }

  void MemoryModule::printMemoryEntries(void)
  {
#ifdef MEMORY_MODULE_DEBUG
    uint64 j;
    for(uint64 i = 0; i < rows; i++)
      {
        j = 0;
        for(MemoryList::const_iterator it = memoryEntries[i].begin(); it != memoryEntries[i].end(); it++)
          {
            DEBUG_MODULE_COUT("(" << i << "," << j<< ") Valid: " << it->validBit << ", Tag: " << it->tag);
            j++;
          }
      }
#endif //MEMORY_MODULE_DEBUG
  }
}
