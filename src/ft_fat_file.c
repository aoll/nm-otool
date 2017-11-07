/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:20:03 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:33:40 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	ft_fat_file_all(
	char *ptr, char *ptr_end, char *av, t_cmd_flag *cmd_f)
{
	t_fat_infos f_i;

	f_i.f_h = (struct fat_header *)ptr;
	f_i.nb_arch = swap_uint32(f_i.f_h->nfat_arch);
	f_i.f_a = (void *)f_i.f_h + sizeof(*f_i.f_h);
	f_i.offset = 0;
	while (f_i.nb_arch)
	{
		f_i.offset = swap_uint32(f_i.f_a->offset);
		if (!check_valid_file(ptr + f_i.offset, ptr_end) && f_i.offset >= 0)
		{
			if (!cmd_f->is_otool)
			{
				ft_putstr(av);
				ft_putstr(":\n");
			}
			ft_otool(ptr + f_i.offset, ptr_end, av, cmd_f);
		}
		f_i.f_a = (void *)f_i.f_a + sizeof(*f_i.f_a);
		f_i.nb_arch--;
	}
	return (EXIT_SUCCESS);
}

int			ft_fat_file(
	char *ptr, char *ptr_end, char *av, t_cmd_flag *cmd_f)
{
	struct fat_header	*f_h;
	struct fat_arch		*f_a;
	int					nb_arch;
	int					offset;

	f_h = (struct fat_header *)ptr;
	nb_arch = swap_uint32(f_h->nfat_arch);
	f_a = (void *)f_h + sizeof(*f_h);
	offset = 0;
	while (nb_arch)
	{
		if (swap_uint32(f_a->cputype) == CPU_TYPE_X86_64)
		{
			offset = swap_uint32(f_a->offset);
			if (offset >= 0)
				return (ft_otool(ptr + offset, ptr_end, av, cmd_f));
		}
		f_a = (void *)f_a + sizeof(*f_a);
		nb_arch--;
	}
	return (ft_fat_file_all(ptr, ptr_end, av, cmd_f));
}
