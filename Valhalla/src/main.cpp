#include <iostream>

#include "StdTypes.h"
#include "MemoryModule.h"
#include "DefaultParameters.h"

using namespace std;
using namespace Valhalla;

int main(int argc, char ** argv)
{
  cout << "Creating Main Memory." << endl;
  MemoryModule * mainMemory = new MemoryModule();
  mainMemory->printMemoryModuleSetup();

  cout << "Creating L2 Cache." << endl;
  MemoryModule * l2Cache = new MemoryModule(L2_BLOCK_SIZE,
                                            L2_MEMORY_SIZE,
                                            L2_ASSOCIATIVITY,
                                            L2_HIT_PENALTY,
                                            (L2_MISS_PENALTY + MAIN_MEMORY_SEND_ADDRESS_TIME + MAIN_MEMORY_READY_TIME),
                                            MAIN_MEMORY_CHUNK_SEND_TIME,
                                            MAIN_MEMORY_ADDRESS_WIDTH,
                                            mainMemory);
  l2Cache->printMemoryModuleSetup();

  cout << "Creating L1 Data Cache." << endl;
  MemoryModule * l1DataCache = new MemoryModule(L1_BLOCK_SIZE,
                                                L1_MEMORY_SIZE,
                                                //L1_ASSOCIATIVITY,
                                                2,
                                                L1_HIT_PENALTY,
                                                L1_MISS_PENALTY,
                                                L2_TRANSFER_TIME,
                                                L2_TRANSFER_WIDTH,
                                                l2Cache);

  l1DataCache->printMemoryModuleSetup();

  cout << "Creating L1 Instruction Cache." << endl;
  MemoryModule * l1InstCache = new MemoryModule(L1_BLOCK_SIZE,
                                                L1_MEMORY_SIZE,
                                                L1_ASSOCIATIVITY,
                                                L1_HIT_PENALTY,
                                                L1_MISS_PENALTY,
                                                L2_TRANSFER_TIME,
                                                L2_TRANSFER_WIDTH,
                                                l2Cache);

  uint64 time = l1DataCache->checkMemoryEntry(CACHE_WRITE, 65536, 32);
  cout << "Time for memory lookup 1: " << time << endl;
  time = l1DataCache->checkMemoryEntry(CACHE_WRITE, 4096, 32);
  cout << "Time for memory lookup 2: " << time << endl;

  time = l1DataCache->checkMemoryEntry(CACHE_READ, 8192, 32);
  cout << "Time for memory lookup 3: " << time << endl;
  time = l1DataCache->checkMemoryEntry(CACHE_READ, 256, 32);
  cout << "Time for memory lookup 4: " << time << endl;

  time = l1DataCache->checkMemoryEntry(CACHE_READ, 512, 32);
  cout << "Time for memory lookup 5: " << time << endl;
  
  l1DataCache->printMemoryEntries();
  l2Cache->printMemoryEntries();

  
  cout << "Test Complete." << endl;
  return 0;
}
