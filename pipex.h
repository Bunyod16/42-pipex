#ifndef PIPEX_H
#define PIPEX_H

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(const char *s, char c);
char	*ft_strdup(const char *s1);
char	**process_path(char *str, char *ag);
void		free_pp(char **str);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

#endif