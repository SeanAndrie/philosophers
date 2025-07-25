/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_putendl_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:33:38 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/24 16:18:19 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcore.h>

void	core_putendl_fd(const char *str, int fd)
{
	core_putstr_fd(str, fd);
	write(fd, "\n", 1);
}
