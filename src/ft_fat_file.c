/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fat_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	ft_fat_file(char *ptr, char *ptr_end, char *av, int is_otool)
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
			{
				return (ft_otool(ptr + offset, ptr_end, av, is_otool));
			}
		}
		f_a = (void *)f_a + sizeof(*f_a);
		nb_arch--;
	}
	return (EXIT_SUCCESS);
}

