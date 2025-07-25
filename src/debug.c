/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:29:04 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/24 23:41:03 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    print_args(char **av)
{
    while (*av != NULL)
        core_putendl_fd(*av++, STDOUT_FILENO);
}
