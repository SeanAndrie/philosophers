/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcore.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:47:44 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 03:07:30 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCORE_H
# define LIBCORE_H

# include <limits.h>
# include <unistd.h>

int     ft_atoi(const char *s);
long	ft_atol(const char *s);

void    ft_putstr_fd(const char *s, int fd);

#endif
