/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	ft_loop_error(char *av)
{
	ft_putstr_fd(av, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(ERROR_FORMAT_FILE, STDERR);
	return (EXIT_FAILURE);
}

int			ft_otool(char *ptr, char *ptr_end, char *av, int is_otool)
{
	unsigned int magic_number;

	if (ptr >= ptr_end)
		return (ft_loop_error(av));
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC)
		if (is_otool)
			return (handle_text(ptr, ptr_end, av));
		else
			return (handle(ptr, ptr_end));
	else if (magic_number == MH_MAGIC_64)
		if (is_otool)
			return (handle_64_text(ptr, ptr_end, av));
		else
			return (handle_64(ptr, ptr_end));
	else if (magic_number == FAT_CIGAM)
		return (ft_fat_file(ptr, ptr_end, av, is_otool));
	else if (!strncmp(ptr, ARMAG, SARMAG))
		return (ft_ar_file(ptr, ptr_end, av, is_otool));
	return (ft_loop_error(av));
}
