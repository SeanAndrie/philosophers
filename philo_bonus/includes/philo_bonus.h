/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:43:10 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/15 14:19:37 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <libcore.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

# define PHILO_USAGE \
	"<n_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [max_meals]"

# define DEBUG_MODE false

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef enum e_arg_type
{
	TYPE_UINT,
	TYPE_TIME
}						t_arg_type;

typedef struct s_arg_desc
{
	const char			*name;
	t_arg_type			type;
	void				*target;
	int					max_value;
}						t_arg_desc;

typedef struct s_semaphores
{
	sem_t				*forks;
	sem_t				*log_sem;
	sem_t				*meal_sem;
	sem_t				*full_sem;
	sem_t				*death_sem;
	sem_t				*queue_sem;
	bool				sem_initialized;
}						t_semaphores;

typedef struct s_philo
{
	unsigned int		id;
	t_table				*table;
	pthread_t			monitor;
	unsigned int		meals_eaten;
	time_t				last_meal_ms;
}						t_philo;

typedef struct s_table
{
	pid_t				*pids;
	pthread_t			watcher;
	unsigned int		n_philo;
	t_philo				**philos;
	unsigned int		max_meals;
	pid_t				parent_pid;
	t_semaphores		semaphores;
	time_t				start_time;
	time_t				time_to_die_ms;
	time_t				time_to_eat_ms;
	time_t				time_to_sleep_ms;
}						t_table;

// Initialization
t_table					*set_table(int argc, char **argv);

// Parsing
int						parse_arguments(int argc, char **argv, t_table *table);

// Simulation
int						start_simulation(t_table *table);

// Simuation Utilities
void					wait_philosophers(t_table *table);
void					kill_processes(t_table *table, int n_proc);

// Philosopher Actions
bool					philo_eat(t_philo *philo);
bool					philo_starved(t_philo *philo);
void					log_status(t_philo *philo, const char *action);

// Cleanup
void					unlink_semaphores(void);
void					free_table(t_table *table);
void					close_semaphores(t_semaphores *sem);
void					cleanup_on_exit(t_philo *philo, int exit_code);

#endif
