/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:00:21 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/15 13:41:28 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	cleanup_on_exit(t_philo *philo, int exit_code)
{
	close_semaphores(&philo->table->semaphores);
	exit(exit_code);
}

void	unlink_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/log_sem");
	sem_unlink("/meal_sem");
	sem_unlink("/full_sem");
	sem_unlink("/death_sem");
	sem_unlink("/queue_sem");
}

void	close_semaphores(t_semaphores *sem)
{
	sem_close(sem->forks);
	sem_close(sem->log_sem);
	sem_close(sem->meal_sem);
	sem_close(sem->full_sem);
	sem_close(sem->death_sem);
	sem_close(sem->queue_sem);
}

void	free_table(t_table *table)
{
	t_semaphores	*sem;

	if (!table)
		return ;
	sem = &table->semaphores;
	if (sem->sem_initialized)
	{
		close_semaphores(sem);
		if (getpid() == table->parent_pid)
			unlink_semaphores();
	}
	if (getpid() == table->parent_pid && table->pids)
	{
		kill_processes(table, table->n_philo);
		wait_philosophers(table);
	}
	if (table->pids)
		free(table->pids);
	if (table->philos)
		free(table->philos);
	free(table);
}
