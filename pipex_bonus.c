/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:58:13 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/27 15:58:17 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_first_child_herdoc(int i, t_cmd *str, int **fd, t_alloc **gc)
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

void	ft_all_child_herdoc(t_cmd *str, t_alloc **gc, int *i, int **fd)
{
	char	*her;

	(write(1, "> ", 2), her = get_next_line(0));
	while (her != NULL)
	{
		if ((ft_strcmp(str->av[2], her) == 0))
			break ;
		(write(1, "> ", 2), write(fd[1][1], her, ft_strlen(her)));
		(free(her), her = get_next_line(0));
	}
	(close(fd[1][1]), free(her));
	(*i) = (*i) + 1;
	while ((str->av)[(*i) + 2] != NULL)
	{
		ft_fork((*i), str->id, gc);
		if ((str->id)[(*i)] == 0)
		{
			if ((*i) == 2)
				ft_first_child_herdoc((*i), str, fd, gc);
			else if ((str->av)[(*i) + 3] == NULL)
				ft_last_child((*i), str, fd, gc);
		}
		ft_close_file_parnet((*i), fd);
		(*i)++;
	}
}

void	ft_all_child(t_cmd *str, t_alloc **gc, int *i, int **fd)
{
	while ((str->av)[(*i) + 2] != NULL)
	{
		ft_fork((*i), str->id, gc);
		if ((str->id)[(*i)] == 0)
		{
			if ((*i) == 1)
				ft_first_child((*i), str, fd, gc);
			else if ((str->av)[(*i) + 3] == NULL)
				ft_last_child((*i), str, fd, gc);
			else
				ft_middle_child((*i), str, fd, gc);
		}
		ft_close_file_parnet((*i), fd);
		(*i)++;
	}
}

void	ft_all_variable(t_cmd *str, int arc, char **arv, char **envp)
{
	str->ac = arc;
	str->av = arv;
	str->env = envp;
}

int	main(int argc, char **argv, char **envp)
{
	int		**fd;
	t_cmd	str;
	t_alloc	*gc;
	int		status;
	int		i;

	i = 1;
	ft_all_variable(&str, argc, argv, envp);
	status = 0;
	gc = NULL;
	if (argc >= 5)
	{
		fd = gc_malloc(&gc, (argc - 2) * sizeof(int *));
		str.id = gc_malloc(&gc, (argc - 2) * sizeof(int));
		ft_creat_pipe(i, argc, fd, &gc);
		if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && (argc == 6))
			ft_all_child_herdoc(&str, &gc, &i, fd);
		else
			ft_all_child(&str, &gc, &i, fd);
		ft_waiting_child(i, str.id, &status);
		ft_lstclear(&gc);
	}
	else
		write(1, "Usage: ./pipex input_file cmd1 cmd2 output_file\n", 49);
	return ((status >> 8) & 0xFF);
}
