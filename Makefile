# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 11:47:21 by akovalyo          #+#    #+#              #
#    Updated: 2020/10/16 10:24:43 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
LIBFT_DIR = libft
LIBFT_INCL = libft/includes
INCL = includes
SRC = 	addtoken_1.c \
		addtoken_2.c \
		builtins.c \
		builtin_cd.c \
		builtin_envmanage.c \
		builtins.c \
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
		utils_cd.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))

all: $(NAME)

$(NAME): 
	@make -C $(LIBFT_DIR) re
	@gcc $(FLAGS) $(SRCS) -o $(NAME) -L $(LIBFT_DIR) -lft -I $(LIBFT_INCL) -I $(INCL)
	@echo "\033[1;35m\rminishell is ready\033[0m"

clean:
	@make -C $(LIBFT_DIR) clean

fclean: clean 
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

test:
	gcc -g $(SRCS) -o $(NAME) -L $(LIBFT_DIR) -lft -I $(LIBFT_INCL) -I $(INCL)

mem:
	gcc -g -fsanitize=address -fno-omit-frame-pointer $(SRCS) -o $(NAME) -L libft/ -lft -I $(LIBFT_INCL) -I $(INCL)

norm: 
	@make -C libft norm
	@norminette -R CheckForbiddenSourceHeader $(SRCS) 

