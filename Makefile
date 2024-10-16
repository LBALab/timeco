GAME := us

CC = $(shell brew --prefix llvm)/bin/clang

CFLAGS = -std=c99 -Wall -Wno-missing-braces -DDEBUG
LDFLAGS =

ROOT = ./
BIN = ./bin
INCLUDES = -I./src/*.h
SRCS = $(shell find src -name "*.c")

SDL_PATH = lib/sdl
SDL_BIN = $(BIN)/$(SDL_PATH)
SDL_MIXER_PATH = lib/sdl_mixer
SDL_MIXER_BIN = $(BIN)/$(SDL_MIXER_PATH)

INCLUDES += -I$(SDL_PATH)/include -I$(SDL_MIXER_PATH)/include
LDFLAGS += -L$(SDL_BIN) -L$(SDL_MIXER_BIN) -Wl,-rpath -Wl,${ROOT} -lSDL3

timeco:
	$(CC) $(INCLUDES) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(BIN)/$@

sdl:
	$(shell mkdir -p $(SDL_BIN))
	cmake -S $(SDL_PATH) -B $(SDL_BIN) -DSDL_STATIC=ON -DCMAKE_OSX_ARCHITECTURES="x86_64"
	cd $(SDL_BIN) && make -j 10

sdl_mixer:
	$(shell mkdir -p $(SDL_MIXER_BIN))
	cmake -S $(SDL_MIXER_PATH) -B $(SDL_MIXER_BIN) -DCMAKE_OSX_ARCHITECTURES="x86_64" -DCMAKE_PREFIX_PATH=$(shell pwd)/bin/lib/sdl
	cd $(SDL_MIXER_BIN) && make -j 10

all: sdl sdl_mixer timeco

install:
	cp $(BIN)/timeco $(BIN)/$(GAME)
	cp $(SDL_BIN)/libSDL3.0.dylib $(BIN)/$(GAME)
	cp $(SDL_BIN)/libSDL3.dylib $(BIN)/$(GAME)
	cp $(SDL_BIN)/libSDL3.a $(BIN)/$(GAME)
	cp $(SDL_MIXER_BIN)/libSDL3_mixer.dylib $(BIN)/$(GAME)
	cp $(SDL_MIXER_BIN)/libSDL3_mixer.0.dylib $(BIN)/$(GAME)
	cp $(SDL_MIXER_BIN)/libSDL3_mixer.0.0.0.dylib $(BIN)/$(GAME)

run: install
	cd $(BIN)/$(GAME) && ./timeco

clean-all:
	find bin ! -name 'src' ! -name 'util' -type d -maxdepth 1 -mindepth 1 -exec rm -rf {} +

clean:
	rm -f $(BIN)/timeco
