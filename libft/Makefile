# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 21:26:34 by akovalyo          #+#    #+#              #
#    Updated: 2020/10/09 16:56:20 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -c
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(addprefix objs/,$(notdir $(patsubst %.c,%.o,$(SRCS))))

TOTAL = $(shell find srcs -iname  "*.c" | wc -l | bc)
TOTAL_D := $(shell echo $(TOTAL)/10 | bc)
RES = 0
COUNT = 0
END  = 0
define status
	$(eval COUNT := $(shell find objs -iname "*.o" 2> /dev/null | wc -l | bc))
	$(eval COUNT_D := $(shell echo $(COUNT)/10 | bc))
	$(eval RES := $(shell echo ${TOTAL_D} - ${COUNT_D} | bc))
	printf "\r\033[0;32m"
	printf "█%.0s" $(shell seq 0 ${COUNT_D})
	printf $(COUNT)
	$(eval END := $(shell echo ${TOTAL_D} - ${COUNT_D} + 12 | bc))
	printf "%$(END)s" "  Compiling libft... files:${TOTAL}"
endef

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "\033[0;32m\rlibft compiled                              \033[0m"
	@echo

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p objs
	@gcc $(FLAGS) $< -I ./includes -o $@
	@$(call status)

clean:
	@rm -rf $(OBJS_DIR)


fclean: clean 
	@rm -f $(NAME)

re: fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) includes/libft.h includes/printf.h

memory:
	@gcc -g -o test main.c -L. -lft -I ./includes
	@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./test
	@rm test
	@gcc -g -fsanitize=address -o test main.c -L. -lft -I ./includes
	@./test
	@rm test

test:
	@clang -o test main.c -L. -lft -I ./includes
	@./test
	@rm test

debug:
	@gcc -g -o test main.c -L. -lft -I ./includes
