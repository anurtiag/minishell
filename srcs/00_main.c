/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/26 19:09:27 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
 
// static int	print_history(char *line, t_input **struct_input)
// {
// 	if (tokenization(line, struct_input) == FALSE)
// 	{
// 		return (printf("syntax error\n"), FALSE);
// 	}
// 	return (TRUE);
// }

void	prepare_program(t_input *struct_input, char **envp)
{
	load_history();
	save_env(envp, &struct_input);
	signal_receiver();
	read_table(&struct_input);

	//print_options_for_state(struct_input->parsing_table, 0);
}
 int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_input *struct_input;

	(void)argc;
	(void)argv;
	input = NULL;
	prepare_program(struct_input, envp);
	while (1)
	{
		input = readline("Minishell>>");
		if (input == NULL || ft_strncmp(input, "exit", 5) == 0)
			break ;
		//print_history(input, &struct_input);
		save_history(input);
		free(input);
	}
	return (0);
}
