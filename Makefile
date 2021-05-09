BUILD_DIR 	= bin/
CC        	= g++
CFLAGS    	= -Wall -Werror -Ibase64/src -Ibase64/include -o2
SO_CFLAGS   = -fPIC
TEST_CFLAGS = -static -Lbin/ -lbase64 -Ilibs/
LDFLAGS     = -shared
LIB       	= libbase64
TEST_LIB    = $(LIB)_tests
STATIC    	= $(BUILD_DIR)$(LIB).a
SHARED_LIB  = $(BUILD_DIR)$(LIB).so
SRC         = $(wildcard base64/src/*.cpp)
TEST_SRC    = $(wildcard tests/*.cpp)
OBJ         = $(SRC:.cpp=.o)

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