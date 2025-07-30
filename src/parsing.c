/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:00:04 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/30 09:12:38 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static t_arg_desc	define_argument(const char *name, t_arg_type type,
		void *target, int max_value)
{
	return ((t_arg_desc){name, type, target, max_value});
}

static t_arg_desc	*define_default_arguments(t_table *table)
{
	static t_arg_desc	args[5];

	args[0] = define_argument("n_philo", TYPE_UINT, &table->n_philo, 200);
	args[1] = define_argument("time_to_die_ms", TYPE_TIME,
			&table->time_to_die_ms, 0);
	args[2] = define_argument("time_to_eat_ms", TYPE_TIME,
			&table->time_to_eat_ms, 0);
	args[3] = define_argument("time_to_sleep_ms", TYPE_TIME,
			&table->time_to_sleep_ms, 0);
	args[4] = define_argument("n_meals", TYPE_UINT, &table->max_meals, 0);
	return (args);
}

static void	arg_error(const char *name, int index, const char *message,
		int *ret)
{
	core_putstr_fd("philo: table init: argument ", STDERR_FILENO);
	core_putnbr_fd(index, STDERR_FILENO);
	core_putstr_fd(" (", STDERR_FILENO);
	core_putstr_fd(name, STDERR_FILENO);
	core_putstr_fd(") ", STDERR_FILENO);
	core_putstr_fd(message, STDERR_FILENO);
	core_putendl_fd("", STDERR_FILENO);
	*ret = 0;
}

static int	parse_positive_int(const char *str, int *out_val)
{
	char	*end;
	long	value;

	if (!str || *str == '\0')
		return (0);
	errno = 0;
	value = core_strtol(str, &end, 10);
	if (errno == ERANGE || value > INT_MAX || value < 1)
		return (0);
	if (str == end || *end != '\0')
		return (0);
	*out_val = (int)value;
	return (1);
}

int	parse_arguments(int argc, char **argv, t_table *table)
{
	int			i;
	int			ret;
	int			value;
	t_arg_desc	*args;

	i = 1;
	ret = 1;
	args = define_default_arguments(table);
	while (i < argc)
	{
		if (!parse_positive_int(argv[i], &value))
			arg_error(args[i - 1].name, i, "is not a valid positive integer",
				&ret);
		if (args[i - 1].max_value && value > args[i - 1].max_value)
			arg_error(args[i - 1].name, i, "exceeds maximum allowed value",
				&ret);
		if (args[i - 1].type == TYPE_TIME && value < 10)
			arg_error(args[i - 1].name, i, "must be >= 10ms", &ret);
		if (args[i - 1].type == TYPE_UINT)
			*(unsigned int *)args[i - 1].target = (unsigned int)value;
		else
			*(time_t *)args[i - 1].target = (time_t)value;
		i++;
	}
	return (ret);
}
