# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 11:47:21 by akovalyo          #+#    #+#              #
#    Updated: 2020/10/19 16:28:26 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ****** #
# COLORS #
# ****** #

RED = \033[0;31m
BRED = \033[1;31m
GREEN = \033[0;32m
BGREEN = \033[1;32m
YELLOW = \033[0;33m
BELLOW = \033[1;33m
BLUE = \033[0;34m
BBLUE = \033[01;34m
MAGENTA = \033[0;35m
BMAGENTA = \033[1;35m
CYAN = \033[0;36m
BCYAN = \033[1;36m
RESET = \033[0m

# ********** #
# STATUS BAR #
# ********** #

TOTAL = $(shell find $(SRCS_DIR) -iname  "*.c" | wc -l)
define status
	$(eval COUNT := $(shell find $(OBJS_DIR) -iname "*.o" 2> /dev/null | wc -l))
	$(eval PER := $(shell awk "BEGIN {printf \"%.0f\n\", $(COUNT)/$(TOTAL) * 100}"))
	$(eval SIZE := $(shell awk "BEGIN {printf \"%.0f\n\", $(PER)/10}"))
	printf "\r$(COLOR)"
	printf "█%.0s" $(shell seq 0 $(SIZE))
	printf "%s%%" $(PER)
	$(eval END := $(shell awk "BEGIN {printf \"%.0f\n\", 10 - $(SIZE)}"))
	printf "%$(END)s" "  Compiling libft...           "
	printf "\r$(RESET)"
endef

# ********** #

COLOR = $(MAGENTA)
NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
SRCS_DIR = srcs
LIBFT_DIR = libft
LIBFT_INCL = libft/includes
OBJS_DIR = objs
INCL = includes
LFT = -L libft/ -lft
SRC = 	addtoken_1.c \
		addtoken_2.c \
		builtins.c \
		builtin_cd.c \
		builtin_envmanage.c \
		check_builtins_and_bin.c \
		comm_array.c \
		env.c \
		fd.c \
		init.c \
		main.c \
		memory.c \
		parser.c \
		signal.c \
		utils_1.c \
		utils_2.c \
		utils_addtoken.c \
		utils_cd.c \
		utils_check_bin.c

SRCS = ${addprefix ${SRCS_DIR}/, ${SRC}}
OBJS = $(addprefix $(OBJS_DIR)/,$(notdir $(patsubst %.c,%.o,$(SRCS))))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(FLAGS) -I $(LIBFT_INCL) -I $(INCL) -o $(NAME) $(OBJS) $(LFT)
	@echo "\r$(COLOR)minishell is ready"
	@printf "\r$(RESET)"
	@echo

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I $(LIBFT_INCL) -I $(INCL) -c $< -o $@
	@$(call status)

clean:
	@make -C $(LIBFT_DIR) clean

fclean: clean 
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)

re: fclean all

test: $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(FLAGS) -I $(LIBFT_INCL) -I $(INCL) -o $(NAME) $(OBJS) $(LFT) 

mem: 
	@$(CC) $(FLAGS) -fsanitize=address -fno-omit-frame-pointer -I $(LIBFT_INCL) -I $(INCL) -o $(NAME) $(SRCS) $(LFT) 

valgr:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes 

efence:
	@$(CC) $(FLAGS) -I $(LIBFT_INCL) -I $(INCL) -o $(NAME) $(SRCS) $(LFT) -lefence

norm: 
	@make -C libft norm
	@norminette -R CheckForbiddenSourceHeader $(SRCS) $(INCL)/*.h

.PHONY: clean fclean re test mem norm
