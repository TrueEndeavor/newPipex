/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:38:39 by lannur-s          #+#    #+#             */
/*   Updated: 2023/11/10 14:47:26 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialize_pipeline(t_pipeline *pipeline, int num_cmds)
{
	int	i;

	i = 0;
	pipeline->num_cmds = num_cmds;
	pipeline->cmds = (t_command *) malloc (num_cmds * sizeof(t_command));
	while (i < num_cmds)
	{
		pipeline->cmds[i].cmd_args = NULL;
		pipeline->cmds[i].cmd_path = NULL;
		i++;
	}
	pipeline->infile = NULL;
	pipeline->outfile = NULL;
	pipeline->limiter = NULL;
}

void	load_pipeline(t_pipeline *pipeline, char **av, char **paths)
{
	int		num_cmds;
	int		last;
	int		i;
	int		idx;
	int		out_fd;

	num_cmds = pipeline->num_cmds;
	idx = num_cmds + 2;	
	last = num_cmds + 2;
	i = 0;
	initialize_pipeline(pipeline, num_cmds);
	pipeline->infile = ft_strdup(av[1]);
	pipeline->outfile = ft_strdup(av[idx]);	
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		pipeline->here_doc = 1;
		pipeline->infile = "/tmp/here_doc";		
		pipeline->limiter = ft_strjoin(av[2], "\n");
		i++;
		out_fd = open(av[last], HEREDOC_OUTFILE_MODE, OUTFILE_PERM);
	}
	else
	{
		pipeline->here_doc = 0;
	}
	while (i < num_cmds)
	{
		if (!av[i + 2] || ft_strcmp(av[i + 2], "") == 0)
		{
			display_error(ERR_BAD_ARGUMENTS_COUNT, PIPEX_USAGE);
			free_pipeline(pipeline);
			exit (1);
		}	
		pipeline->cmds[i] = extract_cmd_opts(av[i + 2], paths);
		i++;
	}
	pipeline->num_cmds = num_cmds - pipeline->here_doc;
}

t_command	extract_cmd_opts(char *stdin_arg, char **paths)
{
	int			i;
	t_command	command;

	i = 0;
	command.cmd_args = ft_split(stdin_arg, ' ');
	if (!paths || !command.cmd_args[0] || command.cmd_args[0][0] == '\0')
		command.cmd_path = verify_bash_cmd_path(command.cmd_args[0]);
	else
		command.cmd_path = resolve_cmd_path(paths, command.cmd_args[0]);
	return (command);
}

char	*verify_bash_cmd_path(char *cmd)
{
	if (cmd == NULL)
		return (ft_strdup(ERR_COMMAND_NOT_FOUND));
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
