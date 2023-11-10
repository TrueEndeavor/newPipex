/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:19:04 by lannur-s          #+#    #+#             */
/*   Updated: 2023/11/10 12:55:06 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

/* *****************************   INCLUDES   ******************************* */
/* For function open() */
# include <fcntl.h>

/* close(), read(), write(), access(), dup(), dup2(), execve(), fork(), 
 * pipe(), getpid(), unlink(), wait()  */
# include <unistd.h>

/* malloc(), free(), exit() */
# include <stdlib.h>

/* perror(), pid_t */
# include <stdio.h>

/* waitpid() */
# include <sys/wait.h>

/* errno */
# include <errno.h>

/* Libft functions */
# include "libft.h"

/* *****************************   STRUCTURES   *******************************/
typedef struct Command
{
	char		*cmd_path;
	char		**cmd_args;
}	t_command;

typedef struct Pipeline
{
	int			num_cmds;
	int			pipe_fds[2];
	int			prev;
	char		*infile;
	char		*outfile;
	t_command	*cmds;
}	t_pipeline;

/* *****************************   CONSTANTS   ********************************/

/* This program needs atleast 5 parameters minimum on the command line. 
*/
# define MIN_COMMAND_LINE_ARGS 5

# define READ 0
# define WRITE 1
# define COMMAND_NOT_FOUND 127

/* **************************   ERROR MESSAGES   ******************************/

# define ERR_BAD_ARGUMENTS_COUNT "Bad number of arguments"
# define ERR_FILE_DOESNT_EXIST "No such file or directory"
# define ERR_DIR_DOESNT_EXIST "not a directory"
# define ERR_PERMISSION_DENIED "Permission denied"
# define ERR_COMMAND_NOT_FOUND "command not found"
# define PIPEX_USAGE "./pipex infile \"cmd1 opts\" \"cmd2 opts\" outfile"

/* ****************************   FUNCTIONS   *********************************/
int			is_invalid_input_arguments(int ac);
int			display_error(char *error, char *usage);
void		err_handler(char *cmd_path, char **cmd_args, t_pipeline *pipeline);
void		verify_infile_validity(char *infile, t_pipeline *pipeline);
int			verify_outfile_validity(char *outfile, t_pipeline *pipeline);

void		load_pipeline(t_pipeline *pipeline, char **av, char **paths);
t_command	extract_cmd_opts(char *stdin_arg, char **paths);
char		*resolve_cmd_path(char **paths, char *cmd);
char		*verify_bash_cmd_path(char *cmd);

void		free_pipeline(t_pipeline *pipeline);
void		free_paths(char **paths);
void		free_all_commands(t_pipeline *pipeline);
void		free_commands(t_command *command);
void		free_file_names(t_pipeline *pipeline);

void		close_pipes(t_pipeline *pipeline);

#endif
