/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:29:04 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/07 15:23:26 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_table_parameters(t_table *table)
{
	printf("\nNumber of Philosophers: %u\n", table->n_philo);
	printf("Time to die (ms): %ld\n", table->time_to_die_ms);
	printf("Time to eat (ms): %ld\n", table->time_to_eat_ms);
	printf("Time to sleep (ms): %ld\n", table->time_to_sleep_ms);
	printf("Number of Meals: %u\n\n", table->max_meals);
}

void	print_philo_params(t_philo **philos, size_t n_philo)
{
	size_t	i;

	i = 0;
	while (i < n_philo)
	{
		printf("philo id: %u\n", philos[i]->id);
		printf("\tmeals_eaten: %u\n", philos[i]->meals_eaten);
		printf("\tlast_meal_ms: %ld\n\n", philos[i]->last_meal_ms);
		i++;
	}
}

void	log_status(t_philo *philo, const char *action)
{
	time_t	now;
	time_t	elapsed;
	time_t	since_last_action;
	time_t	since_last_meal;

	now = get_current_time();
	elapsed = now - philo->table->start_time;
	since_last_action = now - philo->last_action_ms;
	since_last_meal = now - philo->last_meal_ms;
	mutex_gate(&philo->table->mutexes.log_lock, LOCK, "write");
	printf("%ld %u %s", elapsed, philo->id, action);
	if (DEBUG_MODE)
		printf(" [+%ldms since last action, +%ldms since last meal]",
			since_last_action, since_last_meal);
	printf("\n");
	mutex_gate(&philo->table->mutexes.log_lock, UNLOCK, "write");
	philo->last_action_ms = now;
}
