/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:08:22 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/11 18:55:29 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <libcore.h>
# include <pthread.h>

# define PHILO_USAGE "<n_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [max_meals]"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef enum e_arg_type
{
	TYPE_UINT,
	TYPE_TIME
}						t_arg_type;

typedef enum e_lock_action
{
	LOCK,
	UNLOCK
}						t_lock_action;

typedef struct s_arg_desc
{
	const char			*name;
	t_arg_type			type;
	void				*target;
	int					max_value;
}						t_arg_desc;

typedef struct s_mutexes
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		log_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		death_lock;
	bool				locks_initialized;
}						t_mutexes;

typedef struct s_philo
{
	unsigned int		id;
	pthread_t			thread;
	t_table				*table;
	int					left_fork;
	int					right_fork;
	unsigned int		meals_eaten;
	time_t				last_meal_ms;
}						t_philo;

typedef struct s_table
{
	unsigned int		n_philo;
	t_mutexes			mutexes;
	t_philo				**philos;
	unsigned int		max_meals;
	bool				death_flag;
	time_t				start_time;
	time_t				time_to_die_ms;
	time_t				time_to_eat_ms;
	time_t				time_to_sleep_ms;
}						t_table;

// Parsing
int						parse_arguments(int argc, char **argv, t_table *table);

// Philosopher Actions
int						philo_think(t_philo *philo);
int						philo_sleep(t_philo *philo);
int						philo_eat(t_philo *philo);

// Cleanup Functions
void					free_table(t_table *table);
void					free_forks(pthread_mutex_t *forks, size_t count);

// Debugging Functions
void					print_table_parameters(t_table *table);
void					print_philo_params(t_philo **philos, size_t n_philo);
void					log_status(t_philo *philo, const char *action);

// Resource Initialization
t_table					*set_table(int argc, char **argv);

// Synchronization Mech. Function Wrappers
int						destroy_mutex(pthread_mutex_t *mutex,
							const char *context);
int						initialize_mutex(pthread_mutex_t *mutex,
							const char *context);
int						create_thread(pthread_t *thread, void *routine(void *),
							void *arg, const char *context);
int						mutex_gate(pthread_mutex_t *mutex, t_lock_action action,
							char *context);

// Simulation Functions
int						start_simulation(t_table *table);

// Simulation Utilities
bool					single_philo(t_philo *philo);
void					set_death_flag(t_table *table);
bool					simulation_active(t_table *table);
bool					philo_dead_or_philos_full(t_table *table);

#endif
