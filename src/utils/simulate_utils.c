/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:55:25 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/30 08:59:12 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	check_philosopher(t_table *table, size_t index, bool *ate_enough)
{
	time_t	current_time;

	current_time = get_current_time() - table->start_time;
	mutex_gate(&table->mutexes.meal_lock, LOCK, "meal");
	if ((current_time
			- table->philos[index]->last_meal_ms) > table->time_to_die_ms)
	{
		mutex_gate(&table->mutexes.meal_lock, UNLOCK, "meal");
		set_death_flag(table);
		log_status(table->philos[index], "died", ANSI_RED);
		return (true);
	}
	if (table->max_meals
		&& table->philos[index]->meals_eaten < table->max_meals)
		*ate_enough = false;
	mutex_gate(&table->mutexes.meal_lock, UNLOCK, "meal");
	return (false);
}

bool	check_philosopher_state(t_table *table)
{
	size_t	i;
	bool	ate_enough;

	i = -1;
	ate_enough = true;
	if (!simulation_active(table))
		return (false);
	while (++i < table->n_philo)
	{
		if (check_philosopher(table, i, &ate_enough))
			break ;
	}
	if (table->max_meals > 0 && ate_enough)
		return (false);
	return (true);
}

bool	simulation_active(t_table *table)
{
	bool	active;

	mutex_gate(&table->mutexes.death_lock, LOCK, "death");
	active = !table->death_flag;
	mutex_gate(&table->mutexes.death_lock, UNLOCK, "death");
	return (active);
}
