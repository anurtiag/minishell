/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:43:59 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/22 12:37:42 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_echo(char **args, int fd)
{
	size_t	i;
	int		control;

	// ft_putstr_fd("puta\n", 2);
	i = -1;
	control = FALSE;
	args++;
	while (args[0] && (ft_strncmp(args[0], "-n", ft_strlen(args[0])) == 0))
	{
		control = TRUE;
		args++;
	}
	while(args[++i])
	{
		if (i != 0)
			ft_putchar_fd(' ', fd);
		ft_putstr_fd(args[i], fd);
	}
	if (control == FALSE)
		printf("\n");
}

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return(1);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	get_path(char *args, t_input **env)
{
	char		**path;
	char		*tmp;
	char		*route;
	size_t		i;
	t_var_list	*current;

	i =  -1;
	current = (*env)->ent_var;
	while(ft_strncmp(current->name, "PWD", 3) != 0)
		current = current->next;
	if(args[0] == '/')//rutas absolutas
	{
		if (access(args, X_OK) != 0)
			return(print_error(8, NULL, NULL), 1);
		chdir(args);
		ft_pwd();
		current->content = ft_strdup(args);
		return(0);
	}
	path = ft_split(args, '/');
	route = getcwd(NULL, 0);
	if (!path)
		return(1);
	while (path[++i])//rutas relativas
	{
		if((ft_strncmp(path[i], "..", 2) == 0) && ft_strlen(path[i]) == 2)
		{
			route = ft_substr(route, 0, ft_strrchr(route, '/') - route);
			chdir(route);
		}
		else if (!(path[i][0] == '.' && path[i][1] == '/' && ft_strlen(path[i]) == 1))
		{
			route = ft_strjoin(route, "/");
			route = ft_strjoin(route, path[i]);
			if (access(route, X_OK) != 0)
				return(print_error(8, NULL, NULL), 1);
		}
	}
	chdir(route);
	current->content = ft_strdup(route);
	// printf("donde petas get path?\n");
	return(0);
}

int	ft_cd(char **args, t_input **env)
{
	size_t		i;
	char		*home;
	t_var_list	*current;

	i = 0;
	current = (*env)->ent_var;
	while(ft_strncmp(current->name, "PWD", 3) != 0)
		current = current->next;
	while (args[i])
	{
		// printf("tenemos %s\n", args[i]);
		i++;
	}
	if (i > 1)
		get_path(args[1], env);
	else
	{
		home = getenv("HOME");
		if(access(home, X_OK) == 0)
		{
			if (chdir(home) != 0)
			{
				return(1);
			}
		}
		free(current->content);
		current->content = ft_strdup(home);
	}
	ft_pwd();
	return(0);
}

void add_var(char *name, t_var_list **env, char *content)
{
	t_var_list	*current;
	t_var_list	*new;

	current = *env;
	while(current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0)
		{
			if(content)
				current->content = ft_strdup(content);
			return ;
		}
		current = current->next;
	}
	new = (t_var_list *)malloc(sizeof(t_var_list));
	if(!new)
		return ;
	current = *env;
	while(current->next)
		current = current->next;
	new->name = ft_strdup(name);
	if (content)
		new->content = ft_strdup(content);
	else
		new->content = NULL;
	current->next = new;
	new->next = NULL;
	new->is_printed = 0;
}

void ft_empty_export(t_var_list **env)
{
	t_var_list 	*save;
	t_var_list	*current;
	t_var_list	*name;
	int			size;

	size = 0;
	current = *env;
	while(current)
	{
		size++;
		current = current->next;
	}
	// printf("size vale %d\n", size);
	while(size > 1)
	{
		current = *env;
		// printf("\n\n%s\n\n", current->name);
		name = current;
		while(name->is_printed == 1 && name->next)
			name = name->next;
		while(current)
		{
			if(ft_strncmp(name->name, current->name, ft_strlen(current->name)) > 0 && current->is_printed == 0)
				name = current;
			current = current->next;
		}
		// printf("\n\n\n");
		name->is_printed = 1;
		if (name->content)
			printf("declare -x %s=%s\n", name->name, name->content);
		else
			printf("declare -x %s\n", name->name);
		size--;
	}
	current = *env;
	while(current)
	{
		current->is_printed = 0;
		current = current->next;
	}
}

int ft_export(char *var, t_input **struct_input)
{
	char		*equal;
	char		*name;
	char		*content;

	if (var)
		equal = ft_strchr(var, '=');
	if(!var)
		ft_empty_export(&(*struct_input)->ent_var);
	else if (equal)
	{
		name = ft_substr(var, 0, equal - var);
		// printf("el nombre es %s\nel contenido %s\n", name, (equal + 1));
		add_var(name, &(*struct_input)->ent_var, (equal + 1));
		free(name);
	}
	else
		add_var(var, &(*struct_input)->ent_var, NULL);
		free(var);
}

void	ft_eexit(char **arg, t_input **struct_input, t_step *step)
{
	int num;
	int i;

	i = -1;
	if (!arg[1])
	{
		free_all(*struct_input, (*struct_input)->input);
		free_steps(step);
		exit(0);
	}
	while (arg[1][++i])
	{
		if (!ft_isdigit((int)arg[1][i]))
		{
			printf("exit: %s: numeric argument required\n", arg[1]);
			free_all(*struct_input, (*struct_input)->input);
			free_steps(step);
			exit(0);
		}
	}
	num = ft_atoi(arg[1]);
	if (num >= 0 && num <= 255)
	{
		free_all(*struct_input, (*struct_input)->input);
		free_steps(step);
		exit(num);
	}		
	else
	{
		printf("exit\n");
		free_all(*struct_input, (*struct_input)->input);
		free_steps(step);
		exit(0);
	}
}

void	ft_unset(char *name, t_input **struct_input)
{
	t_var_list *current;
	t_var_list *tmp;

	if (!name)
		return ;
	current = (*struct_input)->ent_var;
	// printf("Vamos a intentar quitar el primero a ver si funtxiona\n%s\n", name);
	//printf("La primera variable es %s\n", current->name);
	if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)//seria para verificar si el primero 
	{
		// printf("Llegamos a entrar aqui?\n");
		(*struct_input)->ent_var = current->next;
		free(current);
		return ;
	}
	while(current->next)
	{
		if (ft_strncmp(current->next->name, name, ft_strlen(name)) == 0)
		{
			tmp = current->next;
			if(current->next->next)
				current->next = current->next->next;
			else
				current->next = NULL;
			free(tmp);
			return ;
		}
		current = current->next;
	}
}

int	ft_built_in(t_var_parsed_table	*cmd_list, t_input **struct_input, int *control, int mode, t_step *step)
{
	if (ft_strncmp(cmd_list->cmd_splited[0], "echo", 4) == 0)
	{
		if(mode == 0)
			return(TRUE);
		else if(mode == 2)
			ft_echo(cmd_list->cmd_splited, cmd_list->fd_out);
		else
			ft_echo(cmd_list->cmd_splited, 1);
		*control = FALSE;
		
	}
	else if(ft_strncmp(cmd_list->cmd_splited[0], "pwd", 3) == 0)
	{
		if(mode == 0)
			return(TRUE);
		*control = FALSE;
		ft_pwd();
	}
	else if(ft_strncmp(cmd_list->cmd_splited[0], "cd", 2) == 0)
	{
		if(mode == 0)
			return(TRUE);
		*control = FALSE;
		ft_cd(cmd_list->cmd_splited, struct_input);
	}
	else if(ft_strncmp(cmd_list->cmd_splited[0], "export", 6) == 0)
	{
		if(mode == 0)
			return(TRUE);
		*control = FALSE;
		ft_export(cmd_list->cmd_splited[1], struct_input);
	}
	else if(ft_strncmp(cmd_list->cmd_splited[0], "unset", 5) == 0)
	{
		if(mode == 0)
			return(TRUE);
		*control = FALSE;
		ft_unset(cmd_list->cmd_splited[1], struct_input);
	}
	else if(ft_strncmp(cmd_list->cmd_splited[0], "env", 3) == 0)
	{
		if(mode == 0)
			return(TRUE);
		*control = FALSE;
		ft_print_var(*struct_input);
	}
	else if(ft_strncmp(cmd_list->cmd_splited[0], "exit", ft_strlen(cmd_list->cmd_splited[0])) == 0)
	{
		if(mode == 0)
			return(TRUE);
		*control = FALSE;
		ft_eexit(cmd_list->cmd_splited, struct_input, step);
	}
	return (0);
}
