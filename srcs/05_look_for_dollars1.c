/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_look_for_dollars1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:19:28 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/26 13:59:20 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Deletes the char on the N position
void	del_char(char **cadena, int position)
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
	*cadena = ft_strjoin(before, after, 15);
}

//Looks for a variable with the name vien
int	ft_find_variable(char *var_name, t_var_list **v_list, char **content)
{
	t_var_list	*current;

	current = *v_list;
	while (current)
	{
		if ((strncmp(var_name, current->name, INT32_MAX) == 0 && \
		(strlen(var_name) == strlen(current->name))))
		{
			free(*content);
			(*content) = current->content;
			return (TRUE);
		}
		current = current->next;
	}
	free(*content);
	(*content) = ft_strdup("");
	return (FALSE);
}

//Looks into the cmd looking for dollars and equals
void	expand_var_ent(t_var_parsed_table **table, t_input **struct_input)
{
	t_var_parsed_table	*current;
	int					i;
	char				**cmd;

	current = *table;
	if (!current->cmd)
		return ;
	while (current != NULL)
	{
		i = 0;
		if (current->cmd == NULL)
			break ;
		cmd = current->cmd_splited;
		while (cmd[i])
		{
			ft_look_4_dollar(cmd[i], &(*struct_input)->ent_var, &cmd[i]);
			ft_look_4_equal(cmd[i], &(*struct_input)->ent_var, 0);
			i++;
		}
		current = current->next;
	}
}
