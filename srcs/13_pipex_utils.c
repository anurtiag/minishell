/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:46:50 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/25 12:40:44 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incs/minishell.h"

int	ft_verify_cmd(char **paths, t_var_parsed_table *cmd, t_input **env)
{
	size_t	i;
	char	*str;
	char	*str_tmp;
	int control;
	
	control = TRUE;
	i = -1;

	if (strcmp(cmd->cmd_splited[0], ".") == 0)
		return(print_error(12, cmd->cmd_splited[0], env), FALSE);
	else if (strcmp(cmd->cmd_splited[0], "..") == 0)
		return(print_error(10, cmd->cmd_splited[0], env), FALSE);
	while(paths[++i])
	{
		str_tmp = ft_strjoin("/", cmd->cmd_splited[0]);
		//printf("el comando es: %s\nel path %s\n", str, paths[i]);
		str = ft_strjoin(paths[i], str_tmp);
		free(str_tmp);
		//printf("despues del join comando es: %s\n", str);
		if (access(str, X_OK) == 0)
		{
			cmd->path = str;
			return (TRUE);
		}
	free(str);
	}
	print_error(10, cmd->cmd_splited[0], env);
	return (FALSE);
}

int	relative_path(t_var_parsed_table *cmd, t_input **env)
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
				printf("puta1\n");
				print_error(8, cmd->cmd_splited[0], env);
				return (free(route), free_double(path), FALSE);
			}
		}
	}
	free_double(path);
	cmd->path = route;
	return (TRUE);
}

int	cmd_handle(t_var_parsed_table **cmd_list, t_input **env, t_step *step)
{
	t_var_parsed_table	*cmd;
	char				*path_env;
	char				**posible_paths;
	int					control;
	struct stat			statbuf;

	cmd = *cmd_list;
	if (!cmd->cmd)
	{
		return (FALSE);
	}
	else if (ft_strlen(cmd->cmd_splited[0]) == 0)
	{
		print_error(10, cmd->cmd_splited[0], env);
		return (FALSE);
	}
	control = TRUE;
	path_env = ft_getenv(&(*env)->ent_var, "PATH");
	if (!path_env)
		return(FALSE);
	posible_paths = ft_split(path_env, ':');
	while(cmd)
	{
		if (cmd->cmd == NULL)
			break;
		if (ft_built_in(cmd, env, NULL, 0, step) == TRUE)
			control = TRUE;
		else if (cmd->cmd_splited[0][0] == '/')
		{
			if (stat(cmd->cmd_splited[0], &statbuf) == -1)
			{
				return (print_error(8, cmd->cmd_splited[0], env), free_double(posible_paths), free(path_env), FALSE);
			}
			
			if (access(cmd->cmd_splited[0], X_OK) != 0)
			{
				print_error(10, cmd->cmd_splited[0], env);
				control = FALSE;
			}
			if (S_ISDIR(statbuf.st_mode))
				return(print_error(14, NULL, env), free_double(posible_paths), free(path_env), FALSE);
			cmd->path = ft_strdup(cmd->cmd_splited[0]);
		}
		else if (cmd->cmd_splited[0][0] == '.' && cmd->cmd_splited[0][1] == '/')
		{
			if (relative_path(cmd, env) == FALSE)
				control = FALSE;
		}
		else
		{
			if (ft_verify_cmd(posible_paths, cmd, env) == FALSE)
				control = FALSE;
		}
		if (control == FALSE)
			return(free_double(posible_paths), free(path_env), FALSE);
		cmd = cmd->next;
	}
	free(path_env);
	free_double(posible_paths);
	return (TRUE);
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
		print_error(11, NULL, NULL);
		return (1);
	}
	remove_quotes_aux(&end);
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
	//free(end);
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
