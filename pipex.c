/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:57:56 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/27 15:57:58 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		}
		ft_close_file_parnet((*i), fd);
		(*i)++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		**fd;
	t_cmd	str ;
	t_alloc	*gc ;
	int		status;
	int		i;

	i = 1;
	str.ac = argc;
	str.av = argv;
	str.env = envp;
	status = 0;
	gc = NULL;
	if (argc == 5)
	{
		fd = gc_malloc(&gc, (argc - 2) * sizeof(int *));
		str.id = gc_malloc(&gc, (argc - 2) * sizeof(int));
		ft_creat_pipe(i, argc, fd, &gc);
		ft_all_child(&str, &gc, &i, fd);
		ft_waiting_child(i, str.id, &status);
		ft_lstclear(&gc);
	}
	else
		write(1, "Usage: ./pipex input_file cmd1 cmd2 output_file\n", 49);
	return ((status >> 8) & 0xFF);
}
