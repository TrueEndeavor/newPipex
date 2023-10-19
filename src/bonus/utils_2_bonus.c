/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:12:57 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/19 16:12:18 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_limiter(char *str, char *limiter)
{
	size_t	length;

	length = ft_strlen(str);
	if (length > 0 && str[length - 1] == '\n')
	{
		str[length - 1] = '\0';
	}
	if (ft_strcmp(str, limiter) == 0)
		return (1);
	return (0);
}

void	execute_here_doc(t_pipeline *pipeline)
{
	char	*line;
	int		temp_fd;
	size_t     len;

	line = NULL;
	len = ft_strlen(pipeline->limiter);
	ft_putstr_fd("Please enter heredoc content (type '", STDERR_FILENO);
	ft_putstr_fd(pipeline->limiter, STDERR_FILENO);
	ft_putstr_fd("' to end):\n", STDERR_FILENO);
	temp_fd = open(pipeline->infile_name, O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (temp_fd == -1)
	{
		display_error(ERR_FILE_DOESNT_EXIST, pipeline->infile_name);
		close_fds(pipeline);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
   		//if (ft_strlen(line)-1 == len && is_limiter(line, pipeline->limiter))
   		dprintf(1, "...%d\n", ft_strcmp(line, pipeline->limiter));
   		if (ft_strcmp(line, pipeline->limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, temp_fd);
		if (line)
			free (line);
	}
	close(temp_fd);
}
