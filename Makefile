
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
AR = ar rcs
NAME = libmx.a
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

EXEC = pathfinder
EXEC_SRC = src/main.c
EXEC_OBJ = $(OBJ_DIR)/$(EXEC).o

all: $(NAME) $(EXEC)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(EXEC_OBJ) $(NAME)
	$(CC) $(CFLAGS) -o $(EXEC) $(EXEC_OBJ) -L. -lmx

$(EXEC_OBJ): $(EXEC_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(NAME) $(EXEC)

re: clean all

.PHONY: all clean re
