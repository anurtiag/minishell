/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:08:36 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/04 18:47:01 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	tokenization(char *input, t_input **struct_input)
{
	int		control[2];
	char	**tokens;
	static t_var_list *variable_list;
	int i = -1;
	char	*tmp;

	control[0] = TRUE;
	control[1] = TRUE;
	tokens = ft_bash_split(input, SPACE_M, control);
	// while(tokens[++i])
	// 	printf("%s\n", tokens[i]);
	if (control[0] == TRUE && control[1] == TRUE)
	{
		while(tokens[++i])
		{
			if(tokens[i][0] == '\'')
			{
				tmp = tokens[i];
				tokens[i] = ft_strtrim(tokens[i], "\'");
				free(tmp);
			}
			else if(tokens[i][0] == '\"')
			{
				tmp = tokens[i];
				tokens[i] = ft_strtrim(tokens[i], "\"");
				free(tmp);
			}
		}
		i = -1;
		// while(tokens[++i])
		// 	printf("%s\n", tokens[i]);
		(*struct_input)->token_raw = tokens;
		return(TRUE);
	}
	else
		return(FALSE);
}