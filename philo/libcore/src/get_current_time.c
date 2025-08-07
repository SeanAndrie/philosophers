/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:03:57 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/30 09:04:02 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcore.h>

time_t	get_current_time(void)
{
	int				err;
	struct timeval	time;

	err = gettimeofday(&time, NULL);
	if (err != 0)
		fatal_error("gettimeofday", strerror(err), EXIT_FAILURE);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
