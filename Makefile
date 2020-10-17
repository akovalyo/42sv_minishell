# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 11:47:21 by akovalyo          #+#    #+#              #
#    Updated: 2020/10/17 16:57:56 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror
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

TOTAL = $(shell find srcs -iname  "*.c" | wc -l | bc)
TOTAL_D := $(shell echo $(TOTAL)/10 | bc)
COUNT = 0
END  = 0

define status
	$(eval COUNT := $(shell find objs -iname "*.o" 2> /dev/null | wc -l | bc))
	$(eval COUNT_D := $(shell echo $(COUNT)/2 | bc))
	printf "\r\033[1;35m"
	printf "█%.0s" $(shell seq 0 $(COUNT_D))
	printf "%s%%" $(shell awk "BEGIN {printf \"%.0f\n\", $(COUNT)/$(TOTAL) * 100}")
	$(eval END := $(shell echo $(TOTAL_D) - $(COUNT_D) + 12 | bc))
	printf "%$(END)s" "  Compiling minishell...  "
	printf "\r\033[0m"
endef

all: $(NAME)

$(NAME): $(OBJS) $(INCL)
	@make -C $(LIBFT_DIR)
	@$(CC) $(FLAGS) -I $(LIBFT_INCL) -I $(INCL) -o $(NAME) $(OBJS) $(LFT)
	@echo "\033[1;35m\rminishell is ready\033[0m"

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

test: $(OBJS) $(INCL)
	@make -C $(LIBFT_DIR)
	@$(CC) $(FLAGS) -I $(LIBFT_INCL) -I $(INCL) -o $(NAME) $(OBJS) $(LFT) 

mem: 
	@$(CC) $(FLAGS) -g -fsanitize=address -fno-omit-frame-pointer -I $(LIBFT_INCL) -I $(INCL) -o $(NAME) $(SRCS) $(LFT) 

valgr:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes 

efence:
	@$(CC) $(FLAGS) -g -I $(LIBFT_INCL) -I $(INCL) -o $(NAME) $(SRCS) $(LFT) -lefence

norm: 
	@make -C libft norm
	@norminette -R CheckForbiddenSourceHeader $(SRCS) $(INCL)/*.h

.PHONY: clean fclean re test mem norm
