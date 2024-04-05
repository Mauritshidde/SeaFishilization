TARGET ?= game.exe
SRC_DIRS ?= ./src
CC = x86_64-w64-mingw32-g++

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRCS))) $(patsubst %.c,%.o,$(filter %.c,$(SRCS))) $(patsubst %.s,%.o,$(filter %.s,$(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
LDFLAGS := -static -L/usr/local/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -luser32 -lshell32 -lpsapi

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
