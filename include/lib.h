/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:53:44 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/03 20:57:14 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
// macros

# define BUFFER_SIZE 69

// HEADERS

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

// Forward declarations
typedef struct s_shell	t_shell;

// prototypes str_man1.c

int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);

// prototypes str_man2.c

size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
char					*ft_itoa(int n);
void					ft_putstr_fd(char *s, int fd);

// prototypes str_man3.c

char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					**ft_split(char const *s, char c);

// prototypes str_man4.c

char					*ft_strchr(const char *s, int c);
int						ft_strcmp(char *s1, char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strjoin(char *s1, char *s2);
bool					is_space(char ch);

// get_next_line

char					*get_next_line(int fd);

// test functions
void					run_exp_tests(t_shell *shell);

#endif