BIN_NAME = magic
LIB_NAME = 

CFLAGS=-Wall -Werror -Wpedantic -Iinclude
LDFLAGS=-lGL -lglfw -lGLEW

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(patsubst src/%.cpp,obj/%.o, $(SOURCES))

$(BIN_NAME): $(OBJECTS)
	g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.cpp
	mkdir -p $(shell dirname $@)
	g++ $(CFLAGS) -c -o $@ $^

clean:
	rm $(BIN_NAME) -f
	rm -rf obj

