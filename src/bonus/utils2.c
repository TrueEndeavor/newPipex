/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:12:57 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/18 19:14:38 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void execute_here_doc(t_pipeline *pipeline)
{
	char *line = NULL;
    size_t len = 0;

    ft_putstr_fd("Please enter input (type '", STDERR_FILENO);
    ft_putstr_fd(pipeline->limiter, STDERR_FILENO);
    ft_putstr_fd("' to end):\n", STDERR_FILENO);

    while (get_next_line(0)) != -1)
    {
        if (ft_strcmp(line, pipeline->limiter) == 0)
            break;

        // Process the input line here if needed

        free(line);
        line = NULL;
        len = 0;
    }

    if (line)
        free(line);