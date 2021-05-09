BUILD_DIR 	= bin/
CC        	= g++
CFLAGS    	= -fPIC -Wall -Werror -Ibase64/src -Ibase64/include
LDFLAGS     = -shared
LIB       	= libbase64
STATIC    	= $(BUILD_DIR)$(LIB).a
SHARED_LIB  = $(BUILD_DIR)$(LIB).so
SRC         = $(wildcard base64/src/*.cpp)
OBJ         = $(SRC:.cpp=.o)

all: $(STATIC) $(SHARED_LIB)

$(SHARED_LIB): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(addprefix $(BUILD_DIR), $(notdir $^))

$(STATIC): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(addprefix $(BUILD_DIR), $(notdir $^))

%.o: %.cpp build
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)$(notdir $@) $<

build:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -fr $(BUILD_DIR)*