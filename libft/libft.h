/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:44:50 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/11 04:20:15 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "garbage_collector.h"
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
	int				a;
}					t_list;

int					ft_isalpha(int a);
int					ft_isdigit(int a);
int					ft_isalnum(int a);
int					ft_isascii(int a);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isspace(char c);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
int					ft_atoi(const char *str);
int					ft_lstsize(t_list *lst);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(char *src, int c);
char				*ft_strnstr(const char *big, const char *small, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dest_str, const char *src_str, size_t n);
size_t				ft_strlcat(char *dest_str, const char *src_str, size_t n);
void				*ft_memset(void *str, int c, size_t n);
void				ft_bzero(void *str, size_t n);
void				*ft_memcpy(void *dest_str, const void *src_str, size_t n);
void				*ft_memmove(void *dest_str, const void *src_str, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
void				*ft_calloc(size_t num, size_t size);
char				*ft_strdup(const char *str);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_printf(const char *format, ...);
int					ft_putstr(char *x);
char				*ft_itoa_2(int n);
int					ft_px(unsigned long p);
int					ft_bx(unsigned int nbr);
int					ft_ux(unsigned int nbr);
int					ft_sx(unsigned int nrb);
int					ft_putchar(char x);
char				*get_next_line(int fd);
char				*ft_strjoin_gnl(char const *s1, char const *s2);

#endif
