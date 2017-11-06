/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	execute_is_otool(char *av, t_cmd_flag *cmd_f)
{
	int			fd;
	char		*ptr;
	struct stat	buf;
	int			ret;

	if ((fd = open(av, O_RDONLY)) < 0)
	{
		ft_putstr(NO_ACCESS);
		ft_putstr(av);
		ft_putstr("\n");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
		return (EXIT_FAILURE);
	if ((ptr = mmap(
		0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (EXIT_FAILURE);
	ret = ft_otool(ptr, (void *)ptr + buf.st_size, av, cmd_f);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	return (ret);
}

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
	{
		return (error_flag(av));
	}
	while (*av)
	{
		if (*av == 'u')
			cmd_f->u = 1;
		else if (*av == 'U')
			cmd_f->U = 1;
		else if (*av == 'g')
			cmd_f->g = 1;
		else
		{
			return (error_flag(av));
		}
		av++;
	}
	return (EXIT_SUCCESS);
}

static int	set_cmd_flag(int ac, char **av, t_cmd_flag *cmd_f)
{
	int i;
	int err;

	cmd_f->is_otool = 0;
	cmd_f->g = 0;
	cmd_f->u = 0;
	cmd_f->U = 0;
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
	print_outpout_64(NULL, NULL, NULL, cmd_f);
	return (i);
}

int			main(int ac, char **av)
{
	int			ret;
	int			i;
	t_cmd_flag	cmd_f;


	if (ac < 2)
		return (EXIT_FAILURE);
	if ((i = set_cmd_flag(ac, av, &cmd_f)) < 0)
	{
		if (i == HELP_FLAG)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	while (i < ac)
	{
		ret = execute_is_otool(av[i], &cmd_f);
		i++;
	}
	return (ret);
}
