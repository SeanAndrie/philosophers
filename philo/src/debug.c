/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:29:04 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/30 08:58:57 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline void	header_and_columns(void)
{
	printf("\n===================");
	printf(" FINAL FORK STATISTICS ");
	printf("====================\n");
	printf("| fork_id | times_used ");
	printf("| total_time_held | average_time_held |\n");
	printf("|---------|------------|--------");
	printf("---------|-------------------|\n");
}

void	print_fork_statistics(t_table *table)
{
	size_t	i;
	t_fork	*forks;
	time_t	average_time_held;

	header_and_columns();
	forks = table->mutexes.forks;
	i = 0;
	while (i < table->n_philo)
	{
		if (forks[i].times_used > 0)
			average_time_held = forks[i].total_time_held_ms
				/ forks[i].times_used;
		else
			average_time_held = 0;
		printf("|%5zu    ", i);
		printf("|%6lu      ", forks[i].times_used);
		printf("|%9lums      ", forks[i].total_time_held_ms);
		printf("|%10lums       ", average_time_held);
		printf("|\n");
		i++;
	}
	printf("==================================");
	printf("============================\n\n");
}

void	log_status(t_philo *philo, const char *action, const char *color)
{
	time_t	elapsed;

	elapsed = get_current_time() - philo->table->start_time;
	mutex_gate(&philo->table->mutexes.log_lock, LOCK, "write");
	if (!simulation_active(philo->table) && core_strncmp(action, "died",
			4) != 0)
	{
		mutex_gate(&philo->table->mutexes.log_lock, UNLOCK, "write");
		return ;
	}
	if (color)
		printf("%s%ld %u %s%s\n", color, elapsed, philo->id, action,
			ANSI_RESET);
	else
		printf("%ld %u %s\n", elapsed, philo->id, action);
	mutex_gate(&philo->table->mutexes.log_lock, UNLOCK, "write");
}
