/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:30:01 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/27 13:01:03 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_step	*init_first_step(t_input **struct_input, t_token *input_token)
{
	t_step		*first_step;
	t_states	*state;

	first_step = NULL;
	first_step = (t_step *)malloc(sizeof(t_step));
	if (first_step == NULL)
		return (first_step);
	state = (t_states *)malloc(sizeof(t_states));
	if (state == NULL)
		return (free(first_step), first_step);
	first_step->step_nbr = 0;
	first_step->state_nbr = 0;
	if (find_state((*struct_input)->parsing_table, 0, &state) == FALSE)
	{
		free(state);
		free(first_step);
		return (first_step);
	}
	first_step->state = state;
	first_step->option_nbr = 0;
	first_step->tree_stack = NULL;
	first_step->input = input_token;
	first_step->next = NULL;
	first_step->prev = NULL;
	return (first_step);
}

int	start_anaylizer(t_input **struct_input, t_token *input_token)
{
	t_step	*step;
	t_token	*c_token;
	t_options	*def_option;
	t_options	*available_option;
	
	step = init_first_step(struct_input, input_token);
	if (step == NULL)
		return (printf("ERROR INIT THE FIRST STEP\n"), FALSE);

	//cogemos el primer nodo de input como nuestro token a evaluar
	c_token = step->input;
	
	while (step->input != NULL)
	{     //(si vamos a un estado de una opcion que es token simple nuestro token a evaluar es el stack, sino el ultimo del input)


		//conseguimos la opcion default siempre que la tengamos y la opcion disponible depende de nuestro c_token
		def_option = find_option(step->state, -1);
		available_option = find_option(step->state, c_token->type);

		//miramos si nuestro token es el mismo que el default (volvemos al paso anterior)
		if (def_option && (def_option->next_state == c_token->type))
		{
			//volvemos al paso anterior manteniendo nuestro c_token;
		}
		//miramos si es mismo tipo que un token simple (si es asi aplicamos la accion y movemos al siguiente paso creandolo)
		else if ((available_option != NULL))
		{
			//aplicamos accion y creamos un nuevo paso;
		}
		else if ((available_option == NULL) && def_option)
		{
			//si no coincide con ningun tipo de token, y tenemos default, hacemos default (volvemos al paso anterior)
		}
		else if ((available_option == NULL) && (def_option == NULL))
		{
			//si no coincide con ninguno y no tenemos default, systax error;
		}

		break;
	}
	if ((step->tree_stack != NULL) && ((stack_size(step->tree_stack) == 1) && (step->tree_stack->type == 100)))
	{
		return (TRUE);
	}
	else
		return (FALSE);
}
