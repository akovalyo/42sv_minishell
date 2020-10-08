# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 11:47:21 by akovalyo          #+#    #+#              #
#    Updated: 2020/10/07 18:53:19 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror -c
SRCS_DIR = srcs/
LIBFT_DIR = libft/
LIBFT_INCL = libft/includes/
INCL = includes/

SRC = main.c \
		signal.c \
		utils_1.c \
		utils_2.c \
		utils_cd.c \
		memory.c \
		env.c \
		parser.c \
		addnode_1.c \
		addnode_2.c \
		builtins.c \
		builtin_cd.c \
		builtin_envmanage.c \
		fd.c

SRCS = ${addprefix ${SRCS_DIR}, ${SRC}}

OBJF = $(SRC:%.c=%.o)

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all
%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif


$(NAME): 
	@make -C $(LIBFT_DIR) re

all: $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJF)

fclean: clean 
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

test:
	gcc -g $(SRCS) -o $(NAME) -L libft/ -lft -I libft/includes/ -I includes/

mem:
	gcc -g -fsanitize=address -fno-omit-frame-pointer $(SRCS) -o $(NAME) -L libft/ -lft -I libft/includes/ -I includes/

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(INCL)*.h $(LIBFT_DIR)*.c $(LIBFT_INCL)*.h

endif