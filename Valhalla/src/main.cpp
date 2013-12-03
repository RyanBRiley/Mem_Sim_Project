#include <iostream>

#include "StdTypes.h"
#include "MemoryModule.h"

using namespace std;

int main(int argc, char ** argv)
{
  cout << "Creating Main Memory." << endl;
  MemoryModule * mainMemory = new MemoryModule();

  cout << "Creating L2 Cache." << endl;
  MemoryModule * l2Cache = new MemoryModule(L2_BLOCK_SIZE,
                                            L2_MEMORY_SIZE,
                                            L2_ASSOCIATIVITY,
                                            L2_HIT_PENALTY,
                                            (L2_MISS_PENALTY + MAIN_MEMORY_SEND_ADDRESS_TIME + MAIN_MEMORY_READY_TIME),
                                            MAIN_MEMORY_CHUNK_SEND_TIME,
                                            MAIN_MEMORY_ADDRESS_WIDTH,
                                            mainMemory);

  cout << "Creating L1 Cache." << endl;
 MemoryModule * l1Cache = new MemoryModule(L1_BLOCK_SIZE,
                                           L1_MEMORY_SIZE,
                                           L1_ASSOCIATIVITY,
                                           L1_HIT_PENALTY,
                                           L1_MISS_PENALTY,
                                           L2_TRANSFER_TIME,
                                           L2_TRANSFER_WIDTH,
                                           l2Cache);

  cout << "Test Complete." << endl;
  return 0;
}
