CXX = g++
CXX_FLAGS = -Wall -Wextra -Werror -pedantic -std=gnu++2a -O3 -g

TARGET = ipkcpc
SRC = $(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXX_FLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)