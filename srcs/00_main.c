/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/22 15:11:26 by emimenza         ###   ########.fr       */
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

	input = NULL;
	print_env(envp);
	load_history();
	save_env(envp, &struct_input);
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
