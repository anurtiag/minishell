/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_look_for_dollars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:19:28 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/13 15:48:13 by anurtiag         ###   ########.fr       */
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
			return (TRUE);
		}
		current = current->next;
	}
	(*content) = "";
	return (FALSE);
}

static int	ft_trim_var_dollar(char *token,  t_var_list **variable_list, char **content)
{
	char	*match_var_name;
	char	*before;
	char	*after;
	int		size;
	int		size1;
	int 	size2;

	size2 = 0;
	size1 = 0;
	size = 0;
	before = NULL;
	after = NULL;

	while (token[size] && (token[size] != '$'))
		size++;
	before = malloc(sizeof(char) * size + 1);
	
	while (token[size1] && (token[size1] != '$'))
	{
		before[size1] = token[size1];
		size1++;
	}
	before[size1] = '\0';

	while (token[size1] && ((token[size1] != 34) && token[size1] != 39))
		size1++;
	
	after = malloc(sizeof(char) * (ft_strlen(token) - size1 + 1));

	while (token[size1])
	{
		after[size2] = token[size1];
		size1++;
		size2++;
	}
	after[size2] = '\0';

	match_var_name = strndup(ft_strchr(token, '$') + 1, (size1 - size - size2 - 1));
	
	if (ft_find_variable(match_var_name, variable_list, content) == TRUE)
	{
		(*content) = ft_strjoin((*content), after);
		(*content) = ft_strjoin(before, (*content));
		return (TRUE);
	}
	return (FALSE);
}

//Check in the given input if a variable call is detected
int	ft_look_4_dollar(char const *token, t_var_list **variable_list, char **content)
{
	int i;
	int max;
	int	quotes_flag;

	quotes_flag = 0;
	max = ft_strlen(token);
	i = 0;
	while (i < max)
	{
		if (token[i] == '\'')
			quotes_flag = 1;

		//((token[i - 1] == SPACE_M) || (!token[i - 1])) &&
		if ((quotes_flag == 0) && ((token[i] == '$') && (((token[i + 1] >= 'a') && (token[i + 1] <= 'z')) || ((token[i + 1] >= 'A') && (token[i + 1] <= 'Z')))))
		{
			if (ft_trim_var_dollar((char *)token, variable_list, content) == TRUE)
				return (TRUE);
			return(FALSE);
		}
		i++;
	}
	return (FALSE);
}

//Looks into the cmd looking for dollars and equals
void	expand_var_ent(t_var_parsed_table **table, t_input **struct_input)
{
	t_var_parsed_table *current;
	int	index;
	char **cmd;

	current = *table;
	if (!current->cmd)
		return ;
	while (current != NULL)
	{
		index = 0;
		cmd = current->cmd_splited;
		while (cmd[index])
		{
			ft_look_4_dollar(cmd[index], &(*struct_input)->ent_var, &cmd[index]);
			ft_look_4_equal(cmd[index], &(*struct_input)->ent_var, 0);
			index++;
		}
		current = current->next;
    }
}
