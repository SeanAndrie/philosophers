/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcore.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:57:16 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/24 22:42:20 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCORE_H
# define LIBCORE_H

# include <errno.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

int		core_isdigit(int c);
int		core_isspace(int c);
int		core_isalpha(int c);
int		core_tolower(int c);

long	core_strtol(const char *nptr, char **endptr, int base);
    
void	core_putstr_fd(const char *str, int fd);
void	core_putendl_fd(const char *str, int fd);

void	exit_on_error(const char *context, const char *message, int exit_code);

#endif
