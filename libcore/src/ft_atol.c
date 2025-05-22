/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:46:52 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 02:54:55 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcore.h"

static long	check_overflow(long long res, int digit, int sign)
{
	if (res > (LONG_MAX / 10) || (res == (LONG_MAX / 10) && (digit - '0') > 7))
	{
		if (sign == 1)
			return (LONG_MAX);
		else if (sign == -1)
			return (LONG_MIN);
	}
	return (0);
}

long	ft_atol(const char *s)
{
	long long	res;
	long		sign;
	long		overflow;

	res = 0;
	sign = 1;
	overflow = 0;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && (*s >= '0' && *s <= '9'))
	{
		overflow = check_overflow(res, *s, sign);
		if (overflow != 0)
			return (overflow);
		res = res * 10 + *s++ - '0';
	}
	return ((long)res * sign);
}
