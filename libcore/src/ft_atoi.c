/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:45:12 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 02:52:10 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcore.h"

static int check_overflow(int res, char digit, int sign)
{
    if (res > (INT_MAX / 10) || (res == (INT_MAX / 10) && (digit - '0') > 7))
    {
        if (sign == 1)
            return (INT_MAX);
        else if (sign == -1)
            return (INT_MIN);
    }
    return (0);
}

int ft_atoi(const char *s)
{
    long res;
    int sign;
    int overflow;

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
    return ((int)res * sign);
}
