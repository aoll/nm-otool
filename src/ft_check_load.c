/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:19:38 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/29 13:11:05 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	ret_err(void)
{
	ft_putstr_fd(ERROR_LOAD_MIN_SIZE, STDERR);
	return (EXIT_FAILURE);
}

int			ft_check_load(
	struct load_command *lc, char *ptr_end, t_load *load)
{
	int							i;
	int							size;

	i = -1;
	size = 0;
	if (!load->ncmds)
		return (EXIT_FAILURE);
	while (++i < load->ncmds)
	{
		if (swap_uint32_check(lc->cmdsize, load->is_indian) < MIN_LOAD_SIZE)
			return (ret_err());
		size += swap_uint32_check(lc->cmdsize, load->is_indian);
		if ((void *)(lc = (void *)lc
		+ swap_uint32_check(lc->cmdsize, load->is_indian))
		+ sizeof(struct load_command) > (void *)ptr_end)
			return (EXIT_FAILURE);
	}
	if (size != load->sizeofcmds)
	{
		ft_putstr_fd(ERROR_LOAD_SIZE, STDERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
