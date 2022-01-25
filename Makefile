CC = gcc

EXTRA_FLAGS = -pedantic

LIBS = utils dirtraversal argparse
LIB_OBJECTS = $(addprefix $(BUILD_DIR)$(LIB_SUB_DIR), $(LIBS:=.o))
LIB_TESTS = $(addprefix $(BUILD_DIR), $(LIBS:=_test))


SRC_DIR = src/
TEST_SRC_DIR = src/unittests/

BUILD_DIR = build/
LIB_SUB_DIR = libs/


MAIN = main.c
EXEC_NAME = zls

all : main tests

main : $(LIB_OBJECTS) 
	$(CC) $(EXTRA_FLAGS) $(SRC_DIR)$(MAIN) $(LIB_OBJECTS) -o $(BUILD_DIR)$(EXEC_NAME)

tests : $(LIB_TESTS)

$(BUILD_DIR)%_test : $(BUILD_DIR)$(LIB_SUB_DIR)%.o
	mkdir -p $(@D)
	$(CC) $(EXTRA_FLAGS) $(LIB_OBJECTS) $(TEST_SRC_DIR)$(notdir $@).c -o $@

$(BUILD_DIR)$(LIB_SUB_DIR)%.o : $(SRC_DIR)%.c 
	mkdir -p $(@D)
	$(CC) $(EXTRA_FLAGS) $< -c -o $@

clean:
	rm -r build || true
