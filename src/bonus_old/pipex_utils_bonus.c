/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:38:39 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/12 10:27:36 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Initializes the pipeline structure, setting default values for its members.
 * 
 * @param pipeline Pointer to the pipeline structure to be initialized.
 */
void	initialize_pipeline(t_pipeline *pipeline, int num_cmds)
{
	int	i;

	i = 0;
	pipeline->infile = -1;
	pipeline->cmds = (t_command *) malloc(num_cmds * sizeof(t_command));	
	if (!pipeline->cmds)
	{
		//return (NULL);
	}
	pipeline->outfile = -1;
	pipeline->num_cmds = 0;
}

/**
 * Loads commands and initializes the pipeline structure based on the input 
 * arguments.
 * 
 * @param pipeline Pointer to the pipeline structure to be loaded.
 * @param av Array of command line arguments.
 * @param paths Array of paths extracted from the environment.
 */
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
	while (i < num_cmds)
	{
		pipeline->cmds[i] = extract_cmd_opts(av[i + 2], paths);
		i++;
	}
	pipeline->num_cmds = num_cmds;
}

/**
 * Parses command options and retrieves command paths using the available 
 * paths in the environment.
 *
 * In case paths are not available, it verifies the command argument directly,
 * without trying to match with command paths
 *  - env -i (ignore environment)
 *  - unset PATH (remove the PATH variable from the current shell session)
 * 
 * @param stdin_arg Command argument string to be parsed.
 * @param paths Array of paths extracted from the environment.
 * @return A t_command structure containing parsed command details.
 */
t_command	extract_cmd_opts(char *stdin_arg, char **paths)
{
	int			i;
	t_command	command;

	i = 0;
	command.cmd_args = ft_split(stdin_arg, ' ');
	if (!paths)
		command.cmd_path = verify_bash_cmd_path(command.cmd_args[0]);
	else
		command.cmd_path = resolve_cmd_path(paths, command.cmd_args[0]);
	return (command);
}

/**
 * Verifies the existence and permissions of a command path.
 * If the command is valid and accessible, the function returns
 * a dynamically allocated string containing the verified command path.
 * If the command is invalid or inaccessible, appropriate error messages
 * (ERR_DIR_DOESNT_EXIST, ERR_FILE_DOESNT_EXIST, or ERR_COMMAND_NOT_FOUND)
 * are returned.
 * 
 * @param cmd The command (with or without path) to be verified.
 * @return A dynamically allocated string representing the verified command path
 *         if it is valid and accessible. If not, appropriate error messages are
 *         returned. The caller is responsible for freeing the returned string
 *         after use.
 */
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

/**
 * Resolves the command's full path by searching through the specified paths.
 * If the command contains a directory path, it is verified and returned.
 * Otherwise, the function attempts to find the command in the provided paths.
 * 
 * @param cmd The command to be rload_pipelineesolved (either a full path or a 
 *            command name).
 * @param paths An array of paths to search for the command.
 * @return A dynamically allocated string representing the resolved command path
 *         if found and accessible. If not found or inaccessible, appropriate
 *         error messages (ERR_DIR_DOESNT_EXIST, ERR_FILE_DOESNT_EXIST, or
 *         ERR_COMMAND_NOT_FOUND) are returned.
 *         The caller is responsible for freeing the returned string after use.
 */
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
