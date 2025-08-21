/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 01:52:05 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/21 15:59:41 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	log_fork_status(t_philo *philo, t_fork *fork, int fork_index,
		t_fork_status status)
{
	t_table	*table;
	time_t	elapsed;
	time_t	hold_time;

	table = philo->table;
	elapsed = get_current_time() - table->start_time;
	mutex_gate(&table->mutexes.log_lock, LOCK, "fork_log");
	printf("%ld %u", elapsed, philo->id);
	if (status == FORK_ACQUIRED)
		printf(" acquired fork %d (used #: %lu)\n", fork_index,
			fork->times_used);
	else if (status == FORK_RELEASED)
	{
		hold_time = elapsed - fork->hold_start_ms;
		printf(" released fork %d (held for %ldms | total: %ldms)\n",
			fork_index, hold_time, fork->total_time_held_ms);
	}
	mutex_gate(&table->mutexes.log_lock, UNLOCK, "fork_log");
}

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
	if (!simulation_active(philo->table))
		return (mutex_gate(&fork->mutex, UNLOCK, "fork"), 0);
	if (fork->is_taken)
	{
		mutex_gate(&fork->mutex, UNLOCK, "fork");
		return (0);
	}
	fork->is_taken = true;
	fork->times_used++;
	fork->hold_start_ms = elapsed;
	fork->owner_id = philo->id;
	if (VERBOSE)
		log_fork_status(philo, fork, fork_index, FORK_ACQUIRED);
	else
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
