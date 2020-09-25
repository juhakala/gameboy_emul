NAME = gameboy

RED := $(shell tput -Txterm setaf 1)
GREEN := $(shell tput -Txterm setaf 2)

RESET := $(shell tput -Txterm sgr0)

SRC = main.c initial_setup.c hexdumps.c \
	read.c mbc_read_write.c lcd.c timer.c interrupts.c

OPS = not_done.c nop.c \
	ld.c jr.c jp.c and_xor.c inc_dec.c call_push_pop_ret.c cp_and_or.c add_sub.c adc_sbc.c misc.c \
	bit_cb.c rlc_rrc_cb.c res_set_cb.c


OBJ_S = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_O = $(addprefix $(OBJ_DIR)/, $(OPS:.c=.o))

SRC_DIR = src
OPS_DIR = ops
OBJ_DIR = obj
H_DIR = include
DEP_S = $(OBJ_S:%.o=%.d)
DEP_O = $(OBJ_O:%.o=%.d)

L_SDL = `$(SDL_DIR)/sdl2-config --cflags --libs`
SDL_DIR = SDL2-2.0.12
SDL_INC_DIR = SDL2-2.0.12/include
SDL_TAR = SDL2-2.0.12.tar.gz

GCC = gcc #-Wall -Wextra -Werror

all: $(NAME)

-include $(DEP_S)
-include $(DEP_O)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(GCC) -MMD -o $@ -c $< -I $(H_DIR)

$(OBJ_DIR)/%.o : $(OPS_DIR)/%.c
	$(GCC) -MMD -o $@ -c $< -I $(H_DIR)

$(NAME): $(OBJ_S) $(OBJ_O)
	@$(GCC) -o $@ $^ -I $(H_DIR) -I $(SDL_INC_DIR) $(L_SDL)
	@echo "	${GREEN}$(NAME) compiled!${RESET}"
	@$(MAKE) logo1

$(OBJ_S): | $(OBJ_DIR)

$(OBJ_DIR): | $(SDL_DIR)
	mkdir $@

$(SDL_DIR):
	tar -xvf $(SDL_TAR)
	cd $(SDL_DIR) && ./configure --prefix=`pwd`/lib
	make -C $(SDL_DIR)
	make -C $(SDL_DIR) install

clean:
ifeq (,$(wildcard $(NAME)))
else
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)
	@$(MAKE) logo2
endif

fclean: clean
	bash del.sh

delete:
	rm -rf $(SDL_DIR)

re: fclean all

logo1:
	@echo "${RED}              ▄               ${RESET}"
	@echo "${RED}     ‴   █▄░  ██░ ▄████▄░  ‴  ${RESET}"
	@echo "${RED}         ██░  ██░ ██░         ${RESET}"
	@echo "${RED}        ███████░ █████░       ${RESET}"
	@echo "${RED}         ██░  ██░ ██░         ${RESET}"
	@echo "${RED}         ██░  ▀█░ █▀░ ▪       ${RESET}"
	@echo "${RED}         ▀            ▫       ${RESET}"


logo2:
	@echo "${RED}           ▄▄██▄     ░░                     ▄▄██▄               ${RESET}"
	@echo "${RED}          ███░ ██░    ██▄░▄██░             ███░ ██░ ▄████▄░     ${RESET}"
	@echo "${RED}          ██░ ▄█▀░   ░█░█▄█ █░             ██░ ▄█▀░ ██░         ${RESET}"
	@echo "${RED}         ████▄▀      ▄█  █░ █▄      ▄▄▀▀  ████▄▀   █████░       ${RESET}"
	@echo "${RED}          ██░ ▀█▄░  ▄█▀     ▀█░            ██░ ▀█▄░ ██░         ${RESET}"
	@echo "${RED}          ██░  ▀█░  ▀░░     ░█             ██░  ▀█░ █▀░ ▪       ${RESET}"
	@echo "${RED}          ▀                  ░             ▀                    ${RESET}"
