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
 
namespace Valhalla
{
  MemoryModule::MemoryModule(void)
  {
    blockSize = DEFAULT_L1_BLOCK_SIZE;
    memorySize = DEFAULT_L1_MEMORY_SIZE;
    associativity = DEFAULT_L1_ASSOCIATIVITY;
    hitPenalty = DEFAULT_L1_HIT_PENALTY;
    missPenalty = DEFAULT_L1_MISS_PENALTY;
    transferPenalty = 0;
    nextMemoryModule = NULL;
    busWidthToNextMemoryModule = 0;
    hitCount = 0;
    missCount = 0;
    if(!initalizeMemoryEntries())
      {
        cerr << "MemoryModule: Failed to initialize memory entries." << endl;
      }
  }
         
  MemoryModule::MemoryModule(uint32 newBlockSize, uint64 newMemorySize, uint64 newAssociativity, uint32 newHitPenalty,
                             uint32 newMissPenalty)
  {
    blockSize = newBlockSize;
    memorySize = newMemorySize;
    associativity = newAssociativity;
    hitPenalty = newHitPenalty;
    missPenalty = newMissPenalty;
    transferPenalty = 0;
    nextMemoryModule = NULL;
    busWidthToNextMemoryModule = 0;
    hitCount = 0;
    missCount = 0;
    if(!initalizeMemoryEntries())
      {
        cerr << "MemoryModule: Failed to initialize memory entries." << endl;
      }
  }

  MemoryModule::MemoryModule(uint32 newBlockSize, uint64 newMemorySize, uint64 newAssociativity, uint32 newHitPenalty,
                             uint32 newMissPenalty, uint32 newTransferPenalty, MemoryModule * newNextMemoryModule,
                             uint32 newBusWidthToNextMemoryModule)
  {
    blockSize = newBlockSize;
    memorySize = newMemorySize;
    associativity = newAssociativity;
    hitPenalty = newHitPenalty;
    missPenalty = newMissPenalty;
    transferPenalty = newTransferPenalty;
    nextMemoryModule = newNextMemoryModule;
    busWidthToNextMemoryModule = newBusWidthToNextMemoryModule;
    hitCount = 0;
    missCount = 0;
    if(!initalizeMemoryEntries())
      {
        cerr << "MemoryModule: Failed to initialize memory entries." << endl;
      }
  }
                                                         
  bool MemoryModule::setNextMemoryModulePointer(uint32 newTransferPenalty, MemoryModule * newNextMemoryModule,
                                                uint32 newBusWidthToNextMemoryModule)
  {
    if(newNextMemoryModule == NULL)
      {
        return false;
      }
    transferPenalty = newTransferPenalty;
    nextMemoryModule = newNextMemoryModule;
    busWidthToNextMemoryModule = newBusWidthToNextMemoryModule;
    return true;
  }

  bool MemoryModule::checkMemoryEntry(uint8 opcode, uint64 address, uint32 byteSize)
  {
    if(nextMemoryModule == NULL)
      {
        return false;
      }
                
    return true;
  }
        
  bool MemoryModule::initalizeMemoryEntries(void)
  {
    if(blockSize == 0 || associativity == 0)
      {
        cerr << "initalizeMemoryEntries: blockSize or associativity equals 0." << endl; 
        return false;
      }
    uint32 rows = (memorySize/blockSize)/associativity;
    if(rows == 0)
      {
        cerr << "initalizeMemoryEntries: memory rows equals 0." << endl; 
        return false;
      }
    
    memoryEntries = new MemoryEntry*[rows];
    for(uint32 i = 0; i < rows; i++)
      {
        memoryEntries[i] = new MemoryEntry[associativity];
      }
    
    return true;
  }
}
