/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_strncmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:50:12 by sgadinga          #+#    #+#             */
/*   Updated: 2025/08/30 08:55:16 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcore.h>

int core_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t  i;

    i = 0;
    while ((s1[i] && s2[i]) && i < n)
    {
        if ((unsigned char)s1[i] != (unsigned char)s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return (0);
}
