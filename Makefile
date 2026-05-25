CXX = g++

SRC = src/*.cpp
OUT = oyun
CXXFLAGS = -Iinclude

LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT).exe