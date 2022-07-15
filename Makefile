FILES = src/*.cpp src/include/*.cpp
CC = g++
COMPILER_FLAGS = 
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE_FLAGS = -Isrc/include
OUTPUT_DIR = dst
OUTPUT_FILE = desktop
OUTPUT_PATH = $(OUTPUT_DIR)/$(OUTPUT_FILE)

default:
	make build && make run

build: $(FILES)
	$(CC) $(FILES) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_PATH)
run:
	cd $(OUTPUT_DIR);./$(OUTPUT_FILE);cd ..
	# ./$(OUTPUT_PATH)