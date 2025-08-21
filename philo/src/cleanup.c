/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:34:38 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/21 17:08:36 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	wait_philosophers(t_table *table, int n_philo)
{
	while (--n_philo >= 0)
		pthread_join(table->philos[n_philo]->thread, NULL);
}

void	free_forks(t_fork *forks, size_t count)
{
	size_t	i;

	if (!forks)
		return ;
	i = 0;
	while (i < count)
		destroy_mutex(&forks[i++].mutex, "fork");
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
	if (VERBOSE)
		print_fork_statistics(table);
	if (table->mutexes.locks_initialized)
		free_mutexes(table->mutexes, table->n_philo);
	free(table);
}
