/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:42:24 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/24 23:48:28 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int is_valid_integer(const char *str, int *out_val)
{
    long    value;
    char    *end;
    
    errno = 0;
    value = core_strtol(str, &end, 10);
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN)
        return (0);
    if (str == end || *end != '\0')
        return (0);
    *out_val = value;
    return (1);
}

int is_valid_params(int n_params, char **params)
{
    int value;

    while (n_params--)
    {
        if (is_valid_integer(*params, &value))
        {
            if (value <= 0)
                return (0);
        }
        else
            return (0);
        params++;
    }
    return (1);
}

// t_table *init_table(char **av)
// {
//     t_table *tabl
// }
