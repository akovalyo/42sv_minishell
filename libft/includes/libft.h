/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 18:00:42 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 16:43:06 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "printf.h"
# define BUFF_SIZE 32

typedef enum		e_comm
{
	VOID, ECHO, PWD, CD, EXPORT, UNSET, ENV, NOCOMM, SH
}					t_comm;

typedef enum		e_ctg
{
	SP = 1, FLAG, STR, SN_QT, DB_QT, GR_SIGN,
	LESS_SIGN, DB_GR_SIGN, COMM, PIPE
}					t_ctg;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	t_ctg			ctg;
	t_comm			comm;
	int				atr;
	struct s_list	*next;
}					t_list;

/*
** Part 1 - Libc functions
*/

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** Part 2 - Additional functions
*/

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s1, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** Bonus part
*/

void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);

/*
** Personal functions
*/

size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_nbrlen(long n);
size_t				ft_strspn(const char *s, const char *accept);
size_t				ft_strcspn(const char *s, const char *reject);
void				ft_lstadd_back(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstprint_str(t_list *lst);
t_list				*ft_strsplit_lst(char const *s, char c);
char				*rest_text(char *ptr_rest, char **ptr_endl);
int					new_line(const int fd, char **line, char *ptr_rest,
							char **ptr_endl);
t_list				*new_elem(const int fd);
int					get_next_line(const int fd, char **line);
char				*ft_itoa_uns(size_t nbr);
char				*ft_itoa_long(long nbr);
char				*ft_straddchr(char *str, char ch);
char				*ft_straddchr_free(char *str, char ch);
char				*signific_handler(long double nbr, int precis,
										int *increment);
char				*ft_ftoa_long(long double nbr, int precis, int sign);
char				*ft_ftoa(double nbr, int precis);
int					ft_strchr_ind(const char *s, char c);
size_t				ft_arraylen(void **arr);
float				ft_atof(char *nptr);
int					ft_atoi_base(char *str, char *base);
void				*ft_realloc(void *ptr, size_t n);
int					ft_isspace(int c);
char				**ft_strsplit_space(char const *s);
void				ft_strarr_free(char **arr);
int					ft_strnequ_alpha(const char *s1, const char *s2, size_t n);
char				*ft_strjoin_free(char *s1, char *s2);
void				ft_strarr_print(char **arr);

#endif
