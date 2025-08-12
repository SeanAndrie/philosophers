/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:55:25 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/12 22:18:29 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	check_philosopher(t_philo *philo, bool *ate_enough)
{
	bool	died;
	t_table	*table;
	time_t	elapsed;

	died = false;
	table = philo->table;
	elapsed = get_current_time() - table->start_time;
	mutex_gate(&table->mutexes.meal_lock, LOCK, "meal");
	if ((elapsed - philo->last_meal_ms) > table->time_to_die_ms)
	{
		set_death_flag(table);
		log_status(philo, "died");
		died = true;
	}
	if (table->max_meals && philo->meals_eaten >= table->max_meals)
		*ate_enough = true;
	mutex_gate(&table->mutexes.meal_lock, UNLOCK, "meal");
	return (died);
}

bool	philo_dead_or_philos_full(t_table *table)
{
	size_t	i;
	size_t	full_count;
	bool	ate_enough;

	i = 0;
	full_count = 0;
	if (!simulation_active(table))
		return (true);
	while (i < table->n_philo)
	{
		ate_enough = false;
		if (check_philosopher(table->philos[i], &ate_enough))
			return (true);
		if (ate_enough)
			full_count++;
		i++;
	}
	if (table->max_meals > 0 && full_count == table->n_philo)
		return (set_death_flag(table), true);
	return (false);
}

bool	simulation_active(t_table *table)
{
	bool	active;

	mutex_gate(&table->mutexes.death_lock, LOCK, "death");
	active = !table->death_flag;
	mutex_gate(&table->mutexes.death_lock, UNLOCK, "death");
	return (active);
}

bool	single_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->n_philo != 1)
		return (false);
	if (!mutex_gate(&table->mutexes.forks[philo->left_fork], LOCK, "fork"))
		return (true);
	log_status(philo, "has taken a fork");
	core_usleep(table->time_to_die_ms);
	mutex_gate(&table->mutexes.forks[philo->right_fork], UNLOCK, "fork");
	return (true);
}
