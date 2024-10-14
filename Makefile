CC = $(shell brew --prefix llvm)/bin/clang

CFLAGS = -std=c99 -Wall -Wno-missing-braces -DDEBUG
LDFLAGS =

BIN = ./bin
INCLUDES = -I./src/*.h
SRCS = $(shell find src -name "*.c")

SDL_PATH = lib/sdl
SDL_BIN = $(BIN)/$(SDL_PATH)
INCLUDES += -I$(SDL_PATH)/include
LDFLAGS += -L$(BIN) -Wl,-rpath,${BIN} -lSDL3

timeco:
	$(CC) $(INCLUDES) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(BIN)/$@

sdl:
	$(shell mkdir -p $(SDL_BIN))
	cmake -S $(SDL_PATH) -B $(SDL_BIN) -DSDL_STATIC=ON -DCMAKE_OSX_ARCHITECTURES="x86_64"
	cd $(SDL_BIN) && make -j 10
	cp $(SDL_BIN)/libSDL3.0.dylib $(BIN)
	cp $(SDL_BIN)/libSDL3.dylib $(BIN)
	cp $(SDL_BIN)/libSDL3.a $(BIN)

install:
	cp $(BIN)/timeco $(BIN)/us

run: install
	$(BIN)/us/timeco

clean-all:
	find bin ! -name 'src' ! -name 'util' -type d -maxdepth 1 -mindepth 1 -exec rm -rf {} +

clean:
	rm -f $(BIN)/timeco
