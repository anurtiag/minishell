/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/24 16:25:31 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
 
int	print_history(char *line, t_input *struct_input)
{
	if (tokenization(line, struct_input) == 1)
	{
		return (printf("syntax error\n"), 1);
	}
	return (0);
}
 
 int main(void)
{
	char	*input;
	t_input struct_input;

	input = NULL;
	while (1)
	{
		input = readline("\033[0;33mMinishell>\033[0m");
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			printf("%s\n", input);
			break ;
		}
		if (ft_strncmp(input, "clear", 5) == 0)
			system("clear");
		if (print_history(input, &struct_input) == 0)
		{
			//el input esta bien
			//printf("la linea escrita es :%s\n", struct_input.token_raw[0]);
		}
		add_history(input);
	}
	return (0);
}
