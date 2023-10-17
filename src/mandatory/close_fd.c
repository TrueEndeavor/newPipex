/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:00:50 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/17 15:01:05 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipeline *pipeline)
{
	if (pipeline == NULL)
		return ;
	close(pipeline->pipe_fds[0]);
	close(pipeline->pipe_fds[1]);
}

void	close_fds(t_pipeline *pipeline)
{
	if (pipeline->infile >= 0)
		close(pipeline->infile);
	if (pipeline->outfile >= 0)
		close(pipeline->outfile);
}
