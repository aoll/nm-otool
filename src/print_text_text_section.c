/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text_text_section.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:24:10 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/23 15:58:46 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_chariot(int j)
{
	if (j % 16 != 0)
		write(1, "\n", 1);
}

static void	print_infos(char *ptr, t_ptr *ptr_infos, int *j)
{
	if (*(unsigned char *)ptr < 0x10)
		write(1, "0", 1);
	ft_print_adress(*(unsigned char *)ptr);
	if (!ptr_infos->is_indian)
		write(1, " ", 1);
	if (++(*j) % 4 == 0 && ptr_infos->is_indian)
		write(1, " ", 1);
	if (*j % 16 == 0)
		write(1, "\n", 1);
}

int			print_text_text_section(
	void *ptr, long double addr, int size, t_ptr *ptr_infos)
{
	size_t	len;
	int		j;

	j = 0;
	len = ptr_infos->is_64 ? ft_strlen(PADDING_STR_64) : ft_strlen(PADDING_STR);
	write(1, CONTENT_TEXT_TEXT, ft_strlen(CONTENT_TEXT_TEXT));
	while (j < size)
	{
		if (j % 16 == 0)
		{
			ft_print_padding_adresse(
				addr, len, ptr_infos->is_64 ? PADDING_STR_64 : PADDING_STR);
			write(1, "\t", 1);
		}
		print_infos(ptr, ptr_infos, &j);
		addr++;
		ptr++;
	}
	print_chariot(j);
	return (EXIT_SUCCESS);
}
