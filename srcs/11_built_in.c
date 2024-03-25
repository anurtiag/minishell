/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:43:59 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/25 17:17:44 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Custom echo function
void	ft_echo(char **args, int fd)
{
	size_t	i;
	int		control;

	i = -1;
	control = FALSE;
	args++;
	while (args[0] && (ft_strncmp(args[0], "-n", 2) == 0) && ft_strlen(args[0]) == 2)
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
		ft_putstr_fd("\n", fd);
}

//Custom pwd function
int	ft_pwd(t_input **env)
{
	t_var_list	*current;

	current = (*env)->ent_var;
	while(ft_strncmp(current->name, "PWD", 3) != 0)
		current = current->next;
	printf("%s\n", current->content);
	return (0);
}

//Custom path funcion
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
		ft_pwd(env);
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
			tmp = route;
			route = ft_substr(route, 0, ft_strrchr(route, '/') - route);
			free(tmp);
			printf("1la ruta es %s\n", route);
			chdir(route);
		}
		else if ((path[i][0] == '.' && path[i][1] == '/' && ft_strlen(path[i]) == 1))
		{
			route = ft_strjoin(route, "/");
			route = ft_strjoin(route, path[i]);
			if (access(route, X_OK) != 0)
				return(print_error(8, NULL, NULL), free(route), free_double(path), 1);
		}
		else
		{
			tmp = route;
			route = ft_strjoin(route, "/");
			free(tmp);
			tmp = route;
			route = ft_strjoin(route, path[i]);
			free(tmp);
			printf("2la ruta es %s\n", route);
			if (access(route, X_OK) != 0)
				return(print_error(8, NULL, NULL), free(route), free_double(path), 1);
		}
	}
	tmp = current->content;
	current->content = ft_strdup(route);
	printf("3la ruta es %s\n", route);
	chdir(route);
	return(free(tmp), free(route), free_double(path), 0);
}

//Custom cd funcion
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
		i++;
	if (i > 1)
		get_path(args[1], env);
	else
	{
		home = getenv("HOME");
		if(access(home, X_OK) == 0)
		{
			if (chdir(home) != 0)
				return(1);
		}
		free(current->content);
		current->content = ft_strdup(home);
	}
	return(0);
}

//Adds a variable to the list
void add_var(char *name, t_var_list **env, char *content)
{
	t_var_list	*current;
	t_var_list	*new;
	

	current = *env;
	while(current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0)
		{
			free(current->content);//OTRO APAÑO GUARRO PA LA COLE
			if (content)
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

//Custom export funcion
void	ft_empty_export(t_var_list **env)
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

//Exports the var to the env
int	ft_export(char *var, t_input **struct_input)
{
	char		*equal;
	char		*name;
	char		*content;

	if (var && (var[0] == '_' || ft_isalpha(var[0]) == 0 || var[0] == '?'))
		return(print_error(1, NULL, struct_input), FALSE);
	if (var)
		equal = ft_strchr(var, '=');
	if(!var)
		ft_empty_export(&(*struct_input)->ent_var);
	else if (equal)
	{
		name = ft_substr(var, 0, equal - var);
		add_var(name, &(*struct_input)->ent_var, (equal + 1));
		free(name);
	}
	else
		add_var(var, &(*struct_input)->ent_var, NULL);
	return (TRUE);
}

//Custom exit funcion
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
			exit(255);
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

//Custom unset function
void	ft_unset(char *name, t_input **struct_input)
{
	t_var_list *current;
	t_var_list *tmp;

	if (!name || ft_strlen(name) == 0)
	{
		return ;
	}
	current = (*struct_input)->ent_var;
	if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)//seria para verificar si el primero 
	{
		(*struct_input)->ent_var = current->next;
		free(current->content);
		free(current->name);
		free(current);
		return ;
	}
	while(current->next)
	{
		if (ft_strncmp(current->next->name, name, ft_strlen(name)) == 0 && ft_strlen(name) == ft_strlen(current->next->name))
		{
			tmp = current->next;
			if(current->next->next)
				current->next = current->next->next;
			else
				current->next = NULL;
			free(tmp->content);
			free(tmp->name);
			free(tmp);
			return ;
		}
		current = current->next;
	}
}

//Main built in function
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
		ft_pwd(struct_input);
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
