/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:19:29 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/23 00:48:20 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_archive_name(char *archive_name, t_cmd_flag *cmd_f)
{
	if (!cmd_f->is_otool)
	{
		write(1, "\n", 1);
		write(1, archive_name, ft_strlen(archive_name));
		write(1, ":\n", 2);
	}
}

static int	ft_loop_ar_file(
	struct ar_hdr *ar, char *ptr_end, char *av, t_cmd_flag *cmd_f)
{
	int				nb;
	char			*archive_name;
	int				len;

	if ((len = ft_atoi(ar->ar_size)) <= 0)
		return (EXIT_FAILURE);
	while ((char *)(
		ar = (void *)ar + sizeof(*ar) + len) + sizeof(*ar) < ptr_end)
	{
		if ((len = ft_atoi(ar->ar_size)) <= 0)
			return (EXIT_FAILURE);
		nb = ft_atoi(ar->ar_name + ft_strlen(AR_EFMT1));
		if (check_valid_file((void *)ar + nb + sizeof(*ar), ptr_end))
			continue ;
		if (!(archive_name = ft_format_archive_name(
			av, "(", (void *)ar + sizeof(*ar), ")")))
			return (EXIT_FAILURE);
		print_archive_name(archive_name, cmd_f);
		ft_otool(
			(void *)ar + nb + sizeof(*ar), ptr_end, archive_name, cmd_f);
		free(archive_name);
	}
	return (EXIT_SUCCESS);
}

int			ft_ar_file(char *ptr, char *ptr_end, char *av, t_cmd_flag *cmd_f)
{
	struct ar_hdr	*ar;

	if ((void *)
	(ar = (void *)ptr + SARMAG) + sizeof(struct ar_hdr) + sizeof(*ar)
	 > (void *)ptr_end)
		return (EXIT_FAILURE);
	if (cmd_f->is_otool)
		ft_print_archive_name("Archive : ", av);
	return (ft_loop_ar_file(ar, ptr_end, av, cmd_f));
}
