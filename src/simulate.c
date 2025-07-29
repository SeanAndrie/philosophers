/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:43:43 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/29 20:41:27 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	set_death_flag(t_table *table)
{
	mutex_gate(&table->mutexes.death_lock, LOCK, "death");
	table->death_flag = true;
	mutex_gate(&table->mutexes.death_lock, UNLOCK, "death");
}

static void	wait_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_philo)
		pthread_join(table->philos[i++]->thread, NULL);
}

void *philosopher_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		core_usleep(philo->table->time_to_eat_ms * 0.7);
	while (simulation_active(philo->table))
	{
		philo_think(philo);
		if (!simulation_active(philo->table))
			break;
		philo_eat(philo);
		if (!simulation_active(philo->table))
			break;
		philo_sleep(philo);
	}
	return (NULL);
}

static void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	core_usleep(table->time_to_eat_ms * 0.3);
	while (true)
	{
		if (!check_philosopher_state(table))
			return (set_death_flag(table), NULL);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	size_t		i;
	pthread_t	monitor;

	i = -1;
	table->start_time = get_current_time();
	while (++i < table->n_philo)
	{
		if (!create_thread(&table->philos[i]->thread, philosopher_routine,
				table->philos[i], "philosopher"))
		{
			set_death_flag(table);
			while (i-- > 0)
				pthread_join(table->philos[i]->thread, NULL);
			return (0);
		}
	}
	if (!create_thread(&monitor, monitor_routine, table, "monitor"))
	{
		set_death_flag(table);
		wait_philosophers(table);
		return (0);
	}
	pthread_join(monitor, NULL);
	wait_philosophers(table);
	return (1);
}
