/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:34:38 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/29 13:14:04 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_forks(pthread_mutex_t *forks, size_t count)
{
	size_t	i;

	if (!forks)
		return ;
	i = 0;
	while (i < count)
		destroy_mutex(&forks[i++], "fork");
	free(forks);
}

void	free_mutexes(t_mutexes mutexes, int n_philo)
{
	if (mutexes.forks)
	{
		free_forks(mutexes.forks, n_philo);
		mutexes.forks = NULL;
	}
	destroy_mutex(&mutexes.log_lock, "log");
	destroy_mutex(&mutexes.meal_lock, "meal");
	destroy_mutex(&mutexes.death_lock, "death");
}

void	free_table(t_table *table)
{
	if (!table)
		return ;
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	if (table->mutexes.locks_initialized)
		free_mutexes(table->mutexes, table->n_philo);
	free(table);
}
