/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:56:43 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/29 12:12:39 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	sync_error(const char *mechanism, const char *action,
		const char *context, const char *error)
{
	core_putstr_fd("philo: ", STDERR_FILENO);
	core_putstr_fd(context, STDERR_FILENO);
	core_putstr_fd(" ", STDERR_FILENO);
	core_putstr_fd(mechanism, STDERR_FILENO);
	core_putstr_fd(" ", STDERR_FILENO);
	core_putstr_fd(action, STDERR_FILENO);
	core_putstr_fd(" ", STDERR_FILENO);
	core_putstr_fd("failed (", STDERR_FILENO);
	core_putstr_fd(error, STDERR_FILENO);
	core_putendl_fd(")", STDERR_FILENO);
}

int	destroy_mutex(pthread_mutex_t *mutex, const char *context)
{
	int	err;

	err = pthread_mutex_destroy(mutex);
	if (err != 0)
		return (sync_error("mutex", "destruction", context, strerror(err)), 0);
	return (1);
}

int	initialize_mutex(pthread_mutex_t *mutex, const char *context)
{
	int	err;

	err = pthread_mutex_init(mutex, NULL);
	if (err != 0)
		return (sync_error("mutex", "initialization", context, strerror(err)),
			0);
	return (1);
}

int	create_thread(pthread_t *thread, void *routine(void *), void *arg,
		const char *context)
{
	int	err;

	err = pthread_create(thread, NULL, routine, arg);
	if (err != 0)
		return (sync_error("thread", "creation", context, strerror(err)), 0);
	return (1);
}

int	mutex_gate(pthread_mutex_t *mutex, t_lock_action action, char *context)
{
	int	err;

	if (action == LOCK)
	{
		err = pthread_mutex_lock(mutex);
		if (err != 0)
			return (sync_error("mutex", "lock", context, strerror(err)), 0);
	}
	else
	{
		err = pthread_mutex_unlock(mutex);
		if (err != 0)
			return (sync_error("mutex", "unlock", context, strerror(err)), 0);
	}
	return (1);
}
