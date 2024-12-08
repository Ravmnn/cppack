# TODO: add release and debug folders; update symlink to release

MAKEFLAGS += -j4

SOURCE_PATH = src
BUILD_PATH = build
OBJECT_PATH = $(BUILD_PATH)/obj

DEPS_PATH = deps


CC = clang++
CPPVERSION = -std=c++17
WARNING_FLAGS =
OPTMIZATION_FLAGS =
INCLUDES = -I $(DEPS_PATH) -I $(SOURCE_PATH)


# debug / release
MODE = debug

ifeq ($(MODE),debug)

	WARNING_FLAGS = -Wall -Wextra
	OPTMIZATION_FLAGS = -Og

else ifeq ($(MODE),release)

	WARNING_FLAGS = -w
	OPTMIZATION_FLAGS = -O3 -flto

endif

CFLAGS = $(WARNING_FLAGS) $(OPTMIZATION_FLAGS) $(INCLUDES) $(CPPVERSION)



SOURCES = $(shell find $(SOURCE_PATH) -name "*.cpp")
OBJECTS = $(addprefix $(OBJECT_PATH)/, $(patsubst $(SOURCE_PATH)/%, %, $(SOURCES:.cpp=.o)))


APP_NAME = cppack
APP_PATH = $(BUILD_PATH)/$(APP_NAME)



.PHONY: all clean



all build: $(APP_PATH)



run: all
	@ echo Running $(APP_NAME)
	@ $(APP_PATH)



$(APP_PATH): $(OBJECTS)
	@ echo Linking executable file at $(APP_PATH)
	@ $(CC) $(OBJECTS) -o $(APP_PATH) $(CFLAGS)


$(OBJECTS): $(OBJECT_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	@ echo Compiling $<
	@ mkdir $(dir $@) -p
	@ $(CC) -c $< -o $@ $(CFLAGS)



clean:
	@ echo Removing $(BUILD_PATH)
	@ rm $(BUILD_PATH) -r -f
