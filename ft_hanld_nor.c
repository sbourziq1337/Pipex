/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hanld_nor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:03:56 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/23 17:04:00 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_creat_pipe(int i, int argc, int **fd, t_alloc **gc)
{
	while (i <= (argc - 3))
	{
		fd[i] = gc_malloc(gc, (2 * sizeof(int)));
		i++;
	}
	i = 1;
	while (i <= (argc - 3))
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe failed");
			ft_lstclear(gc);
			exit(1);
		}
		i++;
	}
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != 9)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		else
			i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

void	ft_close_file_parnet(int i, int **fd)
{
	if (i == 1)
		close(fd[i][1]);
	else
	{
		close(fd[i][1]);
		close(fd[i - 1][0]);
	}
}

void	ft_waiting_child(int i, int *id, int *status)
{
	int	x;

	x = 1;
	while (x < i)
	{
		waitpid(id[x], status, 0);
		x++;
	}
}

void	ft_fork(int i, int *id, t_alloc **gc)
{
	id[i] = fork();
	if (id[i] == -1)
	{
		perror("fork failed");
		(ft_lstclear(gc), exit(1));
	}
}
