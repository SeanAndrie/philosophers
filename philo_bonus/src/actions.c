/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:23:51 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/15 14:23:53 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

bool	philo_starved(t_philo *philo)
{
	t_table	*table;
	time_t	elapsed;
	bool	starved;

	starved = false;
	table = philo->table;
	sem_wait(table->semaphores.meal_sem);
	elapsed = get_current_time() - table->start_time;
	if ((elapsed - philo->last_meal_ms) > table->time_to_die_ms)
	{
		sem_post(table->semaphores.death_sem);
		log_status(philo, "died", ANSI_RED);
		starved = true;
	}
	sem_post(table->semaphores.meal_sem);
	return (starved);
}

static bool	single_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->n_philo != 1)
		return (false);
	sem_wait(table->semaphores.forks);
	log_status(philo, "has taken a fork", NULL);
	sem_post(table->semaphores.forks);
	core_usleep(table->time_to_die_ms);
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (single_philo(philo))
		return (false);
	sem_wait(table->semaphores.queue_sem);
	sem_wait(table->semaphores.forks);
	log_status(philo, "has taken a fork", NULL);
	sem_wait(table->semaphores.forks);
	log_status(philo, "has taken a fork", NULL);
	sem_wait(table->semaphores.meal_sem);
	philo->last_meal_ms = get_current_time() - table->start_time;
	philo->meals_eaten++;
	if (table->max_meals && philo->meals_eaten == table->max_meals)
		sem_post(table->semaphores.full_sem);
	sem_post(table->semaphores.meal_sem);
	log_status(philo, "is eating", ANSI_GREEN);
	core_usleep(table->time_to_eat_ms);
	sem_post(table->semaphores.forks);
	sem_post(table->semaphores.forks);
	sem_post(table->semaphores.queue_sem);
	return (true);
}

void	log_status(t_philo *philo, const char *action, const char *color)
{
	time_t	elapsed;

	sem_wait(philo->table->semaphores.log_sem);
	elapsed = get_current_time() - philo->table->start_time;
	if (color)
		printf("%s%ld %u %s%s\n", color, elapsed, philo->id, action, ANSI_RESET);
	else
		printf("%ld %u %s\n", elapsed, philo->id, action);
	sem_post(philo->table->semaphores.log_sem);
}
