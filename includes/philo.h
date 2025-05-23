/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:23:17 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 11:55:24 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <libcore.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef EXEC_NAME
# error "EXEC_NAME is not defined."
# else
# define PROG_NAME EXEC_NAME
# endif

# define STDERR 2

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t print_mutex;
	int				n_philos;
	int				sim_stop;
	int				total_meals;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_times_to_eat;
}					t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	struct s_table	*shared;
	long			last_meal;
}					t_philo;

void	error(char *type, char *msg, char *error_code);

// Table Initialization
t_table	*init_table(char **av);

#endif
