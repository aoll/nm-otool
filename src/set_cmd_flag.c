/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	error_flag(char *av)
{
	ft_putstr_fd(ERROR_FLAG, STDERR);
	ft_putstr_fd(" '-", STDERR);
	ft_putstr_fd(av, STDERR);
	ft_putstr_fd("'\n", STDERR);
	ft_putstr_fd(TYPE_HELP, STDOUT);
	return (EXIT_FAILURE);
}

static int	help_mess(void)
{
	ft_putstr_fd(HELP_MESS, STDOUT);
	return (HELP_FLAG);
}

static int	set_flag(char *av, t_cmd_flag *cmd_f)
{
	av++;
	if (!*av)
		return (error_flag(av));
	while (*av)
	{
		if (*av == 'p')
			cmd_f->p = 1;
		else if (*av == 'u')
			cmd_f->u = 1;
		else if (*av == 'U')
			cmd_f->U = 1;
		else if (*av == 'g')
			cmd_f->g = 1;
		else if (*av == 'j')
			cmd_f->j = 1;
		else if (*av == 'r')
			cmd_f->r = 1;
		else
			return (error_flag(av));
		av++;
	}
	return (EXIT_SUCCESS);
}

int			set_cmd_flag(int ac, char **av, t_cmd_flag *cmd_f)
{
	int i;
	int err;

	cmd_f->is_otool = 0;
	cmd_f->p = 0;
	cmd_f->g = 0;
	cmd_f->u = 0;
	cmd_f->U = 0;
	cmd_f->j = 0;
	cmd_f->r = 0;
	i = 1;
	while (i < ac)
	{
		if (*av[i] != '-')
			break ;
		if (!ft_strcmp(av[i], HELP))
			return (help_mess());
		if ((err = set_flag(av[i], cmd_f)))
			return (-1);
		i++;
	}
	return (i);
}
