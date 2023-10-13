/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:42:14 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/13 16:49:50 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	has_invalid_input_arguments(int ac, char **av)
{
	int	fd;

	if (ac < MIN_COMMAND_LINE_ARGS)
	{
		display_error(ERR_BAD_ARGUMENTS_COUNT, PIPEX_B_USAGE);
		return (1);
	}
	fd = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, OUTFILE_PERM);
	if (fd == -1)
	{
		if (errno == EACCES)
			display_error(ERR_PERMISSION_DENIED, av[ac - 1]);
		if (errno == ENOENT)
			display_error(ERR_FILE_DOESNT_EXIST, av[ac - 1]);
		return (0);
	}	
	else if (access(av[1], F_OK) == -1)
	{
		display_error(ERR_FILE_DOESNT_EXIST, av[1]);
		return (1);
	}
	else if (access(av[1], R_OK) == -1)
	{
		display_error(ERR_PERMISSION_DENIED, av[1]);
		exit (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}


int	display_error(char *error, char *details)
{
	if (details != NULL)
	{
		ft_putstr_fd(details, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}
