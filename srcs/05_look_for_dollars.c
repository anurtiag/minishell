/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:19:28 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/25 15:16:49 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


int	ft_find_variable(char *match_var_name, t_var_list **variable_list, char **content)
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

int	ft_trim_var_dollar(char *token, int start, int end, t_var_list **variable_list, char **content)
{
	char	*match_var_name;
	char	*match_var_content;

	match_var_name = strndup(token + start + 1, end);
	if (ft_find_variable(match_var_name, variable_list, content) == 1)
		return (TRUE);
	return (FALSE);
}

int	ft_look_4_dollar(char const *token, int start, int end, t_var_list **variable_list, char **content)
{
	int i;

	i = start;
	while (i < end)
	{
		if (((token[i - 1] == SPACE_M) || (!token[i - 1])) && (token[i] == '$') && (((token[i + 1] >= 'a') && (token[i + 1] <= 'z')) || ((token[i + 1] >= 'A') && (token[i + 1] <= 'Z'))))
		{
			printf("llamada a variable de entorno encontrada\n");
			if (ft_trim_var_dollar((char *)token, start, end, variable_list, content) == TRUE)
				return (TRUE);
			return(FALSE);
		}
		i++;
	}
	return (FALSE);
}