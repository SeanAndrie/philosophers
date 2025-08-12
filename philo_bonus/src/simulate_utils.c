/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:00:09 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/12 22:27:40 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	log_status(t_philo *philo, const char *action)
{
	time_t	elapsed;

	sem_wait(philo->table->semaphores.log_sem);
	elapsed = get_current_time() - philo->table->start_time;
	printf("%ld %u %s\n", elapsed, philo->id, action);
	sem_post(philo->table->semaphores.log_sem);
}

bool	simulation_active(t_table *table)
{
	int	value;

	sem_getvalue(table->semaphores.death_sem, &value);
	return (value == 0);
}

bool	single_philo(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	if (table->n_philo != 1)
		return (false);
	sem_wait(table->semaphores.forks);
	log_status(philo, "has taken a fork");
	core_usleep(table->time_to_die_ms);
	sem_post(table->semaphores.forks);
	return (true);	
}
