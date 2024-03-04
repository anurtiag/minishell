/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:46:50 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/04 13:46:54 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_verify_cmd(char **paths, t_var_parsed_table *cmd)
{
	size_t	i;
	char	*str;

	i = -1;
	cmd->cmd_splited = ft_split(cmd->cmd, ' ');
	while(paths[++i])
	{
		str = ft_strjoin("/", cmd->cmd_splited[0]);
		// printf("el comando es: %s\nel path %s\n", str, paths[i]);
		str = ft_strjoin(paths[i], str);
		// printf("despues del join comando es: %s\n", str);
		if (access(str, X_OK) == 0)
		{
			cmd->path = str;
			return ;
		}
	}
	printf("command %s not found\n", cmd->cmd_splited[0]);
}

void	cmd_handle(t_var_parsed_table **cmd_list)
{
	t_var_parsed_table	*cmd;
	char				*path_env;
	char				**posible_paths;

	cmd = *cmd_list;
	path_env = getenv("PATH");
	posible_paths = ft_split(path_env, ':');
	while(cmd)
	{
		ft_verify_cmd(posible_paths, cmd);
		//printf("%s\n", cmd->cmd);
		//printf("la ruta del comando es :%s\n", cmd->path);
		cmd = cmd->next;
	}
}
