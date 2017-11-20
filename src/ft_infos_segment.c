/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infos_segment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:21:39 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:25:16 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	loop_segment(
	struct load_command *lc, int *index, t_seg_infos *seg_infos, int is_indian)
{
	struct segment_command	*segment;
	struct section			*section;
	uint32_t				loop;

	segment = (struct segment_command *)lc;
	section = (void *)segment + sizeof(*segment);
	loop = 0;
	while (loop < swap_uint32_check(segment->nsects, is_indian))
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			seg_infos->text_nsect = *index + 1;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			seg_infos->data_nsect = *index + 1;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			seg_infos->bss_nsect = *index + 1;
		section = (void *)section + sizeof(*section);
		loop++;
		*index = *index + 1;
	}
}

t_seg_infos	*ft_infos_segment(char *ptr, char *ptr_end,
	struct mach_header *header, struct load_command *lc)
{
	t_seg_infos					*seg_infos;
	uint32_t					i;
	int							index;
	t_load						load;

	if (!(seg_infos = malloc(sizeof(t_seg_infos))))
		return (NULL);
	if ((void *)(lc = (void *)ptr + sizeof(*header))
	+ sizeof(struct load_command) > (void *)ptr_end)
		return (NULL);
	load.is_indian = swap_uint32(*(int *)ptr) == MH_MAGIC ? 1 : 0;
	load.ncmds = swap_uint32_check(header->ncmds, load.is_indian);
	load.sizeofcmds = swap_uint32_check(header->sizeofcmds, load.is_indian);
	if (ft_check_load(lc, ptr_end, &load))
		return (NULL);
	ft_init_seg_infos(seg_infos);
	i = 0;
	index = 0;
	while (i < swap_uint32_check(header->ncmds, load.is_indian))
	{
		if (lc->cmd == LC_SEGMENT)
			loop_segment(lc, &index, seg_infos, load.is_indian);
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
