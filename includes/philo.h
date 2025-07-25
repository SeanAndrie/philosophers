/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:08:22 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/24 23:44:36 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <libcore.h>
#include <pthread.h>

// typedef struct s_shared
// {
    
// }               t_shared;

typedef struct s_table
{
    int         n_philos;
    int         n_times_to_eat;
    long        time_to_die_ms;
    long        time_to_eat_ms;
    long        time_to_sleep_ms;
}               t_table;

// Debugging Functions
void    print_args(char **av);

int is_valid_params(int n_params, char **params);

#endif
