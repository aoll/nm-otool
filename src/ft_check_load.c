/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:19:38 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:25:52 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	ft_check_load(struct load_command *lc, int ncmds, int sizeofcmds)
{
	int							i;
	int							size;

	i = 0;
	size = 0;
	while (i < ncmds)
	{
		if (lc->cmdsize < MIN_LOAD_SIZE)
		{
			ft_putstr_fd(ERROR_LOAD_MIN_SIZE, STDERR);
			return (EXIT_FAILURE);
		}
		size += lc->cmdsize;
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
	if (size != sizeofcmds)
	{
		ft_putstr_fd(ERROR_LOAD_SIZE, STDERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
