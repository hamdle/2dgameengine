################################################################################
# Variable definitions
################################################################################
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = src/*.cpp \
			src/*/*.cpp
LINKER_FLAGS_PIE = -lSDL2 \
				   -lSDL2_image \
				   -lSDL2_ttf \
				   -lSDL2_mixer \
				   -llua5.3
LINKER_FLAGS_FEDORA = -lSDL2 \
					  -lSDL2_image \
					  -lSDL2_ttf \
					  -lSDL2_mixer \
					  -llua
OBJ_NAME = gameengine

################################################################################
# Makefile rules
################################################################################
pie:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS_PIE) -o $(OBJ_NAME)

r:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS_PIE) -o $(OBJ_NAME)

fedora:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS_FEDORA) -o $(OBJ_NAME)

f:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS_FEDORA) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

run-w:
	./$(OBJ_NAME) -w

clean:
	rm $(OBJ_NAME)
