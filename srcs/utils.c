/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:53:49 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/05 15:24:27 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// char	*ft_get_path(char **env, char *cmd)
// {
// 	int		i;
// 	char	*str;
// 	char	**s;
// 	char	*tmp;

// 	i = -1;
// 	str = ft_get_path_line(env);
// 	if (!str)
// 		ft_exit(1);
// 	s = ft_split(str, ':');
// 	if (!s)
// 		ft_exit(1);
// 	cmd = ft_strjoin("/", cmd);
// 	if (!cmd)
// 		ft_exit(1);
// 	while (s[++i])
// 	{
// 		tmp = str;
// 		str = ft_strjoin(s[i], cmd);
// 		if (access (str, X_OK) == 0)
// 			return (free(cmd), freeall(s), free(tmp), str);
// 		free (tmp);
// 	}
// 	return (freeall(s), free(cmd), free(str), NULL);
// }

// t_data	*cmd_handle(char **argv, char **env, int i, t_data *cmd)
// {
// 	t_data	*arg;

// 	arg = (t_data *)malloc(sizeof(t_data));
// 	arg->cmd = ft_get_cmd(argv[i + 2]);
// 	arg->path = ft_get_path(env, arg->cmd[0]);
// 	arg->next = NULL;
// 	if (arg->path != NULL)
// 		return (arg);
// 	else
// 	{
// 		ft_printf("mizsh: command not found: %s\n", arg->cmd[0]);
// 		freeall(arg->cmd);
// 		free(arg);
// 		free_nodes(cmd);
// 		exit(EXIT_FAILURE);
// 	}
// }

// char	*ft_get_path_line(char **env)
// {
// 	int		i;
// 	char	*str;

// 	i = -1;
// 	while (env[++i] != NULL)
// 	{
// 		if (ft_strncmp(env[i], "PATH=", 5) == 0)
// 		{
// 			str = ft_substr(env[i], 5, ft_strlen(env[i]));
// 			if (!str)
// 				ft_exit(1);
// 			return (str);
// 		}
// 	}
// 	return (NULL);
// }

// void	error_handle(int argc, char **argv)
// {
// 	if (argc != 5)
// 	{
// 		write(2, "Wrong arguments\n", 16);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (access (argv[1], F_OK) < 0 || (ft_strlen(argv[1]) == 0))
// 		file_permissions(argv[1], 1);
// 	else if (ft_strlen(argv[argc - 1]) == 0)
// 		file_permissions(argv[argc - 1], 1);
// 	else if (access (argv[1], R_OK) < 0)
// 		file_permissions(argv[1], 0);
// 	if (access (argv[argc - 1], W_OK) < 0 && access (argv[argc - 1], F_OK) == 0)
// 		file_permissions(argv[argc - 1], 0);
// }

// void	file_permissions(char *name, int type)
// {
// 	int	i;

// 	i = -1;
// 	if (type == 0)
// 	{
// 		write (2, "zsh: permission denied: ", 24);
// 		while (name[++i] != '\0')
// 			write (2, &name[i], 1);
// 		write (2, "\n", 1);
// 		exit (EXIT_FAILURE);
// 	}
// 	else if (type == 1)
// 	{
// 		write (2, "zsh: no such file or directory: ", 32);
// 		while (name[++i] != '\0')
// 			write (2, &name[i], 1);
// 		write (2, "\n", 1);
// 		exit (EXIT_FAILURE);
// 	}
// }
