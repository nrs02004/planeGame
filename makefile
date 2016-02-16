CC=g++
#FLAGS=-lSDL2 -lSDL2_image
FLAGS = -framework SDL2 -framework SDL2_image -std=c++11
#-lSDL_image
PROJECTROOT=/Users/noahsimon/Dropbox/planeGame/SDL2_version
#PROJECTROOT=/home/nsimon/Desktop/planeGame/sdl2_version
INC=-I$(PROJECTROOT)/include 
LIB=-L$(PROJECTROOT)/lib
SRC=$(PROJECTROOT)/src/
LIBLUA=$(PROJECTROOT)/lib/liblua.a

all: gameApp

gameApp: main.o action.o display.o event.o image.o ship.o bullet.o enemyShip.o physicalObject.o lua_binding.o level.o
	$(CC) -o gameApp $(LIBLUA) main.o display.o event.o ship.o action.o bullet.o enemyShip.o physicalObject.o image.o lua_binding.o level.o $(FLAGS)

main.o: $(SRC)main.cpp
	$(CC) -c $(SRC)main.cpp  $(INC)

action.o: $(SRC)action.cpp
	$(CC) -c $(SRC)action.cpp $(INC)

display.o: $(SRC)display.cpp
	$(CC) -c $(SRC)display.cpp $(INC)

event.o: $(SRC)event.cpp
	$(CC) -c $(SRC)event.cpp $(INC)

image.o: $(SRC)image.cpp
	$(CC) -c $(SRC)image.cpp $(INC)

ship.o: $(SRC)ship.cpp
	$(CC) -c $(SRC)ship.cpp $(INC)

bullet.o: $(SRC)bullet.cpp
	$(CC) -c $(SRC)bullet.cpp $(INC)

enemyShip.o: $(SRC)enemyShip.cpp
	$(CC) -c $(SRC)enemyShip.cpp $(INC)

physicalObject.o: $(SRC)physicalObject.cpp
	$(CC) -c $(SRC)physicalObject.cpp $(INC)

lua_binding.o: $(SRC)lua_binding.cpp
	$(CC) -c $(SRC)lua_binding.cpp $(INC)

level.o: $(SRC)level.cpp
	$(CC) -c $(SRC)level.cpp $(INC)

clean:
	rm -rf gameApp *.o *~  src/*~ include/*~ level/*~ enemies/*~