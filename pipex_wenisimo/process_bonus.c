/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 07:06:24 by anurtiag          #+#    #+#             */
/*   Updated: 2023/12/26 07:21:08 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_son_process(t_data *arg)
{
	int	fdin;
	int	fdout;

	fdin = dup2(arg->fd->fdin, STDIN_FILENO);
	if (fdin < 0)
		ft_exit(1);
	fdout = dup2(arg->fd->fdout, STDOUT_FILENO);
	if (fdout < 0)
		ft_exit(1);
	if (close(arg->fd->fdin) < 0)
		ft_exit(1);
	if (close(arg->fd->fdout) < 0)
		ft_exit(1);
	if (execve(arg->path, arg->cmd, NULL) == -1)
		ft_exit(1);
}

t_data	*father_process(t_data *cmd, int fd[2], int pid)
{
	if (close(cmd->fd->fdin) < 0)
		ft_exit(1);
	if (close(fd[WRITE]) < 0)
		ft_exit(1);
	if (cmd->next)
		cmd->next->fd->fdin = fd[READ];
	else
		close(fd[READ]);
	if (waitpid(pid, NULL, 0) == -1)
		ft_exit(1);
	cmd = cmd->next;
	return (cmd);
}

void	ft_make_process(t_data *cmd, int fd[2], int pid)
{
	while (cmd)
	{
		if (pipe(fd) < 0)
			ft_exit(1);
		pid = fork();
		if (pid < 0)
			ft_exit(1);
		else if (pid == 0 && !cmd->next)
		{
			if (close(fd[READ]) < 0)
				ft_exit(1);
			if (close(fd[WRITE]) < 0)
				ft_exit(1);
			ft_son_process(cmd);
		}
		else if (pid == 0)
		{
			if (close(fd[READ]) < 0)
				ft_exit(1);
			cmd->fd->fdout = fd[WRITE];
			ft_son_process(cmd);
		}
		else
			cmd = father_process(cmd, fd, pid);
	}
}
