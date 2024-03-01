/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:16:40 by anurtiag          #+#    #+#             */
/*   Updated: 2024/01/09 07:03:53 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "lib/ft_printf/libftprintf.h"
# include "lib/Libft/libft.h"

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
void	ft_son_process(t_data *arg);
void	freeall(char **str);
t_data	*father_process(t_data *cmd, int fd[2], int pid);
void	ft_make_process(t_data *cmd, int fd[2], int pid);
t_data	*set_data(int argc, char **argv, char **env, t_data *cmd);
t_fd	*fd_handle(int i, int argc, char **argv);
void	free_nodes(t_data *cmd);
void	file_permissions(char *name, int type);

#endif