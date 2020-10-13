# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 11:47:21 by akovalyo          #+#    #+#              #
#    Updated: 2020/10/12 17:37:39 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRCS_DIR = srcs
LIBFT_DIR = libft
LIBFT_INCL = libft/includes
INCL = includes
SRCS = $(wildcard $(SRCS_DIR)/*.c)

$(NAME): 
	@make -C $(LIBFT_DIR) re
	@gcc $(FLAGS) $(SRCS) -o $(NAME) -L $(LIBFT_DIR) -lft -I $(LIBFT_INCL) -I $(INCL)
	@echo "\033[1;35m\rminishell is ready\033[0m"

all: $(NAME)

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

