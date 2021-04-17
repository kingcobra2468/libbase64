BUILD_DIR = bin/
CC        = g++
CFLAGS    = -Wall -Werror -Ibase64/src -Ibase64/include
LIB       = base64
STATIC    = $(BUILD_DIR)$(LIB).a
SRC       = $(wildcard base64/src/*.cpp)
OBJ       = $(SRC:.cpp=.o)

all: $(STATIC)
	
$(STATIC): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(addprefix $(BUILD_DIR), $(notdir $^))

%.o: %.cpp build
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)$(notdir $@) $<

build:
	mkdir -p $(BUILD_DIR)

clean:
	rm -fr $(BUILD_DIR)*