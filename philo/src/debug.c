/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:29:04 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/11 18:55:19 by sgadinga         ###   ########.fr       */
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

void	log_status(t_philo *philo, const char *action, const char *color)
{
	time_t	elapsed;

	elapsed = get_current_time() - philo->table->start_time;
	mutex_gate(&philo->table->mutexes.log_lock, LOCK, "write");
	if (color)
		printf("%s%ld %u %s%s\n", color, elapsed, philo->id, action, ANSI_RESET);		
	else
		printf("%ld %u %s\n", elapsed, philo->id, action);
	mutex_gate(&philo->table->mutexes.log_lock, UNLOCK, "write");
}
