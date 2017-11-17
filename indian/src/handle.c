/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:23:09 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/17 16:48:40 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	loop_handle(char *ptr, char *ptr_end,
	struct mach_header *header, t_cmd_flag *cmd_f)
{
	uint32_t				i;
	t_seg_infos				*seg_infos;
	struct symtab_command	*sym;
	struct load_command		*lc;

	if ((void *)(lc = (void *)ptr + sizeof(*header)) + sizeof(struct load_command) > (void *)ptr_end)
		return (EXIT_FAILURE);
	if (!(seg_infos = ft_infos_segment(ptr, ptr_end, header, lc)))
		return (EXIT_FAILURE);
	i = -1;
	seg_infos->cmd_f = cmd_f;
	while (++i < header->ncmds)
	{
		if (swap_uint32(lc->cmd) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			sort_and_print_outpout(sym, ptr, ptr_end, seg_infos);
			break ;
		}
		lc = (void *)lc + swap_uint32(lc->cmdsize);
		i++;
	}
	free(seg_infos);
	return (EXIT_SUCCESS);
}

struct mach_header *endian(void *ptr, void *ptr_end)
{
	struct mach_header	*tmp;
	struct mach_header	*header;

	header = malloc(sizeof(struct mach_header));
	ft_bzero(header, sizeof(struct mach_header));
	if ((void *)(tmp = (struct mach_header *)ptr) > (void *)ptr_end)
		return (NULL);
	ft_memcpy(header, tmp, sizeof(struct mach_header));
	header->ncmds =  swap_uint32(tmp->ncmds);
	header->sizeofcmds = swap_uint32(header->sizeofcmds);
	return (header);
}

int			handle(char *ptr, char *ptr_end, t_cmd_flag *cmd_f)
{
	struct mach_header	*header;
	char *tmp;


	if ((void *)(header = (struct mach_header *)ptr) + sizeof(struct mach_header) > (void *)ptr_end)
		return (EXIT_FAILURE);
	header = endian(ptr, ptr_end);
	if ((void *)ptr + header->sizeofcmds > (void *)ptr_end)
		return (EXIT_FAILURE);
	if (loop_handle(ptr, ptr_end, header, cmd_f))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
