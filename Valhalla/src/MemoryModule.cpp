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
    blockSize = 0;
    memorySize = 0;
    associativity = 0;
    hitPenalty = 0;
    transferPenalty = 0;
    nextMemoryModule = NULL;
    hitCount = 0;
    missCount = 0;
    if(!initalizeMemoryEntries())
      {
        cerr << "MemoryModule: Failed to initialize memory entries." << endl;
      }
  }

  MemoryModule::MemoryModule(uint32 newBlockSize, uint64 newMemorySize, uint64 newAssociativity, uint32 newHitPenalty,
                         uint32 newMissPenalty, uint32 newTransferPenalty, uint32 newBusWidthToNextMemoryModule,
                         MemoryModule * newNextMemoryModule)
  {
    blockSize = newBlockSize;
    memorySize = newMemorySize;
    associativity = newAssociativity;
    hitPenalty = newHitPenalty;
    transferPenalty = newMissPenalty + newTransferPenalty(newBlockSize/newBusWidthToNextMemoryModule);
    nextMemoryModule = newNextMemoryModule;
    hitCount = 0;
    missCount = 0;
    if(!initalizeMemoryEntries())
      {
        cerr << "MemoryModule: Failed to initialize memory entries." << endl;
      }
  }

  bool MemoryModule::setNextMemoryModulePointer(uint32 newTransferPenalty, uint32 newBusWidthToNextMemoryModule,
                                                MemoryModule * newNextMemoryModule)
  {
    if(newNextMemoryModule == NULL)
      {
        return false;
      }
    transferPenalty = missPenalty + newTransferPenalty(blockSize/newBusWidthToNextMemoryModule);;
    nextMemoryModule = newNextMemoryModule;
    return true;
  }

  uint64 MemoryModule::checkMemoryEntry(uint8 opcode, uint64 address, uint32 byteSize)
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
