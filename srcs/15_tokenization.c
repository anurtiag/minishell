/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:08:36 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/25 17:24:57 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Assigns the tokens to the struct
int	tokenization(char *input, t_input **struct_input)
{
	int		control[2];
	char	**tokens;
	static t_var_list *variable_list;
	int 	i = -1;
	char	*tmp;

	control[0] = TRUE;
	control[1] = TRUE;
	tokens = ft_bash_split(input, SPACE_M, control);
	if (control[0] == TRUE && control[1] == TRUE)
	{
		(*struct_input)->token_raw = tokens;
		return(TRUE);
	}
	else
		return(FALSE);
}
