CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra
LDFLAGS  := -L "C:\libsdl\lib" -lSDL2main -lSDL2 -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := program
INCLUDE  := -I "C:\libsdl\include"
SRC      :=                      \
   $(wildcard src/Visual/*.cpp) \
   $(wildcard src/Math/*.cpp) \
   $(wildcard src/*.cpp)         \

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES \
         := $(OBJECTS:.o=.d)
LIB_FOLDER \
		 := Math
LIB_FILE \
		 := file 


all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info new clean

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"

run: $(APP_DIR)/$(TARGET)
	$(APP_DIR)/$(TARGET)

new:
	@if [ -z "$(LIB_FOLDER)" ] || [ -z "$(LIB_FILE)" ]; then \
		echo "Error: Must specify 'LIB_FOLDER' y 'LIB_FILE'. Example: make new LIB_FOLDER=Visual LIB_FILE=Render"; \
	else \
		mkdir -p include/$(LIB_FOLDER); \
		mkdir -p src/$(LIB_FOLDER); \
		echo "#ifndef $(LIB_FILE)_HPP" > include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "#define $(LIB_FILE)_HPP" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "class $(LIB_FILE) {" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "public:" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "    $(LIB_FILE)();" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "    ~$(LIB_FILE)();" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "};" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "#endif // $(LIB_FILE)_HPP" >> include/$(LIB_FOLDER)/$(LIB_FILE).hpp; \
		echo "#include \"../../include/$(LIB_FOLDER)/$(LIB_FILE).hpp\"" > src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "" >> src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "$(LIB_FILE)::$(LIB_FILE)() {" >> src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "    // Constructor" >> src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "}" >> src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "" >> src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "$(LIB_FILE)::~$(LIB_FILE)() {" >> src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "    // Destructor" >> src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "}" >> src/$(LIB_FOLDER)/$(LIB_FILE).cpp; \
		echo "Files added: include/$(LIB_FOLDER)/$(LIB_FILE).hpp & src/$(LIB_FOLDER)/$(LIB_FILE).cpp"; \
	fi
