NAME = gameboy

RED := $(shell tput -Txterm setaf 1)
GREEN := $(shell tput -Txterm setaf 2)

RESET := $(shell tput -Txterm sgr0)

SRC = main.c initial_setup.c hexdumps.c \
	read.c mbc_read_write.c

OPS = not_done.c nop.c \
	ld.c jr.c xor.c inc_dec.c call_push_pop_ret.c cp_and_or.c misc.c \
	bit_cb.c rlc_rrc_cb.c


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
	@$(GCC) -o $@ $^ -I $(H_DIR)
	@echo "	${GREEN}$(NAME) compiled!${RESET}"
	@$(MAKE) logo

$(OBJ_S): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)

logo:
	@echo "${RED}              ▄               ${RESET}"
	@echo "${RED}     ‴   █▄░  ██░ ▄█████░  ‴ ${RESET}"
	@echo "${RED}         ██░  ██░ ██░        ${RESET}"
	@echo "${RED}        ███████░ █████░      ${RESET}"
	@echo "${RED}         ██░  ██░ ██░        ${RESET}"
	@echo "${RED}         ██░  ▀█░ ██░ ▪      ${RESET}"
	@echo "${RED}         ▀            ▫      ${RESET}"
