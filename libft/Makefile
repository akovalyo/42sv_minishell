# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 21:26:34 by akovalyo          #+#    #+#              #
#    Updated: 2020/09/10 17:25:48 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -c
SRC_DIR = srcs/
SRC = ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
      ft_memccpy.c \
      ft_memmove.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_strlen.c \
	  ft_strdup.c \
	  ft_strcpy.c \
	  ft_strncpy.c \
	  ft_strcat.c \
	  ft_strncat.c \
      ft_strlcat.c \
	  ft_strchr.c \
      ft_strrchr.c \
	  ft_strstr.c \
	  ft_strnstr.c \
	  ft_strcmp.c \
	  ft_strncmp.c \
      ft_atoi.c \
      ft_isalpha.c \
      ft_isdigit.c \
      ft_isascii.c \
      ft_isalnum.c \
      ft_isprint.c \
      ft_toupper.c \
      ft_tolower.c \
	  ft_memalloc.c \
	  ft_memdel.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
      ft_strjoin.c \
	  ft_strtrim.c \
      ft_strsplit.c \
      ft_itoa.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putendl.c \
      ft_putnbr.c \
	  ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
	  ft_lstnew.c \
	  ft_lstdelone.c \
	  ft_lstclear.c \
 	  ft_lstadd_front.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_strlcpy.c \
	  ft_calloc.c \
	  ft_nbrlen.c \
	  ft_strspn.c \
	  ft_strcspn.c \
	  ft_lstadd_back.c \
	  ft_lstsize.c \
	  ft_lstlast.c \
	  ft_lstprint_str.c \
	  get_next_line.c \
	  ft_itoa_uns.c\
	  ft_itoa_long.c \
	  ft_straddchr.c \
	  ft_straddchr_free.c \
	  ft_ftoa_long.c \
	  ft_ftoa.c \
	  ft_strchr_ind.c \
	  ft_printf.c \
	  ft_strarraylen.c \
	  ft_atof.c \
	  ft_atoi_base.c \
	  ft_realloc.c \
	  ft_isspace.c \
	  ft_strsplit_space.c \
	  ft_strsplit_lst.c \
	  ft_strtab_free.c \
	  pf_get_c.c \
	  pf_get_s.c \
	  pf_get_di.c \
	  pf_get_u.c \
	  pf_get_p.c \
	  pf_get_x.c \
	  pf_checker.c \
	  pf_analyse.c \
	  pf_helpers.c \
	  pf_print.c \
	  pf_asterisk.c

SRCS = ${addprefix ${SRC_DIR}, ${SRC}}
OBJS = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(SRCS) -I ./includes
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJS)

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

