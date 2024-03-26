/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_look_for_dollars2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:53:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/26 16:38:46 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Trims the token looking for the var name
int	ft_trim_var_dollar(char *token, t_var_list **v_list, \
char **content, int index)
{
	char	*match_var_name;
	char	*before;
	char	*after;
	char	*tmp;

	before = NULL;
	after = NULL;
	tmp = NULL;
	ft_trim_var_dollar_aux(token, &before, &after, &match_var_name, index);
	ft_find_variable(match_var_name, v_list, content);
	tmp = ft_strjoin((*content), after, 5);
	if (ft_strlen(*content) == 0)
		free(*content);
	(*content) = ft_strjoin(before, tmp, 15);
	free(match_var_name);
	return (FALSE);
}

void	ft_trim_var_dollar_aux(char *token, char **before, char **after, \
char **var_name, int index)
{
	int		size;
	int		size1;
	int		size2;

	size2 = 0;
	size1 = -1;
	size = 0;
	while (token[size] && (size != index || (token[size] != '$' || \
	!isalpha(token[size + 1]))))
		size++;
	*before = malloc(sizeof(char) * (size + 1));
	while (++size1 < size)
		(*before)[size1] = token[size1];
	(*before)[size1++] = '\0';
	while (token[size1] && ((token[size1] != '\'') && (token[size1] != '\"') && \
	(token[size1] != '$') && (token[size1] != '/') && (token[size1] != ' ')))
		size1++;
	*after = malloc(sizeof(char) * (ft_strlen(token) - size1 + 1));
	while (token[size1])
		(*after)[size2++] = token[size1++];
	(*after)[size2] = '\0';
	*var_name = strndup(token + size + 1, (size1 - size - size2 - 1));
}

//Check in the given input if a variable call is detected
int	ft_look_4_dollar(char const *token, t_var_list **v_list, char **content)
{
	int	i;
	int	max;

	max = ft_strlen(*content);
	i = 0;
	while (i < max)
	{
		ft_look_4_d_aux(content, i, max, v_list);
		i++;
	}
	if (token[0] == '$')
		free((char *)token);
	return (FALSE);
}

void	ft_look_4_d_aux(char **content, int i, int max, t_var_list **v_list)
{
	int	quotes_flag;
	int	quotes_flag2;

	quotes_flag2 = 0;
	quotes_flag = 0;
	if ((*content)[i] == '\'')
		quotes_flag = !quotes_flag;
	if ((*content)[i] == '\"')
		quotes_flag2 = !quotes_flag2;
	if (!quotes_flag2 && !quotes_flag && (*content)[i] == '$' && \
	((*content)[i + 1] == '\'' || (*content)[i + 1] == '\"'))
	{
		del_char(content, i);
		i = -1;
	}
	else if ((quotes_flag == 0) && (((*content)[i] == '$') && \
	((((*content)[i + 1] >= 'a') && ((*content)[i + 1] <= 'z')) || \
	(((*content)[i + 1] >= 'A') && ((*content)[i + 1] <= 'Z')) || \
	((*content)[i + 1] >= '_' || ((*content)[i + 1] >= '?')))))
	{
		ft_trim_var_dollar(*content, v_list, content, i);
		i = -1;
		max = ft_strlen(*content);
	}
}
