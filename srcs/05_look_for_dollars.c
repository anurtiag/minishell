/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_look_for_dollars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:19:28 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/25 17:12:51 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Deletes the char on the N position
void del_char(char **cadena, int position)
{
	char	*before;
	char	*after;
	int		size1;
	int		size2;
	int		tmp;

	size1 = 0;
	size2 = 0;
	tmp = 0;
	before = NULL;
	after = NULL;
	while (size1 != position)
		size1++;
	before = strndup((*cadena), size1);
	tmp = size1;
	while ((*cadena)[++size1] != '\0')
		size2++;
	after = strndup((*cadena + (tmp + 1)), size2);
	free((*cadena));
	*cadena = ft_strjoin(before, after);
	free(before);
	free(after);
}

//Looks for a variable with the name vien
static int	ft_find_variable(char *match_var_name, t_var_list **variable_list, char **content)
{
	t_var_list *current;

	current = *variable_list;
	while (current)
	{
		if ((strncmp(match_var_name, current->name, INT32_MAX) == 0 && (strlen(match_var_name) == strlen(current->name))))
		{
			free(*content);//PRUEBA GUARRA PARA /bin/echo $"HOME"$USER PARECE QUE FUNCIONA DE MOMENTO SE QUEDA
			(*content) = current->content;
			return (TRUE);
		}
		current = current->next;
	}
	free(*content);
	(*content) = ft_strdup("");
	return (FALSE);
}

//Trims the token looking for the var name
static int	ft_trim_var_dollar(char *token,  t_var_list **variable_list, char **content, int index)
{
	char	*match_var_name;
	char	*before;
	char	*after;
	char	*tmp;
	int		size;
	int		size1;
	int 	size2;

	size2 = 0;
	size1 = 0;
	size = 0;
	before = NULL;
	after = NULL;
	tmp = NULL;
	
	while (token[size] && size != index)
	{
		if (token[size] == '$' && ((isalpha(token[size + 1]) && size == index)))
			break;
		size++;
	}

	before = malloc(sizeof(char) * size + 1);
	
	while (size1 < size)
	{
		before[size1] = token[size1];
		size1++;
	}
	before[size1] = '\0';

	size1++;
	while (token[size1] && ((token[size1] != '\'') && (token[size1] != '\"') && (token[size1] != '$') && (token[size1] != '/') && (token[size1] != ' ')))
		size1++;

	after = malloc(sizeof(char) * (ft_strlen(token) - size1 + 1));
	
	while (token[size1])
	{
		after[size2] = token[size1];
		size1++;
		size2++;
	}
	after[size2] = '\0';

	match_var_name = strndup(token + size + 1, (size1 - size - size2 - 1));

	ft_find_variable(match_var_name, variable_list, content);
	tmp = ft_strjoin((*content), after);
	if (ft_strlen(*content) == 0)
		free(*content);//OTRA FREE GUARRO PARA CASOS COMO: /bin/echo $TESTNOTFOUND
	(*content) = ft_strjoin(before, tmp);
	free(tmp);

	free(match_var_name);
	free(after);
	free(before);
	return (FALSE);
}

//Check in the given input if a variable call is detected
int	ft_look_4_dollar(char const *token, t_var_list **variable_list, char **content)
{
	int i;
	int max;
	int quotes_flag;
	int	quotes_flag2;

	quotes_flag2 = 0;
	quotes_flag = 0;
	max = ft_strlen(*content);
	i = 0;
	while (i < max)
	{
		if ((*content)[i] == '\'')
			quotes_flag = !quotes_flag;

		if ((*content)[i] == '\"')
			quotes_flag2 = !quotes_flag2;

		if (!quotes_flag2 && !quotes_flag && (*content)[i] == '$' && ((*content)[i + 1] == '\'' || (*content)[i + 1] == '\"'))
		{
			del_char(content, i);
			i = -1;
		}
		else if ((quotes_flag == 0) && (((*content)[i] == '$') && ((((*content)[i + 1] >= 'a') && ((*content)[i + 1] <= 'z')) || (((*content)[i + 1] >= 'A') && ((*content)[i + 1] <= 'Z')) || ((*content)[i + 1] >= '_' || ((*content)[i + 1] >= '?')))))
		{
			ft_trim_var_dollar(*content, variable_list, content, i);
			i = -1;
			max = ft_strlen(*content);
		}
		i++;
	}
	if (token[0] == '$')//HE HECHO ESTA GUARRADA PORQUE LEAKEABAN LAS VARIABLES ANTES DE EXPANDIRSE, SI ALGO PETA ES POR ESTO
		free((char *)token);
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
		if (current->cmd == NULL)
			break;
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
