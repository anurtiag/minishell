/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for_equals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:59:12 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/25 13:29:41 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Prints the variables list content
void	ft_print_var(t_input *input)
{
	t_var_list	*variable_list;

	variable_list = input->ent_var;
	if (variable_list == NULL)
		printf("no tienes variables de entorno creadas\n");
	while (variable_list)
	{
		printf("\n--------------\n");
		printf("name: %s\n", variable_list->name);
		printf("content: %s\n", variable_list->content);
		printf("--------------\n");
		variable_list = variable_list->next;
	}
}

//creates a new node and add it to the list
void	ft_add_var(t_var_list **list, char *name, char *content)
{
	t_var_list	*new;

	new = malloc(sizeof(t_var_list));
	if (new == NULL)
		return ;
	new->content = content;
	new->name = name;
	new->next = *list;
	*list = new;
}

//looks for a node with the same name and overwrites its content
int	ft_var_found(t_var_list **list, char *name, char *content)
{
	t_var_list	*current;

	current = *list;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			current->content = content;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

//Trim the token into name and content
void	ft_trim_var_equal(char *token, int equal_pos, int start, int end, t_var_list **variable_list)
{
	char	*var_name;
	char	*var_content;

	var_name = strndup(token + start, equal_pos - start);
	var_content = strndup(token + equal_pos + 2, (end - 1) - (equal_pos + 2));
	//buscamos si hay alguna variable ya creada y si existe la sobreescribimos
	if (ft_var_found(variable_list, var_name, var_content) == 0)
	{
		// y si no existe creamos nuevo nodo y lo anadimos a la lista
		ft_add_var(variable_list, var_name, var_content);
	}
}

//looks for equals in the token
int	ft_look_4_equal(char const *token, int start, int end, t_var_list **variable_list)
{
	int i;

	i = start;
	while (i < end)
	{
		if (((((token[i - 1] >= 'a') && (token[i - 1] <= 'z')) || ((token[i - 1] >= 'A') && (token[i - 1] <= 'Z'))) && (token[i] == '=')) && (((token[i + 1] == '\'') || (token[i + 1] == '\"'))))
		{
			printf("creacion variable de entorno encontrada\n");
			ft_trim_var_equal((char *)token, i, start, end, variable_list);
			return (0);
		}
		i++;
	}
	return (1);
}
