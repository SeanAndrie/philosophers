/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:55:25 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/25 21:53:21 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	is_dead(t_philo *philo)
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
		log_status(philo, "died", ANSI_RED);
		set_death_flag(table);
		died = true;
	}
	mutex_gate(&table->mutexes.meal_lock, UNLOCK, "meal");
	return (died);
}

bool	single_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->n_philo != 1)
		return (false);
	if (!mutex_gate(&table->mutexes.forks[philo->left_fork].mutex, LOCK,
			"fork"))
		return (true);
	log_status(philo, "has taken a fork", NULL);
	core_usleep(table->time_to_die_ms);
	mutex_gate(&table->mutexes.forks[philo->left_fork].mutex, UNLOCK, "fork");
	return (true);
}
