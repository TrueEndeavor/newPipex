/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:51:44 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/10 14:37:51 by lannur-s         ###   ########.fr       */
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
 * |   - handle_errors()  - Errors like non-existent dirs handled            |
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
 * Enjoy your journey through PipeX! 🌟
**/

#include "pipex.h"

/**
 * Sets up input/output redirection for child processes based on child index.
 * 
 * @param pipe_fds Array of pipe file descriptors (pipe_fds[READ] and 
 *                 pipe_fds[WRITE]).
 * @param infile File descriptor for input redirection.
 * @param outfile File descriptor for output redirection.
 * @param child_index Index of the child process in the pipeline.
 */
void	setup_child_io(int *pipe_fds, int infile, int outfile, int child_index)
{
	if (child_index == 1)
	{
		close(pipe_fds[READ]);
		dup2(infile, STDIN_FILENO);
		dup2(pipe_fds[WRITE], STDOUT_FILENO);
		close(pipe_fds[WRITE]);
	}
	else if (child_index == 2)
	{
		close(pipe_fds[WRITE]);
		dup2(pipe_fds[READ], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(pipe_fds[READ]);
	}
}

/*
 * Handles errors related to command execution and exits the 
 * program with appropriate status codes.
 * 
 * @param cmd_path Path to the command being executed.
 * @param cmd_args Arguments of the command being executed.
 * @param pipeline Pointer to the pipeline structure containing command details.
 */
void	handle_errors(char *cmd_path, char **cmd_args, t_pipeline *pipeline)
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

/**
 * Configures a child process to execute a command in the given pipeline.
 * 
 * @param pipeline Pointer to the pipeline structure containing command details.
 * @param child_index Index of the child process in the pipeline.
 * @param env The environment variables passed to the child process.
 * @return 0 if the function is successful 
 * (Note: This return value is not used in the current implementation).
 */
int	setup_and_execute_command(t_pipeline *pipeline, int child_index, char **env)
{
	char	*l_cmd_path;
	char	**l_cmd_args;
	int		infile;
	int		outfile;

	l_cmd_path = pipeline->cmds[child_index - 1].cmd_path;
	l_cmd_args = pipeline->cmds[child_index - 1].cmd_args;
	if (child_index == 1)
	{
		infile = pipeline->infile;
		outfile = -1;
	}
	if (child_index == pipeline->num_cmds)
	{
		infile = -1;
		outfile = pipeline->outfile;
	}
	setup_child_io(pipeline->pipe_fds, infile, outfile, child_index);
	handle_errors(l_cmd_path, l_cmd_args, pipeline);
	if (execve(l_cmd_path, l_cmd_args, env) == -1)
	{
		free_all_commands(pipeline);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * Executes commands in the given pipeline using multiple child processes.
 * 
 * @param pipeline Pointer to the pipeline structure containing command details.
 * @param num_children Number of child processes to create and execute.
 * @param env The environment variables passed to the child processes.
 * @return The exit status of the last executed child process.
 */
int	execute_commands(t_pipeline *pipeline, int num_children, char **env)
{
	int		status;
	pid_t	pid;
	int		i;

	i = 0;
	if (pipe(pipeline->pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (i < num_children)
	{
		pid = fork();
		if (pid == 0)
			setup_and_execute_command(pipeline, i + 1, env);
		i++;
	}
	close_pipes(pipeline);
	i = 0;
	while (i < num_children)
	{
		waitpid(pid, &status, 0);
		i++;
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
