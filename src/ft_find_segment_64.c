/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_segment_64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:20:28 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/29 13:44:07 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int						ret_err(void)
{
	ft_putstr_fd(BAD_OJECT, STDERR);
	return (EXIT_FAILURE);
}

static int						check_segment(
	struct load_command *lc, int ncmds, char *segment_name, t_ptr *ptr_infos)
{
	struct segment_command_64		*seg;
	int								i;

	i = -1;
	while (++i < ncmds)
	{
		if (swap_uint32_check(lc->cmd, ptr_infos->is_indian) == LC_SEGMENT_64)
		{
			if ((void *)(seg = (struct segment_command_64 *)lc)
			+ sizeof(struct segment_command) > (void *)ptr_infos->ptr_end)
				return (EXIT_FAILURE);
			else if (swap_uint32_check(seg->fileoff, ptr_infos->is_indian)
			+ swap_uint32_check(seg->filesize, ptr_infos->is_indian)
			> (long)((size_t)ptr_infos->ptr_end - (size_t)ptr_infos->ptr))
				return (ret_err());
		}
		if (i + 1 < ncmds)
			if ((void *)(lc = (void *)lc
			+ swap_uint32_check(lc->cmdsize, ptr_infos->is_indian))
			+ sizeof(*lc) > (void *)ptr_infos->ptr_end)
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

struct segment_command_64		*ft_find_segment_64(
	struct load_command *lc, int ncmds, char *segment_name, t_ptr *ptr_infos)
{
	struct segment_command_64		*seg;
	int								i;

	if (check_segment(lc, ncmds, segment_name, ptr_infos))
		return (NULL);
	seg = NULL;
	i = -1;
	while (++i < ncmds)
	{
		if (swap_uint32_check(lc->cmd, ptr_infos->is_indian) == LC_SEGMENT_64)
		{
			if ((void *)(seg = (struct segment_command_64 *)lc)
			+ sizeof(struct segment_command) > (void *)ptr_infos->ptr_end)
				return (NULL);
			if (ft_strcmp(seg->segname, segment_name) == 0 || ncmds == 1)
				return (seg);
		}
		if (i + 1 < ncmds)
			if ((void *)(lc = (void *)lc
			+ swap_uint32_check(lc->cmdsize, ptr_infos->is_indian))
			+ sizeof(*lc) > (void *)ptr_infos->ptr_end)
				return (NULL);
	}
	return (seg);
}
