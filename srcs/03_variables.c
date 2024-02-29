/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:23:12 by emimenza          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/26 12:59:29 by anurtiag         ###   ########.fr       */
=======
/*   Updated: 2024/02/23 12:35:35 by emimenza         ###   ########.fr       */
>>>>>>> 79c187a764853d821e230e844a901c7224942d64
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	print_env(char	**env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

//This function saves the env variables into a struct
void	save_env(char	**env, t_input **struct_input)
{
	static t_var_list *variable_list;
	
	//Bucle which will go line by line of the env
	while (*env != NULL)
	{
		ft_look_4_equal(*env, 0, ft_strlen(*env), &variable_list);
		env++;
	}
	*struct_input = (t_input *)malloc(sizeof(t_input));
	(*struct_input)->ent_var = variable_list;
	//ft_print_var(*struct_input);
}
