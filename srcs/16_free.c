/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:17:49 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/12 11:57:07 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void free_options(t_options *options)
{
	t_options *current_option;

	while (options != NULL)
	{
		current_option = options;
		options = options->next;
		free(current_option);
	}
}
void free_states(t_states *states)
{
	t_states *current_state;

	while (states != NULL)
	{
		current_state = states;
		states = states->next;
		free_options(current_state->options);
		free(current_state);
	}
}

//Function to clear all
void	free_all(t_input *struct_input, char *history)
{
	t_var_list *tmp_env;

	//load historial // add historial
	free(history);

	//save env
	while ((struct_input)->ent_var)
	{
		tmp_env = (struct_input)->ent_var->next;
		free((struct_input)->ent_var->name);
		free((struct_input)->ent_var->content);
		free((struct_input)->ent_var);
		(struct_input)->ent_var = tmp_env;
	}

	//tabla comandos
	free_states((struct_input)->parsing_table);

	//prepare program
	free(struct_input);
}