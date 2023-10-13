/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:38:39 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/13 15:14:19 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialize_pipeline(t_pipeline *pipeline, int num_cmds)
{
	int	i;

	i = 0;
	pipeline->infile = -1;
	pipeline->cmds = (t_command *) malloc(num_cmds * sizeof(t_command));
	while (i < num_cmds)
	{
		pipeline->cmds[i].cmd_args = NULL;
		pipeline->cmds[i].cmd_path = NULL;
		i++;
	}
	pipeline->outfile = -1;
	pipeline->num_cmds = 0;
}


void	load_pipeline(t_pipeline *pipeline, char **av, char **paths)
{
	int		num_cmds;
	int		i;
	int		idx;

	num_cmds = pipeline->num_cmds;
	idx = num_cmds + 2;
	i = 0;
	initialize_pipeline(pipeline, num_cmds);
	pipeline->outfile = open(av[idx], O_TRUNC | O_CREAT | O_RDWR, OUTFILE_PERM);
	if (errno == EACCES)
		display_error(ERR_PERMISSION_DENIED, av[num_cmds + 3]);
	pipeline->infile = open(av[1], O_RDONLY);
	if (num_cmds >= 1024)
		return (display_error("Pipex: too many commands\n", ""), exit(EXIT_FAILURE));
	while (i < num_cmds)
	{
		pipeline->cmds[i] = extract_cmd_opts(av[i + 2], paths);
		i++;
	}
	pipeline->num_cmds = num_cmds;
}


t_command	extract_cmd_opts(char *stdin_arg, char **paths)
{
	t_command	command;

	command.cmd_args = ft_split(stdin_arg, ' ');
	if (!paths)
		command.cmd_path = verify_bash_cmd_path(command.cmd_args[0]);
	else
		command.cmd_path = resolve_cmd_path(paths, command.cmd_args[0]);
	return (command);
}


char	*verify_bash_cmd_path(char *cmd)
{
	if ((access(cmd, F_OK | X_OK) != 0))
	{
		if (errno == ENOTDIR)
			return (ft_strdup(ERR_DIR_DOESNT_EXIST));
		if (errno == ENOENT)
			return (ft_strdup(ERR_FILE_DOESNT_EXIST));
		else
			return (ft_strdup(ERR_COMMAND_NOT_FOUND));
	}
	return (ft_strdup(cmd));
}


char	*resolve_cmd_path(char **paths, char *cmd)
{
	char	*full_path;
	char	*file_name;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/') == NULL)
	{
		while (*paths)
		{
			full_path = ft_strjoin(*paths, "/");
			file_name = ft_strjoin(full_path, cmd);
			free(full_path);
			if (access(file_name, F_OK | X_OK) == 0)
			{
				return (file_name);
			}
			if (errno == ENOTDIR)
				return (ft_strdup(ERR_DIR_DOESNT_EXIST));
			free(file_name);
			paths++;
		}
	}
	else
		return (verify_bash_cmd_path(cmd));
	return (ft_strdup(ERR_COMMAND_NOT_FOUND));
}
