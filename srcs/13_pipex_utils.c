/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:46:50 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/12 15:41:11 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_verify_cmd(char **paths, t_var_parsed_table *cmd)
{
	size_t	i;
	char	*str;
	char	*str_tmp;
	i = -1;
	while(paths[++i])
	{
		str_tmp = ft_strjoin("/", cmd->cmd_splited[0]);
		// printf("el comando es: %s\nel path %s\n", str, paths[i]);
		str = ft_strjoin(paths[i], str_tmp);
		free(str_tmp);
		//printf("despues del join comando es: %s\n", str);
		if (access(str, X_OK) == 0)
		{
			cmd->path = str;
			return ;
		}
	}
	free(str);
	printf("command %s not found\n", cmd->cmd_splited[0]);
}

void	relative_path(t_var_parsed_table *cmd, t_input **env)
{
	char		**path;
	char		*tmp;
	char		*route;
	size_t		i;
	t_var_list	*current;

	i = -1;
	path = ft_split(cmd->cmd_splited[0], '/');
	route = getcwd(NULL, 0);
	while (path[++i])//rutas relativas
	{
		if((ft_strncmp(path[i], "..", 2) == 0) && ft_strlen(path[i]) == 2)
		{
			route = ft_substr(route, 0, ft_strrchr(route, '/') - route);
			chdir(route);
		}
		else if (!(path[i][0] == '.' && ft_strlen(path[i]) == 1))
		{
			route = ft_strjoin(route, "/");
			route = ft_strjoin(route, path[i]);
			if (access(route, X_OK) != 0)
			{
				printf("no such file or directory: %s\n", cmd->cmd_splited[0]);
				return ;
			}
		}
	}
	cmd->path = route;
}

void	cmd_handle(t_var_parsed_table **cmd_list, t_input **env)
{
	t_var_parsed_table	*cmd;
	char				*path_env;
	char				**posible_paths;

	cmd = *cmd_list;
	path_env = getenv("PATH");
	posible_paths = ft_split(path_env, ':');
	while(cmd)
	{
		if (cmd->cmd_splited[0][0] == '/')
		{
			// printf("La ruta es %s\n", cmd->cmd_splited[0]);
			if (access(cmd->cmd_splited[0], X_OK) != 0)
			{
				printf("command %s not found\n", cmd->cmd_splited[0]);
				return ;
			}
			cmd->path = cmd->cmd_splited[0];
		}
		else if (cmd->cmd_splited[0][0] == '.')
			relative_path(cmd, env);
		else
		{
			// printf("Entramos aqui?\n");
			ft_verify_cmd(posible_paths, cmd);
		}
		cmd = cmd->next;
	}
	free_double(posible_paths);
}
