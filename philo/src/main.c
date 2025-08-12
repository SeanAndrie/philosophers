/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:53 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/07 17:40:14 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
