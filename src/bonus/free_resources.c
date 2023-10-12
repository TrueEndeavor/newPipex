/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:43:56 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/12 14:43:38 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Frees memory allocated for paths array.
 * 
 * @param paths Array of paths to be deallocated.
 */
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

/**
 * Frees memory associated with command arguments and paths in a t_command 
 * structure.
 * 
 * @param command Pointer to the t_command structure containing command details.
 */
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

/**
 * Frees all memory associated with commands in the pipeline structure.
 * 
 * @param pipeline Pointer to the pipeline structure containing commands.
 */
void	free_all_commands(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->num_cmds)
	{
		if (&(pipeline->cmds[i]))
			free_commands(&(pipeline->cmds[i]));
		i++;
	}
}

/**
 * Frees resources allocated for the pipeline structure, including commands, 
 * file descriptors, and pipes.
 * 
 * @param pipeline Pointer to the pipeline structure to be freed.
 */
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

/**
 * Closes the pipe file descriptors in the given pipeline structure.
 * If the pipeline pointer is NULL, the function simply returns without taking 
 * any action.
 * 
 * @param pipeline Pointer to the pipeline structure containing pipe file 
 * descriptors.
 */
void	close_pipes(t_pipeline *pipeline)
{
	if (pipeline == NULL)
		return ;
	close(pipeline->pipe_fds[0]);
	close(pipeline->pipe_fds[1]);
}
