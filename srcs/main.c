/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/22 13:39:54 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../incs/minishell.h"
 
void	print_history(char *line)
{
	printf("la linea es%s\n", line);
}
 
 int main(void)
{
	char	*input;
	char	*linea;

	linea = NULL;
	input = NULL;
	while (1)
	{
		input = readline("Minishell> ");
		if (ft_strncmp(input, "exit", 3) == 0)
			break ;
		print_history(input);
		add_history(input);
	}
	printf("funtxiono\n");
	return (0);
}
