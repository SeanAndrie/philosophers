/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:24:05 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 11:59:23 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *type, char *msg, char *error_code)
{
	ft_putstr_fd(PROG_NAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(type, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd("\n", STDERR);
	if (error_code)
		exit(ft_atoi(error_code));
}

void	print_table_params(t_table *table)
{
	printf("n_philos: %d\n", table->n_philos);
	printf("time_to_die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time_to_sleep: %ld\n", table->time_to_sleep);
	printf("n_times_to_eat: %d\n", table->n_times_to_eat);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("usage: ", STDERR);
		ft_putstr_fd("./philo [n_philos] [time_to_die] [time_to_eat] ", STDERR);
		ft_putstr_fd("[time_to_sleep] [n_times_to_eat]\n", STDERR);
		exit(1);
	}
	table = init_table(av);
	if (!table)
		error("Table initialization", "Cannot initialize table.", "1");
	printf("Current Time: %ld\n", ft_gettime_ms());
	print_table_params(table);
	free(table);
	return (0);
}
