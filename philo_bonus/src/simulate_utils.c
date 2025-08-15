/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:41:09 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/15 13:41:40 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	wait_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (table->pids[i] != -1)
			waitpid(table->pids[i], NULL, 0);
		i++;
	}
}

void	kill_processes(t_table *table, int n_proc)
{
	while (--n_proc >= 0)
	{
		if (table->pids[n_proc] != -1)
			kill(table->pids[n_proc], SIGTERM);
	}
}
