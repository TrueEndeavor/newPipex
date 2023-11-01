/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:42:14 by lannur-s          #+#    #+#             */
/*   Updated: 2023/11/01 11:13:42 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_file_permissions(int ac, char **av)
{
	int	fd;

	fd = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, OUTFILE_PERM);
	if (fd == -1)
	{
		if (errno == EACCES)
			display_error(ERR_PERMISSION_DENIED, av[ac - 1]);
		if (errno == ENOENT)
			display_error(ERR_FILE_DOESNT_EXIST, av[ac - 1]);
		return (0);
	}	
	else if (ft_strcmp(av[1], "here_doc") == 1 && access(av[1], F_OK) == -1)
	{
		display_error(ERR_FILE_DOESNT_EXIST, av[1]);
		close(fd);
		return (1);
	}
	else if (ft_strcmp(av[1], "here_doc") == 1 && access(av[1], R_OK) == -1)
	{
		display_error(ERR_PERMISSION_DENIED, av[1]);
		close(fd);
		exit (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	has_invalid_input_arguments(int ac, char **av)
{
	if (ft_strcmp(av[1], "here_doc") == 1 && ac < MIN_COMMAND_LINE_ARGS)
	{
		display_error(ERR_BAD_ARGUMENTS_COUNT, PIPEX_USAGE);
		return (1);
	}
	if (ft_strcmp(av[1], "here_doc") == 0 && ac < MIN_CMD_LINE_ARGS_HERE_DOC)
	{
		display_error(ERR_BAD_ARGUMENTS_COUNT, PIPEX_USAGE_HERE_DOC);
		return (1);
	}	
	return (check_file_permissions(ac, av));
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

void	err_handler(char *cmd_path, char **cmd_args, t_pipeline *pipeline)
{
	if (ft_strcmp(cmd_path, ERR_DIR_DOESNT_EXIST) == 0)
	{
		display_error(ERR_DIR_DOESNT_EXIST, cmd_args[0]);
		free_all_commands(pipeline);
		exit (1);
	}
	if (ft_strcmp(cmd_path, ERR_FILE_DOESNT_EXIST) == 0)
	{
		display_error(ERR_FILE_DOESNT_EXIST, cmd_args[0]);
		free_all_commands(pipeline);
		exit (1);
	}
	if (ft_strcmp(cmd_path, ERR_COMMAND_NOT_FOUND) == 0 || !cmd_path)
	{
		display_error(ERR_COMMAND_NOT_FOUND, cmd_args[0]);
		free_all_commands(pipeline);
		exit (127);
	}
}
