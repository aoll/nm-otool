/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:20:03 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/29 13:46:15 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static char	*ft_cputype_name(int cputype)
{
	if (cputype == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (cputype == CPU_TYPE_I386)
		return ("i386");
	else if (cputype == CPU_TYPE_VAX)
		return ("vax");
	else if (cputype == CPU_TYPE_MC680x0)
		return ("mc680x0");
	else if (cputype == CPU_TYPE_MC98000)
		return ("mc98000");
	else if (cputype == CPU_TYPE_SPARC)
		return ("sparc");
	else if (cputype == CPU_TYPE_I860)
		return ("i860");
	return (UNKNOW);
}

static int	ft_print_arch_name(
	char *file_name, void *ptr, void *ptr_end, int is_otool)
{
	int		is_indian;
	int		cputype;

	if (ptr + sizeof(unsigned int) > ptr_end)
		return (EXIT_FAILURE);
	is_indian = swap_uint32(*(int *)ptr) == MH_MAGIC ? 1 : 0;
	cputype = swap_uint32_check(
		*(int *)(ptr + sizeof(unsigned int)), is_indian);
	if (!is_otool)
		ft_putstr("\n");
	ft_putstr(file_name);
	ft_putstr(" (");
	if (!is_otool)
		ft_putstr(FOR_ARCH);
	else
		ft_putstr("architecture");
	ft_putstr(" ");
	ft_putstr(ft_cputype_name(cputype));
	ft_putstr("):\n");
	return (EXIT_SUCCESS);
}

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
		if (ft_print_arch_name(av, ptr + f_i.offset, ptr_end, cmd_f->is_otool))
			return (EXIT_FAILURE);
		ft_otool(ptr + f_i.offset, ptr_end, NULL, cmd_f);
		if ((void *)(f_i.f_a = (void *)f_i.f_a + sizeof(*f_i.f_a))
		+ sizeof(t_fat_infos) > (void *)ptr_end)
			return (EXIT_FAILURE);
		f_i.nb_arch--;
	}
	return (EXIT_SUCCESS);
}

static int	ft_fat_file_all_one(
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
		if (!cmd_f->is_otool)
		{
			ft_putstr(av);
			ft_putstr(":\n");
		}
		ft_otool(ptr + f_i.offset, ptr_end, av, cmd_f);
		if ((void *)(f_i.f_a = (void *)f_i.f_a + sizeof(*f_i.f_a))
		+ sizeof(t_fat_infos) > (void *)ptr_end)
			return (EXIT_FAILURE);
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

	if ((void *)(f_h = (void *)ptr) + sizeof(*f_h) >= (void *)ptr_end)
		return (EXIT_FAILURE);
	nb_arch = swap_uint32(f_h->nfat_arch) + 1;
	if ((void *)(f_a = (void *)f_h + sizeof(*f_h))
	+ sizeof(*f_a) >= (void *)ptr_end)
		return (EXIT_FAILURE);
	while (--nb_arch)
	{
		if (swap_uint32(f_a->cputype) == CPU_TYPE_X86_64)
		{
			if ((long)swap_uint32(f_a->offset) >= 0)
				return (ft_otool(ptr + swap_uint32(f_a->offset),
				ptr_end, av, cmd_f));
		}
		if ((void *)(f_a = (void *)f_a + sizeof(*f_a)) + sizeof(*f_a)
		> (void *)ptr_end)
			return (EXIT_FAILURE);
	}
	if ((nb_arch = swap_uint32(f_h->nfat_arch)) == 1)
		return (ft_fat_file_all_one(ptr, ptr_end, av, cmd_f));
	return (ft_fat_file_all(ptr, ptr_end, av, cmd_f));
}
