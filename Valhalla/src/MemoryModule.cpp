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
#include <string>

#include "StdTypes.h"
#include "DefaultParameters.h"
#include "MemoryModule.h"

using namespace std;

#define MEMORY_MODULE_DEBUG 1
#ifdef MEMORY_MODULE_DEBUG
#define DEBUG_MODULE_COUT(m) cout << m
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
    indexShiftAmount = 0;
    memoryEntries = NULL;
  }

  MemoryModule::MemoryModule(std::string newModuleName, uint32 newBlockSize, uint64 newMemorySize, uint64 newAssociativity, uint32 newHitPenalty,
                 uint32 newMissPenalty, uint32 mainMemoryStartupPenalty, uint32 newTransferPenalty, uint32 newBusWidthToNextMemoryModule,
                 MemoryModule * newNextMemoryModule, std::string newNameNextMemoryModule)
    {
    moduleName = newModuleName;
    blockSize = newBlockSize;
    memorySize = newMemorySize;
    associativity = newAssociativity;
    hitPenalty = newHitPenalty;
    missPenalty = newMissPenalty;
    transferPenalty = mainMemoryStartupPenalty + newTransferPenalty*(newBlockSize/newBusWidthToNextMemoryModule);
    nextMemoryModule = newNextMemoryModule;
    nameNextMemoryModule = newNameNextMemoryModule;
    hitCount = 0;
    missCount = 0;
        
    if(!initalizeMemoryEntries())
      {
        cerr << "MemoryModule: Failed to initialize memory entries." << endl;
      }
    tagShiftAmount = 0;
    uint64 logHold = rows;
    while(logHold != 1)
      {
        tagShiftAmount++;
        logHold >>= 1;
      }
    indexShiftAmount = 0;
    logHold = blockSize;
    while(logHold != 1)
      {
        indexShiftAmount++;
        logHold >>= 1;
      }
    indexBitMask = rows - 1;
    tagBitMask = ~indexBitMask;
    indexBitMask <<= indexShiftAmount;
    tagBitMask <<= indexShiftAmount;
    tagShiftAmount += indexShiftAmount;
  }

  uint64 MemoryModule::checkMemoryEntry(CacheOperation operation, uint64 address, uint32 byteSize)
  {
    if(nextMemoryModule == NULL)
      {
        //Main memory, increment hit counter return 0
        hitCount++;
        return 0;
      }
    
    //take care of address that do not line up with blocks
    uint64 remainder = address % blockSize;
    if(remainder != 0)
      {
        address -= remainder;
        byteSize += remainder;
      }
    uint64 rv = 0;
    uint64 index = 0;
    uint64 tag = 0;
    uint64 writeBackAddress = 0;
    uint64 endAddressValue = address + byteSize;
    bool hitFlag = false;
    
    for(; address < endAddressValue; address += blockSize)
      {
        DEBUG_MODULE_COUT("Level " << moduleName << " access addr = 0x" << hex << address << ", reftype = " << dec << operation << endl);
        index = (address & indexBitMask) >> indexShiftAmount;
        tag = (address & tagBitMask) >> tagShiftAmount;
        DEBUG_MODULE_COUT("    index = 0x" << hex << index << ", tag = 0x" << tag);
        for(MemoryList::iterator it = memoryEntries[index].begin(); it != memoryEntries[index].end(); it++)
          {
            if((it->validBit == true) && (it->tag == tag))
              {
                DEBUG_MODULE_COUT("  HIT" << endl);
                //cache hit, LRU bump
                //copy MemoryEntry and push it to the front, then delete old entry
                //unsure if this will create a copy...
                MemoryEntry hit = MemoryEntry((*it));
                if(operation == CACHE_WRITE)
                  {
                    hit.dirtyBit = true;
                  }
                memoryEntries[index].push_front(hit);
                memoryEntries[index].erase(it);
                hitCount++;
#ifdef MEMORY_MODULE_DEBUG
                cout << "Add " <<  moduleName << " hit time (+ " << dec << hitPenalty << ")" << endl;
#endif
                rv += hitPenalty;
                hitFlag = true;
                break;
              }
          }
        if(hitFlag)
          {
            hitFlag = false;
            continue;
          }
        DEBUG_MODULE_COUT("  MISS" << endl);
        rv += missPenalty;
#ifdef MEMORY_MODULE_DEBUG
        cout << "Add " << moduleName << "miss time (+ " << dec << missPenalty << ")" << endl;
#endif

        //cache miss write it to cache via LRU
        MemoryEntry missed = MemoryEntry();
        missed.validBit = true;
        if(operation == CACHE_WRITE)
          {
            missed.dirtyBit = true;
	    rv += transferPenalty + nextMemoryModule->checkMemoryEntry(CACHE_READ, address, blockSize);
          }
        else
          {
            missed.dirtyBit = false;
          }
        missed.tag = tag;
        //delete last memory entry
        MemoryEntry toDelete = memoryEntries[index].back();
        if(toDelete.validBit && toDelete.dirtyBit)
          {
            //need to write entry, reconstruct address.
            DEBUG_MODULE_COUT("    checkMemoryEntry: write back needed");
            writeBackAddress = (toDelete.tag << tagShiftAmount) | (index << indexShiftAmount);
            rv += transferPenalty + nextMemoryModule->checkMemoryEntry(CACHE_WRITE, writeBackAddress, blockSize);
          }
        memoryEntries[index].pop_back();
        //put cache miss at front.
        memoryEntries[index].push_front(missed);
        
        missCount++;
        if(operation == CACHE_READ)
          {
            rv += nextMemoryModule->checkMemoryEntry(operation, address, blockSize);
            DEBUG_MODULE_COUT("Bringing line into " << moduleName << "." << endl);
            rv += transferPenalty;
            DEBUG_MODULE_COUT("Add " << nameNextMemoryModule << " to " << moduleName << " transfer time (+ "  << dec << transferPenalty << ")" << endl);
            rv += hitPenalty;
#ifdef MEMORY_MODULE_DEBUG
            cout << "Add " << moduleName << "hit replay time (+ " << hitPenalty << ")" << endl;
#endif
          }
        else
          {
			//operation is a cache write, and missed the cache, this code isn't right
            rv += hitPenalty;
          }
      }
    return rv;
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
            temp.dirtyBit = false;
            temp.tag = 0;
            memoryEntries[i].push_back(temp);
          }
      }

    return true;
  }
  
  void MemoryModule::printMemoryModuleSetup(void)
  {
#ifdef MEMORY_MODULE_DEBUG
    DEBUG_MODULE_COUT("Block Size: " << blockSize << endl);
    DEBUG_MODULE_COUT("Memory Size: " << memorySize << endl);
    DEBUG_MODULE_COUT("Associativity: " << associativity << endl);
    DEBUG_MODULE_COUT("Hit Penalty: " << hitPenalty << endl);
    DEBUG_MODULE_COUT("Transfer Penalty: " << transferPenalty << endl);
    DEBUG_MODULE_COUT("Hit Count: " << hitCount << endl);
    DEBUG_MODULE_COUT("Miss Count: " << missCount << endl);
    DEBUG_MODULE_COUT("Hit Penalty: " << hitPenalty << endl);
    DEBUG_MODULE_COUT("Rows: " << rows << endl);
    DEBUG_MODULE_COUT("Index Bit Mask: 0x" << hex << indexBitMask << endl);
    DEBUG_MODULE_COUT("Tag Bit Mask: 0x" << hex << tagBitMask << dec << endl);
    DEBUG_MODULE_COUT("Tag Shift Amount: " << tagShiftAmount << endl);
    DEBUG_MODULE_COUT("Index Shift Amount: " << indexShiftAmount << endl);
    if(nextMemoryModule == NULL)
      {
        DEBUG_MODULE_COUT("Next Memory Module Doesn't Exist" << endl);
      }
    else
      {
        DEBUG_MODULE_COUT("Next Memory Module Exists" << endl);
      }
    if(memoryEntries == NULL)
      {
        DEBUG_MODULE_COUT("Memory Entries are NULL" << endl);
      }
    else 
      {
        DEBUG_MODULE_COUT("Memory Entries not NULL" << endl);
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
            DEBUG_MODULE_COUT("(" << i << "," << j<< ") Valid: " << it->validBit << ", Dirty: " << it->dirtyBit << ", Tag: " << it->tag << endl);
            j++;
          }
      }
#endif //MEMORY_MODULE_DEBUG
  }
}
