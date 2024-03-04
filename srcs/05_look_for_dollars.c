/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_look_for_dollars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:19:28 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/04 19:09:37 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Looks for a variable with the name vien
static int	ft_find_variable(char *match_var_name, t_var_list **variable_list, char **content)
{
	t_var_list *current;

	current = *variable_list;
	while (current)
	{
		if ((strncmp(match_var_name, current->name, INT32_MAX) == 0 && (strlen(match_var_name) == strlen(current->name))))
		{
			(*content) = current->content;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	ft_trim_var_dollar(char *token,  t_var_list **variable_list, char **content)
{
	char	*match_var_name;
	char	*match_var_content;

	match_var_name = strdup(token + 1);
	if (ft_find_variable(match_var_name, variable_list, content) == 1)
		return (TRUE);
	return (FALSE);
}

//Check in the given input if a variable call is detected
int	ft_look_4_dollar(char const *token, t_var_list **variable_list, char **content)
{
	int i;
	int max;

	max = ft_strlen(token);
	i = 0;
	while (i < max)
	{
		if (((token[i - 1] == SPACE_M) || (!token[i - 1])) && (token[i] == '$') && (((token[i + 1] >= 'a') && (token[i + 1] <= 'z')) || ((token[i + 1] >= 'A') && (token[i + 1] <= 'Z'))))
		{
			//printf("llamada a variable de entorno encontrada\n");
			if (ft_trim_var_dollar((char *)token, variable_list, content) == TRUE)
				return (TRUE);
			return(FALSE);
		}
		i++;
	}
	return (FALSE);
}

void	expand_var_ent(t_var_parsed_table **table, t_input **struct_input)
{
	t_var_parsed_table *current;
	int	index;
	char **cmd;

	current = *table;
	while (current != NULL)
	{
		index = 0;
		cmd = current->cmd_splited;
		while (cmd[index])
		{
			ft_look_4_dollar(cmd[index], &(*struct_input)->ent_var, &cmd[index]);
			index++;
		}
		current = current->next;
    }
}
