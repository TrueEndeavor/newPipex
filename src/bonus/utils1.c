/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:55:56 by lannur-s          #+#    #+#             */
/*   Updated: 2023/10/18 19:09:10 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*str_johnny(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dst;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_calloc(sizeof(char), (len + 1));
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

void	je_souffre_trop(t_pipex *pipex)
{
	pipex->str_end = str_johnny(pipex->limiteur, "\n");
	if (!pipex->str_end)
		return (ft_printf("Function str_johnny fail\n"),
			exit(1));
}

void	ft_here_doc(t_pipeline *pipeline)
{
	char	*str;
	int		fd;

	je_souffre_trop(pipeline);
	fd = open(pipeline->in_name, O_RDWR | O_CREAT, 0664);
	if (fd == -1)
		return (ft_printf("Fail open here_doc\n"), exit(EXIT_FAILURE));
	while (1)
	{
		str = get_next_line(0, 0);
		if (!str)
			break ;
		if (!ft_strcmp(str, pipeline->str_end))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
	get_next_line(0, 1);
	free(pipeline->str_end);
	close(fd);
}
