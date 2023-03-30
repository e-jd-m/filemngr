CC = g++
CFLAGS = -Wall -pedantic -g -std=c++17
LDFLAGS = -lstdc++fs

TARGET = flmngr

SOURCE_DIR = src
BUILD_DIR = build

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)
OBJS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all
all: compile doc

.PHONY: compile
compile: $(TARGET)
	@echo "Compile..."

.PHONY: run
run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -c -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

clean:
	-rm -rf $(BUILD_DIR)
	-rm -f $(TARGET)
	-rm -f Makefile.d

Makefile.d: $(SOURCES) $(HEADERS)
	g++ -MM $(SOURCES) > Makefile.d

include Makefile.d
