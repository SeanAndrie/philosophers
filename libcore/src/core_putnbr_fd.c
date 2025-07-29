/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_putnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:42:23 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/28 17:30:02 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcore.h>

void    core_putnbr_fd(int n, int fd)
{
    char c;
    if (n == 0)
    {
        write(1, "0", 1);
        return ;
    }
    if (n < 0)
    {
        write(fd, "-", 1);
        n = -n;
    }
    if (n > 9)
        core_putnbr_fd(n / 10, fd);
    c = n % 10 + '0';
    write(fd, &c, 1);   
}
