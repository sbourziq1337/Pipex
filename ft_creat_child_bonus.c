/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_child_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:58:35 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/27 15:58:40 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_first_child(int i, t_cmd *str, int **fd, t_alloc **gc)
{
	close(fd[i][0]);
	str->file = open(str->av[1], O_RDONLY);
	if (str->file < 0)
		ft_erorr_infile(str, i, gc);
	if (dup2(str->file, 0) == -1 || dup2(fd[i][1], 1) == -1)
		(perror("dup2 failed\n"), ft_lstclear(gc), exit(1));
	close(fd[i][1]);
	close(str->file);
	str->path = ft_check_path(str, str->av[i + 1], gc);
	if (str->path == NULL)
	{
		if (ft_strchr(str->av[i + 1], '/') != NULL)
			(perror(str->av[i + 1]), ft_lstclear(gc), exit(127));
		write(2, str->av[i + 1], ft_strlen(str->av[i + 1]));
		write(2, ": command not found\n", 21);
		(ft_lstclear(gc), exit(127));
	}
	str->args = ft_split(str->av[i + 1], ' ', gc);
	if ((execve(str->path, str->args, str->env) < 0))
		ft_exit1(gc, str, i);
}

void	ft_middle_child(int i, t_cmd *str, int **fd, t_alloc **gc)
{
	close(fd[i - 1][1]);
	str->path = ft_check_path(str, str->av[i + 1], gc);
	if (str->path == NULL)
	{
		ft_lstclear(gc);
		if (ft_strchr(str->av[i + 1], '/') != NULL)
			(perror(str->av[i + 1]), exit(127));
		write(2, str->av[i + 1], ft_strlen(str->av[i + 1]));
		(write(2, ": command not found\n", 21), exit(127));
	}
	if (dup2(fd[i - 1][0], 0) == -1)
		(perror("dup2 failed\n"), ft_lstclear(gc), exit(1));
	close(fd[i - 1][0]);
	if (dup2(fd[i][1], 1) == -1)
		(perror("dup2 failed\n"), ft_lstclear(gc), exit(1));
	close(fd[i][1]);
	str->args = ft_split(str->av[i + 1], ' ', gc);
	if ((execve(str->path, str->args, str->env) < 0))
		ft_exit1(gc, str, i);
}

void	ft_last_child(int i, t_cmd *str, int **fd, t_alloc **gc)
{
	close(fd[i - 1][1]);
	str->file = open(str->av[str->ac - 1],
			O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (str->file < 0)
		ft_erorr_outfiel(str, gc);
	if (dup2(fd[i - 1][0], 0) == -1 || dup2(str->file, 1) == -1)
		(perror("dup2"), ft_lstclear(gc), exit(1));
	close(fd[i - 1][0]);
	close(str->file);
	str->path = ft_check_path(str, str->av[str->ac - 2], gc);
	if (str->path == NULL)
	{
		if (ft_strchr(str->av[str->ac - 2], '/') != NULL)
			(perror(str->av[str->ac - 2]), ft_lstclear(gc), exit(127));
		write(2, str->av[str->ac - 2], ft_strlen(str->av[str->ac - 2]));
		(write(2, ": command not found\n", 21), exit(127));
	}
	str->args = ft_split(str->av[str->ac - 2], ' ', gc);
	if ((execve(str->path, str->args, str->env) < 0))
		ft_exit2(gc, str);
}
