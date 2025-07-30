/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_usleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:03:29 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/30 09:03:35 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcore.h>

void	core_usleep(time_t milliseconds)
{
	time_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
}
