/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_putstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:06:43 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/24 16:17:14 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcore.h>

void	core_putstr_fd(const char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}
