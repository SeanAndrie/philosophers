/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_usleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:39:39 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/29 20:41:52 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcore.h>

int core_usleep(size_t milliseconds)
{
    size_t  start;

    start = get_current_time();
    while ((get_current_time() - start) < milliseconds)
        usleep(100);
    return (0);
}
