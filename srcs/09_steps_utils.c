/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_steps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:29:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/01 10:22:12 by emimenza         ###   ########.fr       */
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
int	stack_size(t_token *tokens)
{
	t_token *current = tokens;
	int i = 0;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
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
void	add_step(t_input *struct_input, t_options *option, t_token *tree_stack, t_token *input_token, t_step **c_step)
{
	t_step		*step;
	t_states	*state;

	step = NULL;
	step = (t_step *)malloc(sizeof(t_step));

	if (step == NULL)
		return ;
	
	state = (t_states *)malloc(sizeof(t_states));
	if (state == NULL)
		return ((void)free(step));

	step->step_nbr = (*c_step)->step_nbr + 1;
	step->state_nbr = option->next_state;

	if (find_state(struct_input->parsing_table, option->next_state, &state) == FALSE)
	{
		free(state);
		free(step);
		return ;
	}
	step->state = state;
	step->option_nbr = 0;
	step->tree_stack = tree_stack;
	step->input = input_token;
	step->next = NULL;
	step->prev = *c_step;
	(*c_step)->next = step;
	*c_step = step;
}

//Returns the last node of the stack
t_token	*last_node_stack(t_token *stack)
{
	t_token	*current;

	current = NULL;
	if (stack == NULL)
		return NULL;
	current = stack;
	while (current->next != NULL)
		current = current->next;		
	return (current);
}

//funcion para volver al paso anterior
void	ret_to_prev(t_step **c_step)
{
	t_step	*prev_step;

	prev_step = (*c_step)->prev;
	prev_step->tree_stack = (*c_step)->tree_stack;
	prev_step->input = (*c_step)->input;
	free(*c_step);
	*c_step = prev_step;
}
