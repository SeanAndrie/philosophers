/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcore.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:57:16 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/29 20:23:12 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCORE_H
# define LIBCORE_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2
# define EXIT_NONE -1

bool    core_isdigit(int c);
bool	core_isspace(int c);
bool    core_isalpha(int c);

int		core_tolower(int c);
int     core_usleep(size_t milliseconds);

long	core_strtol(const char *nptr, char **endptr, int base);

void    core_putnbr_fd(int n, int fd);
void	core_putstr_fd(const char *str, int fd);
void	core_putendl_fd(const char *str, int fd);

void	fatal_error(const char *context, const char *message, int exit_code);
time_t  get_current_time(void);

#endif
