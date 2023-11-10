/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:42:14 by lannur-s          #+#    #+#             */
/*   Updated: 2023/11/10 13:14:10 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_invalid_input_arguments(int ac, char **av)
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
	return (0);
}

void	verify_infile_validity(char *infile, t_pipeline *pipeline)
{
	if (access(infile, R_OK) == -1)
	{
		display_error(strerror(errno), infile);
		free_pipeline(pipeline);
		exit (1);
	}
}

int	verify_outfile_validity(char *outfile, t_pipeline *pipeline)
{
	int	out_fd;

	out_fd = -1;
	out_fd = open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (out_fd == -1)
	{
		display_error(strerror(errno), outfile);
		free_pipeline(pipeline);
		exit (1);
	}
	return (out_fd);
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
	return (0);
}

void	err_handler(char *cmd_path, char **cmd_args, t_pipeline *pipeline)
{
	if (ft_strcmp(cmd_path, ERR_DIR_DOESNT_EXIST) == 0)
	{
		display_error(ERR_DIR_DOESNT_EXIST, cmd_args[0]);
		free_file_names(pipeline);
		free_all_commands(pipeline);
		exit (127);
	}
	if (ft_strcmp(cmd_path, ERR_FILE_DOESNT_EXIST) == 0)
	{
		display_error(ERR_FILE_DOESNT_EXIST, cmd_args[0]);
		free_file_names(pipeline);
		free_all_commands(pipeline);
		exit (127);
	}
	if (ft_strcmp(cmd_path, ERR_COMMAND_NOT_FOUND) == 0 || !cmd_path)
	{
		display_error(ERR_COMMAND_NOT_FOUND, cmd_args[0]);
		free_file_names(pipeline);
		free_all_commands(pipeline);
		exit (127);
	}
}
