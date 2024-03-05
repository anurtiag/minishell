/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:43:59 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/05 12:33:43 by anurtiag         ###   ########.fr       */
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

void add_var(char *name, t_var_list **env, char *content)
{
	t_var_list	*current;
	t_var_list	*new;

	current = *env;
	while(current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(current->name)) == 0)
		{
			if(content)
				current->content = ft_strdup(content);
			return (0);
		}
		current = current->next;
	}
	new = (t_var_list *)malloc(sizeof(t_var_list));
	if(!new)
		return(1);
	new->name = name;
	new->content = content;
	current->next = new;
}

void ft_empty_export(t_var_list **env)
{
	t_var_list	*current;
	t_var_list	*name;
	int			size;

	current = *env;
	while(current)
	{
		size++;
		current = current->next;
	}
	current = *env;
	name->name = current->name;
	while(size > 0)
	{
		
		while(current)
		{
			if(ft_strncmp(name->name, current->name, ft_strlen(name->name)) > 0 || name->is_printed == 0)
				name = current;
			current = current->next;
		}
		name->is_printed = 1;
		printf("declare -x %s=%s\n", name->name, name->content);
		size--;
	}
}

int ft_export(char	*var, t_var_list **env)
{
	char	*equal;
	char	*name;
	char	*content;

	if(!(ft_isalpha((int)*var) || *var == '_'))
		return(ft_printf("Hay que makearlo pero ERROR, invalid export\n"), 1);
	equal = ft_strchr(var, '=');
	if(!var)
		//imprimir todas las variabes en orden alfabetico
	if (equal)
	{
		name = ft_substr(var, 0, equal - name);
		add_var(name, env, (equal + 1));
	}
	else
		add_var(var, env, NULL);
}

int	ft_built_in(char **env, char **argv)
{
	t_var_list	*env;

	save_env(env, &env);
	if (ft_strncmp(argv[0], "echo", 4) == 0 && ft_strncmp(argv[1], "-n", 2) == 0)
		ft_echo(argv, 1);
	else if(ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd();
	else if(ft_strncmp(argv[0], "cd", 2) == 0)
		ft_cd(argv++);
	else if(ft_strncmp(argv[0], "export", 2) == 0)
		ft_export(argv++, &env);
	else if(ft_strncmp(argv[0], "unset", 2) == 0)
		ft_cd(argv++);
	else if(ft_strncmp(argv[0], "env", 2) == 0)
		ft_cd(argv++);
	return (0);	
}
