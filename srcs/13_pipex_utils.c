/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:46:50 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/13 17:13:09 by anurtiag         ###   ########.fr       */
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
	free(str);
	}
	printf("command %s not found\n", cmd->cmd_splited[0]);
}

void	relative_path(t_var_parsed_table *cmd, t_input **env)
{
	char		**path;
	char		*tmp;
	char		*route;
	char		*route_tmp;
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
			route_tmp = ft_strjoin(route, "/");
			free(route);
			route = ft_strjoin(route_tmp, path[i]);
			free(route_tmp);
			if (access(route, X_OK) != 0)
			{
				printf("no such file or directory: %s\n", cmd->cmd_splited[0]);
				return ;
			}
		}
	}
	free_double(path);
	cmd->path = route;
}

void	cmd_handle(t_var_parsed_table **cmd_list, t_input **env)
{
	t_var_parsed_table	*cmd;
	char				*path_env;
	char				**posible_paths;

	cmd = *cmd_list;
	if (!cmd->cmd)
		return ;
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

int	ft_here_doc(char *end, int fd)
{
	char	*delimiter;
	char	*line;
	int		outfile;
	char	*output;
	char	*tmp;

	if (end == NULL)
	{
		printf("no valid limiter\n");
		return (1);
	}
	output = (char *)malloc(sizeof(char) * 1);
	output[0] = '\0';
	delimiter = ft_strjoin(end, "\n");
	while (1)
	{
		write(1,"Minishell heredoc> ", 19);
		line = get_next_line(fd);
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			break ;
		tmp = output;
		output = ft_strjoin(output, line);
		free(line);
		free(tmp);
	}
	outfile = open(".tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return(1);
	free_here_doc(delimiter, output, line, outfile);
	outfile = open(".tempfile.txt", O_RDONLY);
	return (outfile);
}

void	free_here_doc(char *delimiter, char *output, char *line, int outfile)
{
	if (write(outfile, output, ft_strlen(output)) == -1)
		return ;
	free(delimiter);
	free(output);
	free(line);
	line = NULL;
	if (close(outfile) < 0)
		return ;
}
