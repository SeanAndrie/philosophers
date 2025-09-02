/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 01:52:05 by sgadinga          #+#    #+#             */
/*   Updated: 2025/09/02 19:35:02 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	putdown_fork(t_philo *philo, t_fork *fork, int fork_index)
{
	t_table	*table;
	time_t	hold_time;
	time_t	elapsed;

	table = philo->table;
	elapsed = get_current_time() - table->start_time;
	hold_time = elapsed - fork->hold_start_ms;
	fork->total_time_held_ms += hold_time;
	fork->owner_id = 0;
	fork->is_taken = false;
	if (VERBOSE)
		log_fork_status(philo, fork, fork_index, FORK_RELEASED);
	if (!mutex_gate(&fork->mutex, UNLOCK, "fork"))
		return (0);
	return (1);
}

static int	pickup_fork(t_philo *philo, t_fork *fork, int fork_index)
{
	time_t	elapsed;

	elapsed = get_current_time() - philo->table->start_time;
	if (!mutex_gate(&fork->mutex, LOCK, "fork"))
		return (0);
	if (fork->owner_id != -1
		&& fork->total_time_held_ms > (philo->table->time_to_eat_ms / 2)
		&& fork->is_taken)
	{
		mutex_gate(&fork->mutex, UNLOCK, "fork");
		return (usleep(philo->table->time_to_eat_ms * 1000 / 10), 0);
	}
	if (!simulation_active(philo->table) || fork->is_taken)
	{
		mutex_gate(&fork->mutex, UNLOCK, "fork");
		return (0);
	}
	fork->is_taken = true;
	fork->times_used++;
	fork->hold_start_ms = elapsed;
	fork->owner_id = philo->id;
	if (VERBOSE)
		return (log_fork_status(philo, fork, fork_index, FORK_ACQUIRED), 1);
	log_status(philo, "has taken a fork", NULL);
	return (1);
}

int	putdown_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (!putdown_fork(philo, &table->mutexes.forks[philo->right_fork],
			philo->right_fork))
		return (0);
	if (!putdown_fork(philo, &table->mutexes.forks[philo->left_fork],
			philo->left_fork))
		return (0);
	return (1);
}

int	pickup_forks(t_philo *philo)
{
	int		first;
	int		second;
	t_table	*table;

	table = philo->table;
	if (single_philo(philo))
		return (0);
	first = core_min(philo->left_fork, philo->right_fork);
	second = core_max(philo->left_fork, philo->right_fork);
	if (!pickup_fork(philo, &table->mutexes.forks[first], first))
		return (0);
	if (!pickup_fork(philo, &table->mutexes.forks[second], second))
	{
		putdown_fork(philo, &table->mutexes.forks[first], first);
		return (0);
	}
	return (1);
}
