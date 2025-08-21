/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:16:21 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/21 18:50:55 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	initialize_semaphores(t_table *table)
{
	t_semaphores	*sem;

	unlink_semaphores();
	sem = &table->semaphores;
	sem->sem_initialized = false;
	sem->log_sem = sem_open("/log_sem", O_CREAT, 0644, 1);
	sem->meal_sem = sem_open("/meal_sem", O_CREAT, 0644, 1);
	sem->full_sem = sem_open("/full_sem", O_CREAT, 0644, 0);
	sem->death_sem = sem_open("/death_sem", O_CREAT, 0644, 0);
	sem->death_log_sem = sem_open("/death_log_sem", O_CREAT, 0644, 1);
	sem->queue_sem = sem_open("/queue_sem", O_CREAT, 0644, table->n_philo - 1);
	sem->forks = sem_open("/forks", O_CREAT, 0644, table->n_philo);
	if (sem->log_sem == SEM_FAILED || sem->meal_sem == SEM_FAILED
		|| sem->full_sem == SEM_FAILED || sem->death_sem == SEM_FAILED
		|| sem->queue_sem == SEM_FAILED || sem->forks == SEM_FAILED
		|| sem->death_log_sem == SEM_FAILED)
	{
		close_semaphores(sem);
		unlink_semaphores();
		return (0);
	}
	sem->sem_initialized = true;
	return (1);
}

static int	initialize_philos_and_pids(t_table *table)
{
	size_t	i;
	size_t	count;
	t_philo	*block;

	count = table->n_philo;
	table->philos = malloc(sizeof(t_philo *) * count + sizeof(t_philo) * count);
	if (!table->philos)
		return (0);
	table->pids = malloc(sizeof(pid_t) * table->n_philo);
	if (!table->pids)
		return (free(table->philos), 0);
	block = (t_philo *)((char *)table->philos + sizeof(t_philo *) * count);
	i = 0;
	while (i < table->n_philo)
	{
		table->pids[i] = -1;
		table->philos[i] = &block[i];
		table->philos[i]->id = i + 1;
		table->philos[i]->table = table;
		table->philos[i]->meals_eaten = 0;
		table->philos[i]->last_meal_ms = 0;
		i++;
	}
	return (1);
}

t_table	*set_table(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		fatal_error("usage", PHILO_USAGE, EXIT_FAILURE);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	if (!parse_arguments(argc, argv, table))
		return (free(table), NULL);
	if (argc == 5)
		table->max_meals = 0;
	if (!initialize_semaphores(table))
		return (free(table), NULL);
	if (!initialize_philos_and_pids(table))
		return (free_table(table), NULL);
	table->parent_pid = getpid();
	return (table);
}
