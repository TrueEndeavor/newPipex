/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:43:56 by lannur-s          #+#    #+#             */
/*   Updated: 2023/11/10 11:14:20 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (paths == NULL)
		return ;
	if (paths != NULL)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			i++;
		}
		free(paths);
	}
}

void	free_commands(t_command *command)
{
	int	i;

	if (command->cmd_args)
	{
		i = 0;
		while (command->cmd_args[i])
		{
			if (command->cmd_args[i])
				free(command->cmd_args[i]);
			i++;
		}
		free(command->cmd_args);
	}
	if (command->cmd_path)
	{
		free(command->cmd_path);
	}
}

void	free_all_commands(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->num_cmds)
	{
		if (&(pipeline->cmds[i]))
		{
			free_commands(&(pipeline->cmds[i]));
		}
		i++;
	}
	free(pipeline->cmds);
}

void	free_file_names(t_pipeline *pipeline)
{
	if (pipeline->infile)
		free(pipeline->infile);
	if (pipeline->outfile)
		free(pipeline->outfile);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (pipeline == NULL)
		return ;
	free_file_names(pipeline);
	free_all_commands(pipeline);
	close_pipes(pipeline);
}
