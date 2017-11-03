/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_adress_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			ft_get_adress_str(long double adr, char **dest, int index)
{
	long int	simple;
	long double	d;
	char		*s;

	if (index < 0)
		return ;
	simple = adr / 16;
	d = adr / 16 - simple;
	if (simple > 0)
		ft_get_adress_str(simple, dest, index - 1);
	simple = d * 16;
	if (simple > 9)
	{
		simple = 97 + simple - 10;
	}
	else
	{
		simple += '0';
	}
	s = *dest;
	s[index] = (int)simple;
	return ;
}

