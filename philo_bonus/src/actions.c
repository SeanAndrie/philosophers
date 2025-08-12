/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:23:51 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/12 22:28:44 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

bool	philos_are_full(t_table *table)
{
	int	completed_meals;

	sem_getvalue(table->semaphores.full_sem, &completed_meals);
	if (table->max_meals && completed_meals == (int)table->n_philo)
		return (true);
	return (false);
}

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
		log_status(philo, "died");
		starved = true;
	}
	sem_post(table->semaphores.meal_sem);
	return (starved);
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
	if (single_philo(philo))
		return (0);
	sem_wait(table->semaphores.queue_sem);
	sem_wait(table->semaphores.forks);
	log_status(philo, "has taken a fork");
	sem_wait(table->semaphores.forks);
	log_status(philo, "has taken a fork");
	sem_wait(table->semaphores.meal_sem);
	philo->last_meal_ms = get_current_time() - table->start_time;
	philo->meals_eaten++;
	if (table->max_meals && philo->meals_eaten == table->max_meals)
		sem_post(table->semaphores.full_sem);
	sem_post(table->semaphores.meal_sem);
	log_status(philo, "is eating");
	core_usleep(table->time_to_eat_ms);
	sem_post(table->semaphores.forks);
	sem_post(table->semaphores.forks);
	sem_post(table->semaphores.queue_sem);
	return (1);
}
