/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:43:56 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/17 15:00:32 by lannur-s         ###   ########.fr       */
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

void	free_pipeline(t_pipeline *pipeline)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (pipeline == NULL)
		return ;
	if (pipeline->infile != -1)
		close(pipeline->infile);
	if (pipeline->outfile != -1)
		close(pipeline->outfile);
	free_all_commands(pipeline);
	close_pipes(pipeline);
}
