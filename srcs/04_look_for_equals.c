/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_look_for_equals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:59:12 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/26 13:43:51 by emimenza         ###   ########.fr       */
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
int	ft_var_found(t_var_list **list, char *name, char *content)
{
	t_var_list	*current;

	current = *list;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->content);
			current->content = NULL;
			current->content = ft_strdup(content);
			return (TRUE);
		}
		current = current->next;
	}
	return (FALSE);
}

//Trim the token into name and content
void	ft_trim_var_equal(char *token, int e_pos, t_var_list **v_list, int id)
{
	char	*var_name;
	char	*var_content;
	int		content_start;
	int		end;

	content_start = e_pos + 1;
	end = ft_strlen(token);
	var_name = strndup(token, e_pos);
	if (token[e_pos + 1] == '\'' || token[e_pos + 1] == '\"')
		var_content = strndup(token + e_pos + 2, (end - 1) - (e_pos + 2));
	else
		var_content = strndup(token + e_pos + 1, end - (e_pos + 1));
	if (ft_var_found(v_list, var_name, var_content) == FALSE)
		ft_add_var(v_list, var_name, var_content, id);
	else
	{
		if (var_name)
			free(var_name);
		if (var_content)
			free(var_content);
	}
}

//looks for equals in the token
int	ft_look_4_equal(char const *token, t_var_list **variable_list, int id)
{
	int		i;
	char	quote;
	int		max;

	quote = '\0';
	max = ft_strlen(token);
	i = 0;
	while (i < max)
	{
		if (token[i] == '\'' || token[i] == '\"')
			quote = token[i];
		else if (quote == '\0' && token[i - 1] != '\'' \
		&& token[i - 1] != '\"' && token[i] == '=')
		{
			ft_trim_var_equal((char *)token, i, variable_list, id);
			return (TRUE);
		}
		else if (token[i] == quote)
			quote = '\0';
		i++;
	}
	return (FALSE);
}
