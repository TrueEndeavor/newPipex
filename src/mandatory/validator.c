/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:42:14 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/10 13:01:57 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Checks for valid input arguments and file permissions. Displays errors if 
 * necessary.
 * 
 * @param ac Number of command line arguments.
 * @param av Array of command line arguments.
 * @return 1 if there are invalid input arguments or file permissions issues, 
 *         0 otherwise.
 */
int	has_invalid_input_arguments(int ac, char **av)
{
	if (ac < MIN_COMMAND_LINE_ARGS || ac > MIN_COMMAND_LINE_ARGS)
	{
		display_error(ERR_BAD_ARGUMENTS_COUNT, PIPEX_USAGE);
		return (1);
	}
	else if (open(av[4], O_TRUNC | O_CREAT | O_RDWR, OUTFILE_PERM) == -1)
	{
		if (errno == EACCES)
			display_error(ERR_PERMISSION_DENIED, av[4]);
		if (errno == ENOENT)
			display_error(ERR_FILE_DOESNT_EXIST, av[4]);
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
	return (0);
}

/**
 * Displays error messages to the standard error output.
 * 
 * @param error Error message to be displayed.
 * @param details Additional details to be displayed along with the error 
 *                message.
 * @return 1 to indicate an error condition.
 */
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
