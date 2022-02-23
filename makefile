#variables
COMPILE = g++
FLAGS = 
OBJS = HashTable.o
OUT = source

#targets
all: main.cpp $(OBJS)
	$(COMPILE) $(FLAGS) -o $(OUT) main.cpp $(OBJS)
HashTable.o: HashTable.h HashTable.cpp
	$(COMPILE) $(FLAGS) -c HashTable.cpp
clean:
	rm -rf *.o $(OUT)
