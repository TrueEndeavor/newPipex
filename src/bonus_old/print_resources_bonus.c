/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_resources_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:43:56 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/12 13:27:10 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_paths(char **paths)
{
	int	i;

	i = 0;
	if (paths == NULL)
		return ;
	if (paths != NULL)
	{
		while (paths[i] != NULL)
		{
			dprintf(1, "paths[i]=%s\n", paths[i]);
			i++;
		}
		free(paths);
	}
}

void	print_commands(t_command *command)
{
	int	i;

	if (command->cmd_args)
	{
		i = 0;
		while (command->cmd_args[i])
		{
			if (command->cmd_args[i])
				dprintf(1, "command->cmd_args[i]=%s\n", command->cmd_args[i]);
			i++;
		}
		free(command->cmd_args);
	}
	if (command->cmd_path)
	{
		dprintf(1, "command->cmd_path=%s\n", command->cmd_path);
	}
}

void	print_all_commands(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->num_cmds)
	{
		if (&(pipeline->cmds[i]))
			print_commands(&(pipeline->cmds[i]));
		i++;
	}
}

void	print_pipeline(t_pipeline *pipeline)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (pipeline == NULL)
		return ;
	if (pipeline->infile != -1)
		dprintf(1, "pipeline->infile=%d\n", pipeline->infile);
	if (pipeline->outfile != -1)
		dprintf(1, "pipeline->outfile=%d\n", pipeline->outfile);
	print_all_commands(pipeline);
	print_pipes(pipeline);
}

void	print_pipes(t_pipeline *pipeline)
{
	if (pipeline == NULL)
		return ;
	dprintf(1, "<---child #--->\n");
	dprintf(1, "pipeline->pipe_fds[0]=%d\n", pipeline->pipe_fds[0]);
	dprintf(1, "pipeline->pipe_fds[1]=%d\n", pipeline->pipe_fds[1]);
}
