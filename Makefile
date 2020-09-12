NAME = gameboy

SRC = main.c initial_setup.c hexdumps.c \
	read.c mbc_read_write.c

OPS = not_done.c nop.c \
	ld.c jr.c xor.c bit_cb.c inc_dec.c


OBJ_S = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_O = $(addprefix $(OBJ_DIR)/, $(OPS:.c=.o))

SRC_DIR = src
OPS_DIR = ops
OBJ_DIR = obj
H_DIR = include
DEP_S = $(OBJ_S:%.o=%.d)
DEP_O = $(OBJ_O:%.o=%.d)

GCC = gcc #-Wall -Wextra -Werror

all: $(NAME)

-include $(DEP_S)
-include $(DEP_O)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(GCC) -MMD -o $@ -c $< -I $(H_DIR)

$(OBJ_DIR)/%.o : $(OPS_DIR)/%.c
	$(GCC) -MMD -o $@ -c $< -I $(H_DIR)

$(NAME): $(OBJ_S) $(OBJ_O) 
	$(GCC) -o $@ $^ -I $(H_DIR)

$(OBJ_S): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)
