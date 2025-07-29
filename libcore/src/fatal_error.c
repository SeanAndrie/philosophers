/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:01:32 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/28 15:34:43 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcore.h>

void	fatal_error(const char *context, const char *message, int exit_code)
{
	core_putstr_fd("philo: ", STDERR_FILENO);
	if (context)
	{
		core_putstr_fd(context, STDERR_FILENO);
		core_putstr_fd(": ", STDERR_FILENO);		
	}
	core_putendl_fd(message, STDERR_FILENO);
	if (exit_code >= 0)
		exit(exit_code);
}
