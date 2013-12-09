#include <iostream>
#include <stdio.h>

#include "StdTypes.h"
#include "MemoryModule.h"
#include "DefaultParameters.h"

#define procBusWidth 4

using namespace std;
using namespace Valhalla;

int main(int argc, char ** argv)
{

  //Variables for mem operations
  char op;
  uint64 address;
  uint32 byteSize;
  uint64 time = 0;
  uint64 refNum = 0;
  
  cout << "Creating Main Memory." << endl;
  MemoryModule * mainMemory = new MemoryModule();
  //mainMemory->printMemoryModuleSetup();

  //cout << "Creating L2 Cache." << endl;
  MemoryModule * l2Cache = new MemoryModule("L2",
                                            L2_BLOCK_SIZE,
                                            L2_MEMORY_SIZE,
                                            L2_ASSOCIATIVITY,
                                            L2_HIT_PENALTY,
                                            L2_MISS_PENALTY,
                                            MAIN_MEMORY_SEND_ADDRESS_TIME + MAIN_MEMORY_READY_TIME,
                                            MAIN_MEMORY_CHUNK_SEND_TIME,
                                            MAIN_MEMORY_ADDRESS_WIDTH,
                                            mainMemory,
                                            "Memory");
  //l2Cache->printMemoryModuleSetup();

  //cout << "Creating L1 Data Cache." << endl;
  MemoryModule * l1DataCache = new MemoryModule("L1Data",
                                                L1_BLOCK_SIZE,
                                                L1_MEMORY_SIZE,
                                                L1_ASSOCIATIVITY,
                                                L1_HIT_PENALTY,
                                                L1_MISS_PENALTY,
                                                0,
                                                L2_TRANSFER_TIME,
                                                L2_TRANSFER_WIDTH,
                                                l2Cache,
                                                "L2");

  //l1DataCache->printMemoryModuleSetup();

  //cout << "Creating L1 Instruction Cache." << endl;
  MemoryModule * l1InstCache = new MemoryModule("L1Inst",
                                                L1_BLOCK_SIZE,
                                                L1_MEMORY_SIZE,
                                                L1_ASSOCIATIVITY,
                                                L1_HIT_PENALTY,
                                                L1_MISS_PENALTY,
                                                0,
                                                L2_TRANSFER_TIME,
                                                L2_TRANSFER_WIDTH,
                                                l2Cache,
                                                "L2");

  //l1InstCache->printMemorySetup();

  cout << "After initialization" << endl;
 
  while (scanf("%c %llx %ld\n",&op,&address,&byteSize) == 3)
    { 
      int bytesToFetch = byteSize;
      cout << "--------------------------------------------------------------------------------" << endl;
      cout << "Ref " << refNum;
      cout << ": Addr = " << hex << address;
      cout << ", Type = " << op;
      cout << ", BSize = " << byteSize << endl;
      while (bytesToFetch > 0)
	{
	   int tempByteSize;
	   if (!(bytesToFetch % procBusWidth)) tempByteSize = procBusWidth;
	   else tempByteSize = bytesToFetch % procBusWidth;
	   bytesToFetch = bytesToFetch - tempByteSize;
     	   switch(op)
        	{
        	case 'I':
          	//Intruction fetch
          	time += l1InstCache->checkMemoryEntry(CACHE_READ, address, tempByteSize);
          	break;
        	case 'R':
          	time += l1DataCache->checkMemoryEntry(CACHE_READ, address, tempByteSize);
         	 break;
        	case 'W':
          	time += l1DataCache->checkMemoryEntry(CACHE_WRITE, address, tempByteSize);
          	break;
        	default:
          	 continue;
        	}
	}
      cout << "Simulated time = " << dec << time << endl;
      refNum++;
    }
  /*
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
  
  */
  /*
    cout << "L1 instruction cache" << endl;
    l1InstCache->printMemoryEntries();
    cout << "L1 data cache" << endl;
    l1DataCache->printMemoryEntries();
    cout << "L2 cache" << endl;
    l2Cache->printMemoryEntries();
  */
  
  cout << "Test Complete." << endl;
  return 0;
}
