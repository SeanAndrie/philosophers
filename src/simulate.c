/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:43:43 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/30 10:24:04 by sgadinga         ###   ########.fr       */
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

static void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		core_usleep(philo->table->time_to_eat_ms / 2);
	while (simulation_active(philo->table))
	{
		if (!philo_think(philo) || !philo_eat(philo) || !philo_sleep(philo))
			break ;
	}
	return (NULL);
}

static void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (true)
	{
		core_usleep(5);
		if (!check_philosopher_state(table))
		{
			set_death_flag(table);
			break ;
		}
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
