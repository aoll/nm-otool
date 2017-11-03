/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	ft_ar_file(char *ptr, char *ptr_end, char *av, int is_otool)
{
	struct ar_hdr	*ar;
	int				len;
	int				nb;
	char			*archive_name;

	if ((void *)
	(ar = (void *)ptr + SARMAG) + sizeof(struct ar_hdr) > (void *)ptr_end)
		return (EXIT_FAILURE);
	if (is_otool)
		ft_print_archive_name("Archive : ", av);
	if ((len = ft_atoi(ar->ar_size)) <= 0)
		return (EXIT_FAILURE);
	while ((char *)(ar = (void *)ar + sizeof(*ar) + len) < ptr_end)
	{
		if ((len = atoi(ar->ar_size)) <= 0)
			return (EXIT_FAILURE);
		nb = atoi(ar->ar_name + ft_strlen(AR_EFMT1));
		if (check_valid_file((void *)ar + nb + sizeof(*ar), ptr_end))
		{
			continue ;
		}
		if (!(archive_name = ft_format_archive_name(
			av, "(", (void *)ar + sizeof(*ar), ")")))
			return (EXIT_FAILURE);
		if (!is_otool)
		{
			write(1, "\n", 1);
			write(1, archive_name, ft_strlen(archive_name));
			write(1, ":\n", 2);
		}
		ft_otool((void *)ar + nb + sizeof(*ar), ptr_end, archive_name, is_otool);
		free(archive_name);
	}
	return (EXIT_SUCCESS);
}

