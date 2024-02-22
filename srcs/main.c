/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/22 13:04:12 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
 
int	print_history(char *line, t_input **struct_input)
{
	if (tokenization(line, struct_input) == FALSE)
	{
		return (printf("syntax error\n"), FALSE);
	}
	return (TRUE);
}
 
 int main(void)
{
	char	*input;
	t_input *struct_input;

	input = NULL;
	load_history();
	while (1)
	{
		// input = readline("\033[0;33mMinishell>\033[0m");
		input = readline("Minishell>>");
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		save_history(input);
		free(input);
	}
	return (0);
}
