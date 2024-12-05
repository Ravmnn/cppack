CC = g++
CFLAGS = 
OPTMIZATION_FLAGS =


SOURCE_PATH = src
BUILD_PATH = build
OBJECT_PATH = $(BUILD_PATH)/obj


SOURCES = $(shell find $(SOURCE_PATH) -name "*.cpp")
OBJECTS = $(addprefix $(OBJECT_PATH)/, $(patsubst $(SOURCE_PATH)/%, %, $(SOURCES:.cpp=.o)))


APP_NAME = cppack
APP_PATH = $(BUILD_PATH)/$(APP_NAME)



MODE = debug # debug / release

ifeq ($(MODE), debug)

	CFLAGS = -Wall -Wextra
	OPTMIZATION_FLAGS = -O0

else ifeq($(MODE), release)

	CFLAGS = -w
	OPTMIZATION_FLAGS = -O3 -flto

endif



.PHONY: all clean



all: $(APP_PATH)



run: all
	@ echo Running $(APP_NAME)
	@ $(APP_PATH)



$(APP_PATH): $(OBJECTS)
	@ echo Linking executable file at $(APP_PATH)
	@ $(CC) $(OBJECTS) -o $(APP_PATH) $(CFLAGS) $(OPTMIZATION_FLAGS)


$(OBJECTS): $(OBJECT_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	@ echo Compiling $<
	@ mkdir $(dir $@) -p
	@ $(CC) -c $< -o $@ $(CFLAGS) $(OPTMIZATION_FLAGS)



clean:
	@ echo Removing $(BUILD_PATH)
	@ rm $(BUILD_PATH) -r -f