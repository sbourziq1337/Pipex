/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:06:54 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/23 17:06:58 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_alloc
{
	void			*data;
	struct s_alloc	*next;
}					t_alloc;

typedef struct s_cmd
{
	int				*id;
	int				file;
	int				ac;
	char			**av;
	char			*path;
	char			**args;
	char			**access_path;
	char			**env;
}					t_cmd;

char				**ft_split(char *str, char c, t_alloc **gc);
char				*ft_strjoin(t_alloc **gc, char const *s1, char const *s2);
char				*ft_check_path(t_cmd *ptr, char *argv, t_alloc **gc);
int					ft_strlen(char const *s1);
void				ft_creat_pipe(int i, int argc, int **fd, t_alloc **gc);
char				*ft_strchr(char *s, int c);
void				ft_first_child(int i, t_cmd *str, int **fd, t_alloc **gc);
void				ft_last_child(int i, t_cmd *str, int **fd, t_alloc **gc);
void				ft_middle_child(int i, t_cmd *str, int **fd, t_alloc **gc);
void				ft_close_file_parnet(int i, int **fd);
void				ft_waiting_child(int i, int *id, int *status);
void				ft_fork(int i, int *id, t_alloc **gc);
t_alloc				*ft_lstlast(t_alloc *lst);
t_alloc				*ft_lstnew(void *ptr);
void				ft_lstadd_back(t_alloc **lst, t_alloc *new);
void				ft_lstclear(t_alloc **lst);
void				*gc_malloc(t_alloc **gc, int size);
void				ft_erorr_infile(t_cmd *str, int i, t_alloc **gc);
void				ft_erorr_outfiel(t_cmd *str, t_alloc **gc);
void				ft_erorr_cmmd(t_cmd *ptr, int i, t_alloc **gc);
int					ft_strncmp(char *str, char *path, int line);
int					ft_chck_spase(char *str);
void				ft_exit2(t_alloc **gc, t_cmd *str);
void				ft_exit1(t_alloc **gc, t_cmd *str, int i);
char				**ft_helper_find_path(t_alloc **gc, t_cmd *ptr);
void				ft_access_to_path(t_alloc **gc, t_cmd *ptr, char **str,
						char *argv);
void				ft_empty(char *av);

#endif
