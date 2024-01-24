/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:08:36 by anurtiag          #+#    #+#             */
/*   Updated: 2024/01/24 16:13:03 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	tokenization(char *input, t_input *struct_input)
{
	int		control[2];
	char	**tokens;
	int i = -1;

	control[0] = TRUE;
	control[1] = TRUE;
	tokens = ft_bash_split(input, SPACE, control);
	// while(tokens[++i])
	// 	printf("%s\ncontrol1:%d\ncontrol2:%d\n", tokens[i], control[0], control[1]);
	if (control[0] == TRUE && control[1] == TRUE)
	{
		struct_input->token_raw = tokens;
		return(0);
	}

	else
		return(1);
}