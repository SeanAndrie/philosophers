/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:43:43 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/21 12:02:58 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	set_death_flag(t_table *table)
{
	mutex_gate(&table->mutexes.death_lock, LOCK, "death");
	table->death_flag = true;
	mutex_gate(&table->mutexes.death_lock, UNLOCK, "death");
}

bool	simulation_active(t_table *table)
{
	bool	active;

	mutex_gate(&table->mutexes.death_lock, LOCK, "death");
	active = !table->death_flag;
	mutex_gate(&table->mutexes.death_lock, UNLOCK, "death");
	return (active);
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (simulation_active(table))
	{
		if (table->max_meals && philo->meals_eaten == table->max_meals)
			break ;
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
		if (philos_are_full(table))
			break ;
		if (philo_starved(table))
			break ;
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	size_t		i;
	pthread_t	monitor;

	i = 0;
	table->start_time = get_current_time();
	while (i < table->n_philo)
	{
		if (!create_thread(&table->philos[i]->thread, philosopher_routine,
				table->philos[i], "philosopher"))
		{
			set_death_flag(table);
			wait_philosophers(table, i);
			return (0);
		}
		i++;
	}
	if (!create_thread(&monitor, monitor_routine, table, "monitor"))
	{
		set_death_flag(table);
		wait_philosophers(table, table->n_philo);
		return (0);
	}
	pthread_join(monitor, NULL);
	wait_philosophers(table, table->n_philo);
	return (1);
}
