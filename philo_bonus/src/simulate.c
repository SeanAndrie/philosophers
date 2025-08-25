/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:20:43 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/25 21:52:04 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	*monitor_self(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (philo_starved(philo))
			break ;
	}
	return (NULL);
}

static void	philosopher_routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (pthread_create(&philo->monitor, NULL, monitor_self, philo) != 0)
		cleanup_on_exit(philo, EXIT_FAILURE);
	while (true)
	{
		log_status(philo, "is thinking", NULL);
		if (!philo_eat(philo))
			break ;
		log_status(philo, "is sleeping", NULL);
		core_usleep(table->time_to_sleep_ms);
	}
	if (pthread_join(philo->monitor, NULL) != 0)
		cleanup_on_exit(philo, EXIT_FAILURE);
	cleanup_on_exit(philo, EXIT_SUCCESS);
}

static void	*meal_watcher(void *arg)
{
	size_t	i;
	t_table	*table;

	i = 0;
	table = (t_table *)arg;
	while (i < table->n_philo)
	{
		sem_wait(table->semaphores.full_sem);
		i++;
	}
	sem_post(table->semaphores.death_sem);
	return (NULL);
}

static void	*monitor_routine(void *arg)
{
	t_table		*table;
	pthread_t	meals_thread;

	table = (t_table *)arg;
	if (table->max_meals)
	{
		if (pthread_create(&meals_thread, NULL, meal_watcher,
				(void *)table) != 0)
			return (NULL);
		pthread_detach(meals_thread);
	}
	sem_wait(table->semaphores.death_sem);
	kill_processes(table, table->n_philo);
	return (NULL);
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
	if (pthread_create(&table->monitor, NULL, monitor_routine,
			(void *)table) != 0)
		return (0);
	wait_philosophers(table);
	if (pthread_join(table->monitor, NULL) != 0)
		return (0);
	return (1);
}
