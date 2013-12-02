/**
 * Brian Campuzano, Ryan Riley
 * ECEN 4593, Memory Simulation Project
 * Fall 2013, Professor Pleszkun
 * University of Colorado @ Boulder
 *
 * This file implements the interface described in MemoryModule.h
 */
 
MemoryModule::MemoryModule(void);
 
MemoryModule::MemoryModule(uint32 blockSize, uint64 memorySize, uint64 associativity, uint32 hitPenalty,
                         uint32 missPenalty, uint32 transferPenalty);

MemoryModule::MemoryModule(uint32 blockSize, uint64 memorySize, uint64 associativity, uint32 hitPenalty,
                         uint32 missPenalty, uint32 transferPenalty, MemoryModule * nextMemoryModule,
                         uint32 busWidthToNextMemoryModule);
						 
bool MemoryModule::setNextMemoryModulePointer(MemoryModule * nextMemoryModule, uint32 busWidthToNextMemoryModule);

bool MemoryModule::checkMemoryEntry(uint8 referenceType, uint64 address);