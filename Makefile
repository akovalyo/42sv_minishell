# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/31 11:47:21 by akovalyo          #+#    #+#              #
#    Updated: 2020/09/24 12:47:20 by alex             ###   ########.fr        #
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
		utils.c

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
	clang -g -fsanitize=address -fno-omit-frame-pointer $(SRCS) -o $(NAME) -L libft/ -lft -I libft/includes/ -I includes/

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(INCL)*.h $(LIBFT_DIR)*.c $(LIBFT_INCL)*.h

endif