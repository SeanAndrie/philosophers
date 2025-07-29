/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:52:29 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/29 20:39:23 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_think(t_philo *philo)
{
	log_status(philo, "is thinking", NULL);
	if (philo->id % 2 == 1)
		core_usleep(philo->table->time_to_eat_ms * 0.5);
}

void	philo_sleep(t_philo *philo)
{
	log_status(philo, "is sleeping", NULL);
	core_usleep(philo->table->time_to_sleep_ms);
}

static void pickup_forks(t_philo *philo)
{
    t_table *table;
    
    table = philo->table;
    if (philo->id % 2 == 0)
    {
        philo->left_fork = philo->id - 1;
        philo->right_fork = philo->id % table->n_philo;
    }
    else
    {
        philo->left_fork = philo->id % table->n_philo;
        philo->right_fork = philo->id - 1;
    }
    mutex_gate(&table->mutexes.forks[philo->left_fork], LOCK, "fork");
    log_status(philo, "has taken a fork", NULL);
    mutex_gate(&table->mutexes.forks[philo->right_fork], LOCK, "fork");
    log_status(philo, "has taken a fork", NULL);
}

static void putdown_forks(t_philo *philo)
{
    t_table *table;

    table = philo->table;
    mutex_gate(&table->mutexes.forks[philo->right_fork], UNLOCK, "fork");
    mutex_gate(&table->mutexes.forks[philo->left_fork], UNLOCK, "fork");
}

void philo_eat(t_philo *philo)
{
    t_table *table = philo->table;
    
    if (!simulation_active(table))
        return ;
    pickup_forks(philo);
    mutex_gate(&table->mutexes.meal_lock, LOCK, "meal");
    philo->last_meal_ms = get_current_time() - table->start_time;
    philo->meals_eaten++;
    mutex_gate(&table->mutexes.meal_lock, UNLOCK, "meal");
    log_status(philo, "is eating", NULL);
    core_usleep(table->time_to_eat_ms);
    putdown_forks(philo);
}
