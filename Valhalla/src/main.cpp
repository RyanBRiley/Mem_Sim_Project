#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
  cout << "Creating Main Memory." << endl;
  uint64 mainMemoryAccessTime = (DEFAULT_SEND_ADDRES_TIME + DEFAULT_READY_TIME + DEFAULT_CHUNK_SEND_TIME*(DEFAULT_L2_BLOCK_SIZE/DEFAULT_ADDRESS_WIDTH));
  MemoryModule * mainMemory = new MemoryModule(1, 1, 1, mainMemoryAccessTime, 0);
  
  cout << "Creating L2 Cache." << endl;
  MemoryModule * l2Cache = new MemoryModule(DEFAULT_L2_BLOCK_SIZE,
                                            DEFAULT_L2_MEMORY_SIZE,
                                            DEFAULT_L2_ASSOCIATIVTY,
                                            DEFAULT_L2_HIT_PENALTY,
                                            DEFAULT_L2_MISS_PENALTY,
                                            DEFAULT_L2_TRANSFER_TIME,
                                            mainMemory,
                                            DEFAULT_L2_TRANSFER_WIDTH);

  cout << "Creating L1 Cache." << endl;
  MemoryModule * l1Cache = new MemoryModule(
  
  cout << "Test Complete." << endl;
  return 0;
}
