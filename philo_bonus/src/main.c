/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:57:24 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/09 19:22:02 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	main(int argc, char **argv)
{
	t_table	*table;

	table = set_table(argc, argv);
	if (!table)
		return (1);
	if (!start_simulation(table))
	{
		free_table(table);
		fatal_error(NULL, "Could not start simulation.", EXIT_FAILURE);
	}
	free_table(table);
	return (0);
}
