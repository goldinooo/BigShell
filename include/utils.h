#ifndef UTILS_H
#define UTILS_H

// macros

#define BUFFER_SIZE 69

// HEADERS

#include <unistd.h>
#include <stdlib.h>

// prototypes str_man1.c

int	ft_atoi(const char *str);
int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isalnum(int c);

// prototypes str_man2.c

size_t 	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);

// prototypes str_man3.c

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

// prototypes str_man3.c

char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);

// get_next_line

char	*get_next_line(int fd);

#endif