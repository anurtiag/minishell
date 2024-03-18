/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_look_for_equals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:59:12 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/18 12:55:39 by emimenza         ###   ########.fr       */
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
		printf("is env: %i\n", variable_list->is_env);
		printf("--------------\n");
		variable_list = variable_list->next;
	}
}

//creates a new node and add it to the list
static void	ft_add_var(t_var_list **list, char *name, char *content, int id)
{
	t_var_list	*new;

	new = malloc(sizeof(t_var_list));
	if (new == NULL)
		return ;
	new->content = content;
	new->name = name;
	new->next = *list;
	new->is_printed = 0;
	new->is_env = id;
	*list = new;
}

//looks for a node with the same name and overwrites its content
static int	ft_var_found(t_var_list **list, char *name, char *content)
{
	t_var_list	*current;

	current = *list;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			current->content = content;
			return (TRUE);
		}
		current = current->next;
	}
	return (FALSE);
}

//Trim the token into name and content
void	ft_trim_var_equal(char *token, int equal_pos, t_var_list **variable_list,int id)
{
	char	*var_name;
	char	*var_content;
	int		content_start = equal_pos + 1;
	int		end;

	end = ft_strlen(token);
	var_name = strndup(token, equal_pos);
	if (token[equal_pos + 1] == '\'' || token[equal_pos + 1] == '\"')
	{
		var_content = strndup(token + equal_pos + 2, (end - 1) - (equal_pos + 2));
	}
	else
	{
		var_content = strndup(token + equal_pos + 1, end - (equal_pos + 1));
	}

	if (ft_var_found(variable_list, var_name, var_content) == FALSE)
	{
		ft_add_var(variable_list, var_name, var_content, id);
	}
}

//looks for equals in the token
int	ft_look_4_equal(char const *token, t_var_list **variable_list,int id)
{
	int		i;
	char	quote = '\0'; // Variable para rastrear comillas abiertas
	int		max;

	max = ft_strlen(token);
	i = 0;
	while (i < max)
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			quote = token[i]; // Si encontramos una comilla, actualizamos el tipo de comilla
		}
		else if (quote == '\0' && token[i - 1] != '\'' && token[i - 1] != '\"' && token[i] == '=')
		{
			// Si no hay comillas abiertas y encontramos un igual no precedido por comillas
			ft_trim_var_equal((char *)token, i, variable_list, id);
			return (TRUE);
		}
		else if (token[i] == quote)
		{
			quote = '\0'; // Si encontramos la comilla de cierre, la reseteamos
		}
		i++;
	}
	return (FALSE);
}
