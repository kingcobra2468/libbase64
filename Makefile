BUILD_DIR   = bin/
CC          = g++
CFLAGS      = -Wall -Werror -Iinclude -o2
SO_CFLAGS   = -fPIC
TEST_CFLAGS = -static -Lbin/ -lbase64 -Ilib/
LDFLAGS     = -shared
LIB         = libbase64
TEST_LIB    = $(LIB)_tests
STATIC      = $(BUILD_DIR)$(LIB).a
SHARED_LIB  = $(BUILD_DIR)$(LIB).so
SRC         = $(wildcard src/*.cpp)
TEST_SRC    = $(wildcard test/*.cpp)
OBJ         = $(SRC:.cpp=.o)

.PHONY: all
all: $(STATIC) $(SHARED_LIB)

$(SHARED_LIB): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(addprefix $(BUILD_DIR), $(notdir $^))

$(STATIC): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(addprefix $(BUILD_DIR), $(notdir $^))

%.o: %.cpp build
	$(CC) $(CFLAGS) $(SO_CFLAGS) -c -o $(BUILD_DIR)$(notdir $@) $<

build:
	mkdir -p $(BUILD_DIR)

test: $(STATIC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o  $(BUILD_DIR)$(TEST_LIB) $(TEST_CFLAGS)

.PHONY: clean
clean:
	rm -fr $(BUILD_DIR)*