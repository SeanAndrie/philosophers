/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:52:29 by sgadinga          #+#    #+#             */
/*   Updated: 2025/09/02 16:41:42 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	philo_starved(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (is_dead(table->philos[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	philos_are_full(t_table *table)
{
	bool	full;

	full = false;
	mutex_gate(&table->mutexes.meal_lock, LOCK, "meal");
	if (table->max_meals && table->full_count == table->n_philo)
		full = true;
	mutex_gate(&table->mutexes.meal_lock, UNLOCK, "meal");
	if (full)
		set_death_flag(table);
	return (full);
}

int	philo_think(t_philo *philo)
{
	if (!simulation_active(philo->table))
		return (0);
	log_status(philo, "is thinking", NULL);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (!simulation_active(philo->table))
		return (0);
	log_status(philo, "is sleeping", NULL);
	core_usleep(philo->table->time_to_sleep_ms);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (!simulation_active(table))
		return (0);
	if (!pickup_forks(philo))
		return (0);
	if (!mutex_gate(&table->mutexes.meal_lock, LOCK, "meal"))
		return (0);
	philo->last_meal_ms = get_current_time() - table->start_time;
	philo->meals_eaten++;
	if (table->max_meals && philo->meals_eaten == table->max_meals)
		table->full_count++;
	if (!mutex_gate(&table->mutexes.meal_lock, UNLOCK, "meal"))
		return (0);
	log_status(philo, "is eating", ANSI_GREEN);
	core_usleep(table->time_to_eat_ms);
	if (!putdown_forks(philo))
		return (0);
	return (1);
}
