/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	sort_ascii(t_sort **tmp, int nsyms)
{
	int		i;

	i = 0;
	while (i + 1 < nsyms)
	{
		if (ft_strcmp(tmp[i]->name, tmp[i + 1]->name) > 0)
		{
			t_sort *s;
			s = tmp[i];
			tmp[i] = tmp[i + 1];
			tmp[i + 1] = s;
			i = 0;
		}
		else
			i++;
	}
	return ;
}

