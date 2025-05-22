/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:24:05 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 03:06:48 by sgadinga         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	(void)av;
	if (ac < 6)
		error("usage", "./philo [n_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [OPTIONAL | n_times_to_eat]", "1");
	return (0);
}
