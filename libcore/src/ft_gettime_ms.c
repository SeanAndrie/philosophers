/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettime_ms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:31:59 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 11:37:29 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcore.h"

long    ft_gettime_ms()
{
    struct timeval tv;

    if (!gettimeofday(&tv, NULL))
        return (tv.tv_usec / 1000);
    return (-1);
}
