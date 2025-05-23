/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:37:17 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 12:01:57 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutexes(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!table->forks)
		error("Table initialization", "Failed to allocate memory for forks.",
			NULL);
	pthread_mutex_init(&table->stop_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	i = 0;
	while (i < table->n_philos)
		pthread_mutex_init(&table->forks[i++], NULL);
}

t_table	*init_table(char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->sim_stop = 0;
	table->start_time = ft_gettime_ms();
	table->n_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->n_times_to_eat = -1;
	if (av[5])
		table->n_times_to_eat = ft_atoi(av[5]);
	init_mutexes(table);
	return (table);
}
