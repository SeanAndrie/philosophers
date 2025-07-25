/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_strtol_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:30:05 by sgadinga          #+#    #+#             */
/*   Updated: 2025/07/24 22:32:39 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_STRTOL_UTILS_H
#define CORE_STRTOL_UTILS_H

int	convert_to_value(char c, int base);
int	handle_base_prefix(const char **nptr, int base);
void skip_whitespace_and_sign(const char **nptr, int *sign);
long	check_overflow(long res, int digit, int base, int sign);

#endif
