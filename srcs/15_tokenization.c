/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:08:36 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/07 11:00:26 by emimenza         ###   ########.fr       */
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
	if (control[0] == TRUE && control[1] == TRUE)
	{
		// while(tokens[++i])
		// {
		// 	if(tokens[i][0] == '\'')
		// 	{
		// 		tmp = tokens[i];
		// 		tokens[i] = ft_strtrim(tokens[i], "\'");
		// 		free(tmp);
		// 	}
		// 	if(tokens[i][0] == '\"')
		// 	{
		// 		tmp = tokens[i];
		// 		tokens[i] = ft_strtrim(tokens[i], "\"");
		// 		free(tmp);
		// 	}
			
		// 	tokens[i] = remove_quotes(tokens[i]);
		// }
		// i = -1;
		
		(*struct_input)->token_raw = tokens;
		return(TRUE);
	}
	else
		return(FALSE);
}