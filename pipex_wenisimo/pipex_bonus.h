/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:04:14 by anurtiag          #+#    #+#             */
/*   Updated: 2024/01/08 08:40:02 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "lib/ft_printf/libftprintf.h"
# include "lib/Libft/libft.h"
# include "lib/gnl/get_next_line.h"

# ifndef READ
#  define READ 0
# endif
# ifndef WRITE
#  define WRITE 1
# endif

typedef struct s_data
{
	char			*path;
	char			**cmd;
	struct s_data	*next;
	struct s_fd		*fd;
}				t_data;

typedef struct s_fd
{
	int				fdin;
	int				fdout;
}				t_fd;

void	ft_exit(int i);
void	error_handle(int argc, char **argv);
char	*ft_get_path(char **env, char *cmd);
char	**ft_get_cmd(char *s1);
t_data	*cmd_handle(char **argv, char **env, int i, t_data *cmd);
char	*ft_get_path_line(char **env);
void	ft_here_doc(char *argv[], int fd);
void	ft_pipex(int argc, char **argv, char **env);
void	ft_here_doc_errors(int argc, char **argv);
void	ft_son_process(t_data *arg);
void	ft_make_list(t_data **lst, int i, char **argv, char **env);
void	ft_close_fd(t_data *data, int (*fd)[2], int lim, int i);
void	freeall(char **str);
void	free_here_doc(char *delimiter, char *output, char *line, int outfile);
t_data	*father_process(t_data *cmd, int fd[2], int pid);
void	ft_make_process(t_data *cmd, int fd[2], int pid);
t_data	*set_data(int argc, char **argv, char **env, t_data *cmd);
t_fd	*fd_handle(int i, int argc, char **argv);
void	free_nodes(t_data *cmd);
void	ft_make_process(t_data *cmd, int fd[2], int pid);
void	file_permissions(char *name, int type);

#endif