/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 07:34:39 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/26 15:56:25 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//executes the command and redirects the fds
void	ft_son_utils(int (*fd)[2], int (*control_fd)[2], \
t_var_parsed_table *arg)
{
	*fd[READ] = 0;
	*fd[WRITE] = 0;
	*control_fd[READ] = 0;
	*control_fd[WRITE] = 0;
	if (arg->fd_in != 0)
	{
		*fd[READ] = dup2(arg->fd_in, STDIN_FILENO);
		*control_fd[READ] = 1;
	}
	else
		*fd[READ] = arg->fd_in;
	if (*fd[READ] < 0)
		exit(1);
	if (arg->fd_error != -1)
		*fd[WRITE] = dup2(arg->fd_out, STDERR_FILENO);
	else if (arg->fd_out != 1)
	{
		*fd[WRITE] = dup2(arg->fd_out, STDOUT_FILENO);
		*control_fd[WRITE] = 1;
	}
	else
		*fd[WRITE] = arg->fd_out;
	if (*fd[WRITE] < 0)
		exit(1);
}

void	ft_son_process(t_var_parsed_table *arg, \
t_input **struct_input, t_step *step)
{
	int	fd[2];
	int	control_fd[2];
	int	control;

	control = TRUE;
	ft_son_utils(&fd, &control_fd, arg);
	if (control_fd[READ] == 1)
		if (close(arg->fd_in) < 0)
			exit(1);
	if (control_fd[WRITE] == 1)
		if (close(arg->fd_out) < 0)
			exit(1);
	ft_built_in(arg, struct_input, &control, 1, step);
	if (control == FALSE)
		exit(0);
	if (execve(arg->path, arg->cmd_splited, arg->env) == -1)
		exit(1);
}

//this function closes the used fds and assigns the pipe fd
t_var_parsed_table	*father_process(t_var_parsed_table *cmd, int fd[2])
{
	if ((cmd->fd_in != 0 && cmd->fd_in != -1))
		if (close(cmd->fd_in) < 0)
			exit(1);
	if ((cmd->fd_out != 1 && cmd->fd_out != -1))
		if (close(cmd->fd_out) < 0)
			exit(1);
	if (close(fd[WRITE]) < 0)
		exit(1);
	if (cmd->next)
		cmd->next->fd_in = fd[READ];
	else
		close(fd[READ]);
	cmd = cmd->next;
	return (cmd);
}

t_var_parsed_table	*ft_process_utils(t_var_parsed_table *cmd_list, int fd[2], \
t_input **struct_input, t_step *step)
{
	if (cmd_list->pid == 0 && !cmd_list->next)
	{
		if (cmd_list->prev)
		{
			if (waitpid(cmd_list->prev->pid, NULL, 0) == 0)
				ft_close_pipes(fd);
		}
		else
			ft_close_pipes(fd);
		ft_son_process(cmd_list, struct_input, step);
	}
	else if (cmd_list->pid == 0)
	{
		if (close(fd[READ]) < 0)
			exit(1);
		if (cmd_list->fd_out == -1)
			cmd_list->fd_out = fd[WRITE];
		ft_son_process(cmd_list, struct_input, step);
	}
	else
		cmd_list = father_process(cmd_list, fd);
	return (cmd_list);
}

void	ft_make_process(t_var_parsed_table *cmd_list, int fd[2], \
t_input **struct_input, t_step *step)
{
	int		status;
	char	*tmp;

	status = 0;
	while (cmd_list)
	{
		if (pipe(fd) < 0)
			exit(1);
		cmd_list->pid = fork();
		if (cmd_list->pid < 0)
			exit(1);
		cmd_list = ft_process_utils(cmd_list, fd, struct_input, step);
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	tmp = ft_itoa(status);
	ft_var_found(&(*struct_input)->ent_var, "?", tmp);
	free(tmp);
}
