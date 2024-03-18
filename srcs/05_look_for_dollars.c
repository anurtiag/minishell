/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_look_for_dollars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:19:28 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/18 12:41:57 by anurtiag         ###   ########.fr       */
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
	free(*content);
	(*content) = ft_strdup("");
	return (FALSE);
}

static int	ft_trim_var_dollar(char *token,  t_var_list **variable_list, char **content, int index)
{
	char	*match_var_name;
	char	*before;
	char	*after;
	int		size;
	int		size1;
	int 	size2;
	int		sizea;
	int		sizem;
	int		sizeb;

	size2 = 0;
	size1 = 0;
	size = 0;
	before = NULL;
	after = NULL;

	//---------------------------------------------------------------BUSCAR HASTA EL PRIMER DOLLAR && ft_isalpha(token[size + 1])
	
	while (token[size] && size != index)
	{
		if (token[size] == '$' && isalpha(token[size + 1] && size == index))
			break;
		size++;
	}

	before = malloc(sizeof(char) * size + 1);
	sizeb = size;
	//---------------------------------------------------------------CARGAR INFORMACION EN BEFORE

	while (size1 < size)
	{
		before[size1] = token[size1];
		size1++;
	}
	before[size1] = '\0';

	//---------------------------------------------------------------
	//&& (token[size1] != '$'))
	size1++;
	while (token[size1] && ((token[size1] != '\'') && (token[size1] != '\"') && (token[size1] != '$') && (token[size1] != '/')))
	{
		size1++;
	}
	//---------------------------------------------------------------
	after = malloc(sizeof(char) * (ft_strlen(token) - size1 + 1));
	sizea = ft_strlen(token) - size1;
	
	while (token[size1])
	{
		after[size2] = token[size1];
		size1++;
		size2++;
	}
	after[size2] = '\0';
	//---------------------------------------------------------------
	match_var_name = strndup(token + size + 1, (size1 - size - size2 - 1));
	sizem = (size1 - size - size2 - 1);

	// printf("b %s\n", before);
	// printf("m %s\n",match_var_name);
	// printf("a %s\n\n",after);
	
	
	ft_find_variable(match_var_name, variable_list, content);

		(*content) = ft_strjoin((*content), after);
		(*content) = ft_strjoin(before, (*content));

	
	return (FALSE);
}



//Check in the given input if a variable call is detected
int	ft_look_4_dollar(char const *token, t_var_list **variable_list, char **content)
{
	int i;
	int max;
	int quotes_flag;

	
	quotes_flag = 0;
	max = ft_strlen(*content);
	i = 0;
	while (i < max)
	{
		//printf("content %s\n", *content);

		if ((*content)[i] == '\'' && quotes_flag == 0)
			quotes_flag = 1;
		else if ((*content)[i] == '\'' && quotes_flag == 1)
			quotes_flag = 0;
		//printf("%c %i\n", (*content)[i], i);
		//(((*content)[i - 1] == SPACE_M) || (!(*content)[i - 1])) &&
		if ((quotes_flag == 0) && (((*content)[i] == '$') && ((((*content)[i + 1] >= 'a') && ((*content)[i + 1] <= 'z')) || (((*content)[i + 1] >= 'A') && ((*content)[i + 1] <= 'Z')))))
		{
			//printf("el token es %s position %i max %i\n", *content, i, max);
			ft_trim_var_dollar(*content, variable_list, content, i);
			i = -1;
			max = ft_strlen(*content);
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
