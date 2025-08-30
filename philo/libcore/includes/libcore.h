/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcore.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:57:16 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/30 08:55:14 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCORE_H
# define LIBCORE_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define EXIT_NONE -1
# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

bool	core_isdigit(int c);
bool	core_isspace(int c);
bool	core_isalpha(int c);

int		core_tolower(int c);
int		core_min(int a, int b);
int		core_max(int a, int b);
int     core_strncmp(const char *s1, const char *s2, size_t n);

long	core_strtol(const char *nptr, char **endptr, int base);

void	core_putnbr_fd(int n, int fd);
void	core_putstr_fd(const char *str, int fd);
void	core_putendl_fd(const char *str, int fd);

time_t	get_current_time(void);
void	core_usleep(time_t milliseconds);
void	fatal_error(const char *context, const char *message, int exit_code);

#endif
