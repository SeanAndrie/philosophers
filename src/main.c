/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:53 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/29 18:28:05 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_table	*table;

	table = set_table(argc, argv);
	if (!table)
		fatal_error(NULL, "failed to initialize table.", EXIT_FAILURE);
	if (!start_simulation(table))
	{
		free_table(table);
		fatal_error(NULL, "Could not start simulation.", EXIT_FAILURE);
	}
	free_table(table);
	return (0);
}
