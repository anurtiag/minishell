/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:23:12 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/26 13:41:05 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Prints the enviroment vars
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
	static t_var_list	*variable_list;

	while (*env != NULL)
	{
		ft_look_4_equal(*env, &variable_list, 1);
		env++;
	}
	(*struct_input)->ent_var = variable_list;
	ft_trim_var_equal("?=\"0\"", 1, &(*struct_input)->ent_var, 0);
}
