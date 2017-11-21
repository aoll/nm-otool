/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infos_segment_64.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:21:30 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:25:16 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	loop_segment64(
	struct load_command *lc, int *index, t_seg_infos *seg_infos, t_load *load)
{
	struct segment_command_64	*segment;
	struct section_64			*section;
	uint32_t					loop;

	if ((void *)(segment = (struct segment_command_64 *)lc)
	+ sizeof(struct segment_command_64) > load->ptr_end)
		return (EXIT_FAILURE);
	if ((void *)(section = (void *)segment + sizeof(*segment))
	+ sizeof(*section) > load->ptr_end)
		return (EXIT_FAILURE);
	loop = 0;
	while (loop < swap_uint32_check(segment->nsects, load->is_indian))
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			seg_infos->text_nsect = *index + 1;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			seg_infos->data_nsect = *index + 1;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			seg_infos->bss_nsect = *index + 1;
		if ((void *)(section = (void *)section + sizeof(*section))
		+ sizeof(*section) > load->ptr_end)
			return (EXIT_FAILURE);
		loop++;
		*index = *index + 1;
	}
	return (EXIT_SUCCESS);
}

t_seg_infos	*ft_infos_segment_64(char *ptr, char *ptr_end,
	struct mach_header_64 *header, struct load_command *lc)
{
	t_seg_infos					*seg_infos;
	uint32_t					i;
	int							index;
	t_load						load;

	if (!(seg_infos = malloc(sizeof(t_seg_infos))))
		return (NULL);
	load.is_indian = swap_uint32(*(int *)ptr) == MH_MAGIC ? 1 : 0;
	load.ncmds = swap_uint32_check(header->ncmds, load.is_indian);
	load.sizeofcmds = swap_uint32_check(header->sizeofcmds, load.is_indian);
	load.ptr = ptr;
	load.ptr_end = ptr_end;
	ft_init_seg_infos(seg_infos);
	if ((void *)(lc = (void *)ptr + sizeof(*header)) > (void *)ptr_end)
		return (NULL);
	// if (ft_check_load(lc, header->ncmds, header->sizeofcmds))
	// 	return (NULL);
	i = 0;
	index = 0;
	while (i < header->ncmds)
	{
		if (swap_uint32_check(lc->cmd, load.is_indian) == LC_SEGMENT_64)
			loop_segment64(lc, &index, seg_infos, &load);
			if ((void *)(lc = (void *)lc
			+ swap_uint32_check(lc->cmdsize, load.is_indian))
			+ sizeof(struct load_command) > (void *)ptr_end)
			{
				free(seg_infos);
				return (NULL);
			}
		i++;
	}
	return (seg_infos);
}
