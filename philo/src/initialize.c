/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:42:24 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/30 10:27:58 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	initialize_forks(t_table *table)
{
	size_t	i;

	table->mutexes.forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->mutexes.forks)
		return (fatal_error("table init", "forks: malloc failed", EXIT_NONE),
			0);
	i = -1;
	while (++i < table->n_philo)
	{
		if (!initialize_mutex(&table->mutexes.forks[i], "fork"))
		{
			free_forks(table->mutexes.forks, i);
			table->mutexes.forks = NULL;
			return (0);
		}
	}
	return (1);
}

static int	initialize_mutexes(t_table *table)
{
	table->mutexes.locks_initialized = false;
	if (!initialize_mutex(&table->mutexes.log_lock, "log"))
		return (0);
	if (!initialize_mutex(&table->mutexes.meal_lock, "meal"))
	{
		destroy_mutex(&table->mutexes.log_lock, "log");
		return (0);
	}
	if (!initialize_mutex(&table->mutexes.death_lock, "death"))
	{
		destroy_mutex(&table->mutexes.log_lock, "log");
		destroy_mutex(&table->mutexes.meal_lock, "meal");
		return (0);
	}
	table->mutexes.locks_initialized = true;
	if (!initialize_forks(table))
	{
		destroy_mutex(&table->mutexes.log_lock, "log");
		destroy_mutex(&table->mutexes.meal_lock, "meal");
		destroy_mutex(&table->mutexes.death_lock, "death");
		return (0);
	}
	return (1);
}

static int	initialize_philosophers(t_table *table)
{
	size_t	i;
	size_t	count;
	t_philo	*block;

	count = table->n_philo;
	table->philos = malloc(sizeof(t_philo *) * count + sizeof(t_philo) * count);
	if (!table->philos)
		return (0);
	block = (t_philo *)((char *)table->philos + sizeof(t_philo *) * count);
	i = -1;
	while (++i < count)
	{
		table->philos[i] = &block[i];
		table->philos[i]->id = i + 1;
		table->philos[i]->thread = 0;
		table->philos[i]->table = table;
		table->philos[i]->meals_eaten = 0;
		table->philos[i]->last_meal_ms = 0;
		table->philos[i]->last_action_ms = 0;
		table->philos[i]->left_fork = i;
		table->philos[i]->right_fork = (i + 1) % count;
	}
	return (1);
}

t_table	*set_table(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
	{
		fatal_error("usage", PHILO_USAGE, EXIT_NONE);
		return (NULL);
	}
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(*table));
	if (!parse_arguments(argc, argv, table))
		return (free(table), NULL);
	if (argc == 5)
		table->max_meals = 0;
	if (!initialize_mutexes(table))
		return (free_table(table), NULL);
	if (!initialize_philosophers(table))
		return (free_table(table), NULL);
	table->death_flag = false;
	return (table);
}
