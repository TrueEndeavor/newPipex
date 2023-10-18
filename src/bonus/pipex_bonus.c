/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:51:44 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/18 18:40:52 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *  Welcome to lannur-s PipeX! 🚀 Let's visualize the flow of the program:
 *  
 *         +--------------------------------+
 *         |                                |
 *         v                                |
 * +-----------------[Input Processing & Initialization]---------------------+
 * | pipex.h                         - Constants and headers included        |
 * | validator.c                                                             |
 * | - has_invalid_input_arguments() - Input arguments validated             |
 * | libft_combined.c                                                        |
 * | - ft_extract_paths_from_env()   - Paths extracted from environment      |
 * | pipex_utils.c                                                           | 
 * | - initialize_pipeline()         - Pipeline struct initialized with null |
 * | - load_pipeline()               - Pipeline structure loaded with input  |
 * |                                                                         |
 * +-------------------------------------------------------------------------+
 *                                         |
 *                                         v
 * +-----------------------------[Loading Commands & Paths]------------------+
 * | pipex_utils.c                   - Utils to successfully load pipeline   | 
 * | - extract_cmd_opts()    - parses commands  to fetch command paths       |
 * | - verify_bash_cmd_path()- ensures existence & permissions of a command  |
 * | - resolve_cmd_path()    - resolves the command's full path              |
 * |                                                                         |
 * +-------------------------------------------------------------------------+
 *                                         |
 *                                         v
 * +-----------------------------[Executing Commands]------------------------+
 * | main.c                                                                  |
 * | - execute_commands() - Executes multiple commands                       |
 * | - setup_and_execute_command() -  Configuring & executing command        |
 * |   - setup_child_io() - I/O redirection configured for child             |
 * |   - err_handler()  - Errors like non-existent dirs handled            |
 * |                                                                         |
 * +-------------------------------------------------------------------------+
 *                                        |
 *                                        v
 * +------------------------[Cleanup & Resource Management]------------------+
 * | - free_resources.c - Memory and file descriptors freed                  |
 * |   - free_paths()   - Frees memory allocated for paths array
 * |   - free_commands() - Frees memory associated with t_command struture   |
 * |   - free_all_commands() - Frees all memory associated with commands     |
 * |   - free_pipeline() - Frees all resources of pipeline structure         |
 *                         (including commands, file descriptors, and pipes) |
 * |   - close_pipes() - pipes closed
 * |                                                                         |
 * +-------------------------------------------------------------------------+
 *
 * Enjoy your journey through the PipeX project! 🌟
**/

#include "pipex_bonus.h"

void	setup_child_io(int child_index, t_pipeline *pipeline)
{
	if (child_index == 1)
	{
		dup2(pipeline->infile, STDIN_FILENO);
		close(pipeline->infile);
	}
	if (child_index == pipeline->num_cmds)
	{
		dup2(pipeline->outfile, STDOUT_FILENO);
		close(pipeline->outfile);
	}
	if (child_index != 1)
		dup2(pipeline->prev_fd, STDIN_FILENO);
	if (child_index != pipeline->num_cmds)
		dup2(pipeline->pipe_fds[WRITE], STDOUT_FILENO);
	close(pipeline->pipe_fds[WRITE]);
	close(pipeline->pipe_fds[READ]);
}

int	setup_and_execute_command(t_pipeline *pipeline, int child_index, char **env)
{
	char	*l_cmd_path;
	char	**l_cmd_args;

	l_cmd_path = pipeline->cmds[child_index - 1].cmd_path;
	l_cmd_args = pipeline->cmds[child_index - 1].cmd_args;
	setup_child_io(child_index, pipeline);
	err_handler(l_cmd_path, l_cmd_args, pipeline);
	if (execve(l_cmd_path, l_cmd_args, env) == -1)
	{
		free_all_commands(pipeline);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	create_pipe(int *pipe_fds)
{
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	execute_commands(t_pipeline *pipeline, int num_children, char **env)
{
	int		status;
	int		child_index;

	child_index = 1;
	while (child_index <= num_children)
	{
		create_pipe(pipeline->pipe_fds);
		pipeline->pid[child_index] = fork();
		if (pipeline->pid[child_index] == 0)
			setup_and_execute_command(pipeline, child_index, env);
		close(pipeline->pipe_fds[WRITE]);
		if (child_index != 1)
			close(pipeline->prev_fd);
		pipeline->prev_fd = pipeline->pipe_fds[READ];
		child_index++;
	}
	child_index = 1;
	while (child_index <= num_children)
	{
		waitpid(pipeline->pid[child_index], &status, WNOHANG);
		child_index++;
	}
	return (WEXITSTATUS(status));
}

/**
 * PipeX: Executes commands in a pipeline.

 * @param ac Number of command line arguments.
 * @param av Array of command line arguments.
 * @param env Array of environment variables.
 * @return The exit status of the PipeX program.
 *  
 *    +--[Main Function]---------------------+
 *    |  - Input arguments validated         |
 *    |  - Paths extracted from environment  |
 *    |  - Pipeline loaded and executed      |
 *    |  - Resources cleaned up              |
 *    |  - Exit status returned              |
 *    +--------------------------------------+
 * 
**/
int	main(int ac, char **av, char **env)
{
	t_pipeline	pipeline;
	char		**paths;
	int			status;

	if (has_invalid_input_arguments(ac, av) == 1)
		exit (EXIT_FAILURE);
	paths = ft_extract_paths_from_env(env);
	if (!paths)
		free_paths(paths);
	pipeline.num_cmds = ac - 3;
	load_pipeline(&pipeline, av, paths);
	if (paths)
		free_paths(paths);
	status = execute_commands(&pipeline, pipeline.num_cmds, env);
	free_pipeline(&pipeline);
	return (status);
}
