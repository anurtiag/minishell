/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:43:59 by anurtiag          #+#    #+#             */
/*   Updated: 2024/02/28 13:46:12 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


void	ft_echo(char **args, int fd)
{
	size_t	i;

	i = 2;
	while(args[++i])
	{
		if (i != 3)
			ft_putchar_fd(' ', fd);
		ft_putstr_fd(args[i], fd);
	}
}

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return(1);
	printf("%s\n", path);
	return (0);
}

int	get_path(char *args)
{
	char	**path;
	char	*tmp;
	char	*route;
	size_t	i;

	i =  -1;
	if(args[0] == '/')
	{
		if (access(args, X_OK) != 0)
			return(printf("no such file or directory: %s\n", args), 1);
		chdir(args);
		ft_pwd();
		return(0);
	}
	path = ft_split(args, '/');
	route = getenv("PWD");
	if (!path)
		return(1);
	while (path[++i])
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
				return(printf("no such file or directory: %s\n", args), 1);
		}
	}
	chdir(route);
	ft_pwd();
	return(0);
}

int	ft_cd(char **args)
{
	size_t 	i;
	char	*home;

	i = -1;
	while (args[i])
		i++;
	if (i > 2)
		get_path(args[2]);
	else
	{
		home = getenv("HOME");
		if(access(home, X_OK) == 0)
		{
			if (chdir(home) != 0)
			{
				printf("error\n");
				return(1);
			}
		}
	}
	return(0);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return(0);
	if (ft_strncmp(argv[1], "echo", 4) == 0 && ft_strncmp(argv[2], "-n", 2) == 0)
		ft_echo(argv, 1);
	else if(ft_strncmp(argv[1], "pwd", 3) == 0)
		ft_pwd();
	else if(ft_strncmp(argv[1], "cd", 2) == 0)
		ft_cd(argv++);
	return (0);	
}