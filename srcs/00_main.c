/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/23 11:05:30 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
 
// int	print_history(char *line, t_input **struct_input)
// {
// 	if (tokenization(line, struct_input) == FALSE)
// 	{
// 		return (printf("syntax error\n"), FALSE);
// 	}
// 	return (TRUE);
// }

void	print_env(char	**env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
 int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_input *struct_input;

	(void)argc;
	(void)argv;
	//input = NULL;
	load_history();
	save_env(envp, &struct_input);
	signal_receiver();
	while (1)
	{
		input = readline("Minishell>>");
		if (input == NULL || ft_strncmp(input, "exit", 5) == 0)
			break ;
		save_history(input);
		free(input);
	}
	return (0);
}
