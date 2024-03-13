/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:13:42 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/13 12:20:18 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// char	**ft_get_cmd(char *s1)
// {
// 	char	**cmd;

// 	cmd = ft_split(s1, ' ');
// 	if (!cmd)
// 		ft_exit(1);
// 	return (cmd);
// }

// t_data	*set_data(int argc, char **argv, char **env, t_data *cmd)
// {
// 	int		i;
// 	t_data	*tmp;

// 	i = -1;
// 	tmp = NULL;
// 	while (++i < (argc - 3))
// 	{
// 		if (!cmd)
// 		{
// 			cmd = cmd_handle(argv, env, i, cmd);
// 			cmd->fd = fd_handle(i, argc, argv);
// 			cmd->next = NULL;
// 			tmp = cmd;
// 		}
// 		else
// 		{
// 			cmd->next = cmd_handle(argv, env, i, tmp);
// 			cmd = cmd->next;
// 			cmd->fd = fd_handle(i, argc, argv);
// 		}
// 	}
// 	cmd->next = NULL;
// 	return (tmp);
// }

void	ft_exit(int i)
{
	if (i == 1)
	{
		perror(NULL);
		exit(1);
	}
}

void	freeall(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int	pipex(t_var_parsed_table *cmd_list)
{
	// t_data	*cmd;
	// t_data	*tmp;
	int		fd[2];
	int		pid;

	// cmd = NULL;
	// tmp = NULL;
	pid = 0;
	fd[READ] = 0;
	fd[WRITE] = 0;
	ft_make_process(cmd_list, fd, pid);
	if(access(".tempfile.txt", F_OK) == 0)
		unlink(".tempfile.txt");
	return (0);
}
