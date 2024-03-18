/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 07:34:39 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/18 09:39:53 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_son_process(t_var_parsed_table *arg, t_input **struct_input)
{
	int	fdin;
	int	fdout;
	int control_fdin;
	int control_fdout;
	int	control;

	fdin = 0;
	fdout = 0;
	control_fdin = 0;
	control_fdout = 0;
	control = TRUE;
	if (arg->fd_in != 0)//si no es la entrada estandar redirigimos lo que sea como entrada estandar
	{
		fdin = dup2(arg->fd_in, STDIN_FILENO);
		control_fdin = 1;
	}
	else
		fdin = arg->fd_in;
	if (fdin < 0)
	{
		printf("el fdin en el hijo es de %d\n", fdin);
		printf("el fdin que viene de la estructura en el hijo es de %d\n", arg->fd_in);
		printf("son process 1\n");
		ft_exit(1);
	}
	if (arg->fd_error != -1)
		fdout = dup2(arg->fd_out, STDERR_FILENO);
	else if (arg->fd_out != 1)//si no es la salida estandar redirigimos lo que sea como salida estandar
	{
		printf("el fd del outfile es %d\n", arg->fd_out);
		if(fcntl(arg->fd_out, F_GETFD) != -1)
			printf("se trata de un fd valido\n");
		fdout = dup2(arg->fd_out, STDOUT_FILENO);
		control_fdout = 1;
	}
	else
		fdout = arg->fd_out;
	if (fdout < 0)
	{
		printf("son process 2\n");
		ft_exit(1);
	}
	if (control_fdin == 1)
	{
		if (close(arg->fd_in) < 0)
		{
			printf("son process 3\n");
			ft_exit(1);
		}
	}
	if (control_fdout == 1)
	{
		if (close(arg->fd_out) < 0)
		{
			printf("son process 4\n");
			ft_exit(1);
		}
	}
	ft_built_in(arg->cmd_splited, struct_input, &control);
	if (control == FALSE)
	{
		write(2, "salimos por el buit in\n", 23);
		exit(0);
	}
	if (execve(arg->path, arg->cmd_splited, arg->env) == -1)
	{
		printf("son process 5\n");
		ft_exit(1);
	}
}

t_var_parsed_table	*father_process(t_var_parsed_table *cmd, int fd[2])
{
		if ((cmd->fd_in != 0 && cmd->fd_in != -1))//si no es ni la entrada estandar ni -1 (hay que asignarle pipe)
		{
			if (close(cmd->fd_in) < 0)
			{
				printf("father process 1\n");
				ft_exit(1);
			}
		}
		if (close(fd[WRITE]) < 0)//cerramos el pipe de escritura (ya se le a asignado el hijo)
		{
			printf("father process 2\n");
			ft_exit(1);
		}
		if (cmd->next)//si existe el siguiente y no tiene un fd asignado (que pasa si hay un siguiente pero si tiene un fd asignado?)
		{
			cmd->next->fd_in = fd[READ];
		}
		else
		{
			close(fd[READ]);
		}
	cmd = cmd->next;
	return (cmd);
	
}

void	ft_make_process(t_var_parsed_table *cmd_list, int fd[2], t_input **struct_input)
{
	while (cmd_list)
	{
		if (pipe(fd) < 0)//hacemos el pipe
		{
			printf("make process 1\n");
			ft_exit(1);
		}
		cmd_list->pid = fork();//forkeamos
		if (cmd_list->pid < 0)
		{
			printf("make process 2\n");
			ft_exit(1);
		}
		else if (cmd_list->pid == 0 && !cmd_list->next)//en el proceso hijo si es el ultimo nodo...
		{
			if (cmd_list->prev)//si exite uno anterior...
			{
				if (waitpid(cmd_list->prev->pid, NULL, 0) == 0)//... y el proceso anterior a terminado
				{
					if (close(fd[READ]) < 0)
					{
						printf("make process 3\n");
						ft_exit(1);
					}
					if (close(fd[WRITE]) < 0)
					{
						printf("make process 4\n");
						ft_exit(1);
					}
				}
			}
			else//si no existe uno anterior ni siguiente cerramos todos los pipes
			{
				if (close(fd[READ]) < 0)
				{
					printf("make process 3\n");
					ft_exit(1);
				}
				if (close(fd[WRITE]) < 0)
				{
					printf("make process 4\n");
					ft_exit(1);
				}
			}
			ft_son_process(cmd_list, struct_input);// y entramos al hijo
		}
		else if (cmd_list->pid == 0)// si estamos en el hijo pero si existe un siguiente...
		{
			if (close(fd[READ]) < 0)//cerramos el pipe de escritura
			{
				printf("make process 5\n");
				ft_exit(1);
			}
			if(cmd_list->fd_out == -1)//si no tiene un fd asignado le damos el pipe de escritura
			{
				cmd_list->fd_out = fd[WRITE];
			}
			ft_son_process(cmd_list, struct_input);// y entramos al hijo
		}
		else
			cmd_list = father_process(cmd_list, fd);
	}
	while(waitpid(-1, NULL, 0) > 0)
		;
}
