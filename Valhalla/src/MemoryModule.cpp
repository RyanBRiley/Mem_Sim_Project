/**
 * Brian Campuzano, Ryan Riley
 * ECEN 4593, Memory Simulation Project
 * Fall 2013, Professor Pleszkun
 * University of Colorado @ Boulder
 *
 * This file implements the interface described in MemoryModule.h
 */
 
#include "StdTypes.h"
 
namespace Valhalla
{
	MemoryModule::MemoryModule(void)
	{
		blockSize = DEFAULT_BLOCK_SIZE;
		memorySize = DEFAULT_MEMORY_SIZE;
		associativity = DEFAULT_ASSOCIATIVITY;
		hitPenalty = DEFAULT_HIT_PENALTY;
		missPenalty = DEFAULT_MISS_PENALTY;
		transferPenalty = 0;
		nextMemoryModule = NULL;
		busWidthToNextMemoryModule = 0;
		if(!initalizeMemoryEntries())
		{
			//TODO: Error stuff here.
		}
	}
	 
	MemoryModule::MemoryModule(uint32 blockSize, uint64 memorySize, uint64 associativity, uint32 hitPenalty,
							 uint32 missPenalty)
	{
		blockSize = blockSize;
		memorySize = memorySize;
		associativity = associativity;
		hitPenalty = hitPenalty;
		missPenalty = missPenalty;
		transferPenalty = 0;
		nextMemoryModule = NULL;
		busWidthToNextMemoryModule = 0;
		if(!initalizeMemoryEntries())
		{
			//TODO: Error stuff here.
		}
	}

	MemoryModule::MemoryModule(uint32 blockSize, uint64 memorySize, uint64 associativity, uint32 hitPenalty,
							 uint32 missPenalty, uint32 transferPenalty, MemoryModule * nextMemoryModule,
							 uint32 busWidthToNextMemoryModule)
	{
		blockSize = blockSize;
		memorySize = memorySize;
		associativity = associativity;
		hitPenalty = hitPenalty;
		missPenalty = missPenalty;
		transferPenalty = transferPenalty;
		nextMemoryModule = nextMemoryModule;
		busWidthToNextMemoryModule = busWidthToNextMemoryModule;
		if(!initalizeMemoryEntries())
		{
			//TODO: Error stuff here.
		}
	}
							 
	bool MemoryModule::setNextMemoryModulePointer(uint32 transferPenalty, MemoryModule * nextMemoryModule, uint32 busWidthToNextMemoryModule)
	{
		transferPenalty = transferPenalty;
		nextMemoryModule = nextMemoryModule;
		busWidthToNextMemoryModule = busWidthToNextMemoryModule;
	}

	bool MemoryModule::checkMemoryEntry(uint8 referenceType, uint64 address)
	{
		if(nextMemoryModule == NULL)
		{
			return false;
		}
		
		return true;
	}
	
	bool MemoryModule::initalizeMemoryEntries(void)
	{
		uint32 rows = (memorySize/blockSize)/associativity;
		memory.validArray = new bool[rows];
		memory.dirtyBits = new uint8[rows];
		for(uint32 i = 0; i < rows; i++)
		{
			memory.memoryEntries[i] = new uint64[blockSize*associativity];
		}
	}
}