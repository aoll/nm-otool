/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	check_valid_file(char *ptr, char *ptr_end)
{
	unsigned int magic_number;

	if (ptr >= ptr_end)
		return (EXIT_FAILURE);
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC || magic_number == MH_MAGIC_64)
	{
		return (EXIT_SUCCESS);
	}
	else if (magic_number == FAT_CIGAM)
	{
		return (EXIT_SUCCESS);
	}
	else if (!strncmp(ptr, ARMAG, SARMAG))
	{
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
