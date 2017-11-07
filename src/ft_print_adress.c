/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:00 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:22:01 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void				ft_print_adress(long double adr)
{
	long int	simple;
	long double	d;

	simple = adr / 16;
	d = adr / 16 - simple;
	if (simple > 0)
	{
		ft_print_adress(simple);
	}
	simple = d * 16;
	if (simple > 9)
	{
		simple = 97 + simple - 10;
	}
	else
	{
		simple += '0';
	}
	write(1, &simple, 1);
	return ;
}
