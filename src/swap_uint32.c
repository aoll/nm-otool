/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_uint32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:19:08 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/29 12:30:24 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

uint32_t	swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

long	swap_uint32_check(long val, int is_indian)
{
	if (is_indian)
		val = swap_uint32(val);
	if ((long)val < 0)
	{
		printf("%s\n", "ERROR !!!!!!!!!!");
		// exit(1);
		val = 0;
	}
	return (val);
}
