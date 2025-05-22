/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:23:17 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 03:06:28 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <libcore.h>
# include <pthread.h>
# include <stdio.h> // FOR TESTING, REMOVE LATER
# include <stdlib.h>

# ifndef EXEC_NAME
# error "EXEC_NAME is not defined."
# else
# define PROG_NAME EXEC_NAME
# endif

# define STDERR 2

typedef struct s_table
{
	pthread_mutex_t	*forks;
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_times_to_eat;
}					t_table;

typedef struct s_philo
{
	int				id;
	struct s_table	*shared;
}					t_philo;

void	error(char *type, char *msg, char *error_code);

#endif
