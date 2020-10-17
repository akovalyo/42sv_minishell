# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 21:26:34 by akovalyo          #+#    #+#              #
#    Updated: 2020/10/16 17:46:42 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -c
SRCS_DIR = srcs
OBJS_DIR = objs
INCL_DIR = includes
SRC = 	ft_arraylen.c \
		ft_atof.c \
		ft_atoi.c \
		ft_atoi_base.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_ftoa.c \
		ft_ftoa_long.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_itoa_long.c \
		ft_itoa_uns.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstprint_str.c \
		ft_lstsize.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_nbrlen.c \
		ft_printf.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_realloc.c \
		ft_straddchr.c \
		ft_straddchr_free.c \
		ft_strarr_free.c \
		ft_strarr_print.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strchr_ind.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strcspn.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoin_free.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnequ_alpha.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strsplit_lst.c \
		ft_strsplit_space.c \
		ft_strspn.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c \
		pf_analyse.c \
		pf_asterisk.c \
		pf_checker.c \
		pf_get_c.c \
		pf_get_di.c \
		pf_get_p.c \
		pf_get_s.c \
		pf_get_u.c \
		pf_get_x.c \
		pf_helpers.c \
		pf_print.c \

SRCS = ${addprefix ${SRCS_DIR}/, ${SRC}}
OBJS = $(addprefix $(OBJS_DIR)/,$(notdir $(patsubst %.c,%.o,$(SRCS))))

TOTAL = $(shell find srcs -iname  "*.c" | wc -l | bc)
TOTAL_D := $(shell echo $(TOTAL)/10 | bc)
COUNT = 0
END  = 0

define status
	$(eval COUNT := $(shell find objs -iname "*.o" 2> /dev/null | wc -l | bc))
	$(eval COUNT_D := $(shell echo $(COUNT)/10 | bc))
	printf "\r\033[0;32m"
	printf "█%.0s" $(shell seq 0 $(COUNT_D))
	printf "%s%%" $(shell awk "BEGIN {printf \"%.0f\n\", $(COUNT)/$(TOTAL) * 100}")
	$(eval END := $(shell echo $(TOTAL_D) - $(COUNT_D) + 12 | bc))
	printf "%$(END)s" "  Compiling libft...       "
	printf "\r\033[0m"
endef

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "\033[0;32m\rlibft compiled                       "
	@printf "\r\033[0m"
	@echo

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@gcc $(FLAGS) -I $(INCL_DIR) $<  -o $@
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
