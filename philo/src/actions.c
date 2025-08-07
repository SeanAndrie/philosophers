/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:52:29 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/31 14:19:30 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	pickup_forks(t_philo *philo)
{
	int		first;
	int		second;
	t_table	*table;

	table = philo->table;
	if (single_philo(philo))
		return (0);
	first = core_min(philo->left_fork, philo->right_fork);
	second = core_max(philo->left_fork, philo->right_fork);
	if (!mutex_gate(&table->mutexes.forks[first], LOCK, "fork"))
		return (0);
	if (!mutex_gate(&table->mutexes.forks[second], LOCK, "fork"))
	{
		mutex_gate(&table->mutexes.forks[first], UNLOCK, "fork");
		return (0);
	}
	if (!simulation_active(table))
	{
		mutex_gate(&table->mutexes.forks[first], UNLOCK, "fork");
		mutex_gate(&table->mutexes.forks[second], UNLOCK, "fork");
		return (0);
	}
	log_status(philo, "has taken a fork");
	log_status(philo, "has taken a fork");
	return (1);
}

static int	putdown_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (!mutex_gate(&table->mutexes.forks[philo->right_fork], UNLOCK, "fork"))
		return (0);
	if (!mutex_gate(&table->mutexes.forks[philo->left_fork], UNLOCK, "fork"))
		return (0);
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (!simulation_active(philo->table))
		return (0);
	log_status(philo, "is thinking");
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (!simulation_active(philo->table))
		return (0);
	log_status(philo, "is sleeping");
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
	if (!mutex_gate(&table->mutexes.meal_lock, UNLOCK, "meal"))
		return (0);
	log_status(philo, "is eating");
	core_usleep(table->time_to_eat_ms);
	if (!putdown_forks(philo))
		return (0);
	return (1);
}
