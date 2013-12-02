CC = g++
CFLAGS = $(INCLUDES) -c -Wall
LDFLAGS = 
SRC = ./src
INC_DIR = ./includes
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Memory_Simulator

export INCLUDES = -I$(INC_DIR)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SRC)/*o Memory_Simulator