/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:08:22 by sgadinga          #+#    #+#             */
/*   Updated: 2025/09/02 19:16:50 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <libcore.h>
# include <pthread.h>

# define PHILO_USAGE \
	"<n_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [max_meals]"

# define ANSI_RED "\e[0;31m"
# define ANSI_GREEN "\e[0;32m"
# define ANSI_RESET "\e[0m"

# define VERBOSE false

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

typedef enum e_fork_status
{
	FORK_ACQUIRED,
	FORK_RELEASED
}						t_fork_status;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	bool				is_taken;
	int					owner_id;
	unsigned long		times_used;
	time_t				hold_time_ms;
	time_t				hold_start_ms;
	time_t				total_time_held_ms;
}						t_fork;

typedef struct s_mutexes
{
	t_fork				*forks;
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
	unsigned int		full_count;
	bool				death_flag;
	time_t				start_time;
	time_t				time_to_die_ms;
	time_t				time_to_eat_ms;
	time_t				time_to_sleep_ms;
}						t_table;

// Parsing
int						parse_arguments(int argc, char **argv, t_table *table);

// Actions
int						philo_think(t_philo *philo);
int						philo_sleep(t_philo *philo);
int						philo_eat(t_philo *philo);
bool					philo_starved(t_table *table);
bool					philos_are_full(t_table *table);

// Fork Acquisition
int						pickup_forks(t_philo *philo);
int						putdown_forks(t_philo *philo);

// Cleanup
void					free_table(t_table *table);
void					free_mutexes(t_mutexes mutexes, int n_philo);
void					free_forks(t_fork *forks, size_t count);
void					wait_philosophers(t_table *table, int n_philo);

// Debugging
void					print_fork_statistics(t_table *table);
void					log_status(t_philo *philo, const char *action,
							const char *color);
void					log_fork_status(t_philo *philo, t_fork *fork,
							int fork_index, t_fork_status status);

// Resource Initialization
t_table					*set_table(int argc, char **argv);

// Synchronization Mech. Wrappers
int						destroy_mutex(pthread_mutex_t *mutex,
							const char *context);
int						initialize_mutex(pthread_mutex_t *mutex,
							const char *context);
int						create_thread(pthread_t *thread, void *routine(void *),
							void *arg, const char *context);
int						mutex_gate(pthread_mutex_t *mutex, t_lock_action action,
							char *context);

// Simulation
int						start_simulation(t_table *table);
void					set_death_flag(t_table *table);
bool					simulation_active(t_table *table);

// Simulation Utilities
bool					is_dead(t_philo *philo);
bool					single_philo(t_philo *philo);

#endif
