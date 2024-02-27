/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_steps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:29:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/27 12:46:08 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//funcion que devuelva un estado pasando el numero
int	find_state(t_states *states_list, int state_number, t_states **state)
{
	t_states *current_state;

	current_state = states_list;
	while (current_state != NULL && current_state->state != state_number)
	{
		current_state = current_state->next;
	}

	if (current_state != NULL)
	{
		*state = current_state;
		return (TRUE);
	}
	else
		return (FALSE);
}

//Caculates the size of the stack
int	stack_size(t_token *stack)
{
	int	i;

	i = 0;
	while (stack)
		stack = stack->next;
	return (i);
}

//funcion que devuelve la opcion default si la encuentra
t_options *find_option(t_states *state, int token_type)
{
	t_options *current_option;
	t_options *null_option;

	current_option = state->options;
	null_option = NULL;
	
	while (current_option != NULL)
	{
		if (current_option->t_type == token_type)
			return (current_option);
		current_option = current_option->next;
	}
	return (null_option);
}
//funcion para crear un nuevo paso 

//funcion para volver al paso anterior