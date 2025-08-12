/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:20:43 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/12 20:58:51 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	cleanup_on_exit(t_philo *philo, int exit_code)
{
	close_semaphores(&philo->table->semaphores);
	exit(exit_code);
}

static void	*monitor_self(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (simulation_active(table))
	{
		if (philo_starved(philo) || (table->max_meals
				&& philos_are_full(table)))
			exit(1);
	}
	return (NULL);
}

static void	philosopher_routine(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, monitor_self, philo) != 0)
		cleanup_on_exit(philo, EXIT_FAILURE);
	while (simulation_active(philo->table))
	{
		if (!philo_think(philo) || !philo_eat(philo) || !philo_sleep(philo))
			break ;
	}
	if (pthread_join(philo->monitor, NULL) != 0)
		cleanup_on_exit(philo, EXIT_FAILURE);
	cleanup_on_exit(philo, EXIT_SUCCESS);
}

int	start_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	table->start_time = get_current_time();
	while (i < table->n_philo)
	{
		table->pids[i] = fork();
		if (table->pids[i] == 0)
			philosopher_routine(table->philos[i]);
		else if (table->pids[i] == -1)
		{
			kill_processes(table, (int)i);
			wait_philosophers(table);
			return (0);
		}
		i++;
	}
	wait_philosophers(table);
	return (1);
}
