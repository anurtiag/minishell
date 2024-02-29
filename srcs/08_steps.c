/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:30:01 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/29 13:09:14 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Inits the first step of the analizer
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

//Main function of the analizer
int	start_anaylizer(t_input **struct_input, t_token *input_token)
{
	t_step		*step;
	t_step		*c_step;
	t_token		*c_token;
	t_options	*def_option;
	t_options	*available_option;
	int			end_flag;
	int			end = 0;

	end_flag = FALSE;
	c_step = init_first_step(struct_input, input_token);
	step = c_step;
	if (step == NULL)
		return (printf("ERROR INIT THE FIRST STEP\n"), FALSE);

	//cogemos el primer nodo de input como nuestro token a evaluar
	c_token = step->input;
	
	while (end_flag == FALSE)
	{
		// printf("\n\033[0;33m-----INPUT:---%i---\033[0m\n", end);
		// print_token_list(c_step->input);
		// printf("-----STACK:-----\n");
		// print_token_list(c_step->tree_stack);
		// printf("\n");

		//conseguimos la opcion default siempre que la tengamos y la opcion disponible depende de nuestro c_token
		def_option = find_option(c_step->state, -1);
		available_option = find_option(c_step->state, c_token->type);
		//printf("\033[0;32mevaluate node ->%s<- type ->%i<- \033[0m\n", c_token->data, c_token->type);
		//miramos si nuestro token es el mismo que el default (volvemos al paso anterior)
		if (def_option && (def_option->next_state == c_token->type))
		{
			//volvemos al paso anterior manteniendo nuestro c_token;
			//printf("MISMO QUE EL DEFAULT\n");
			apply_action(def_option, &c_step, c_token, &end_flag);
		}
		//No tenemos defualt y tenemos avail option
		else if ((available_option == NULL) && (def_option == NULL) && (c_token->type >= 100) && (c_step->state_nbr != 0))
			ret_to_prev(&c_step);
		//miramos si es mismo tipo que un token simple (si es asi aplicamos la accion y movemos al siguiente paso creandolo)
		else if ((available_option != NULL))
		{
			//aplicamos accion
			apply_action(available_option, &c_step, c_token, &end_flag);
			add_step(*struct_input, available_option, c_step->tree_stack, c_step->input, &c_step);
			
			//(si vamos a un estado de una opcion que es token simple nuestro token a evaluar es el ultimo de stack, sino el primero del input)
			if (c_step->input && (c_token->type >= 100 || c_token->type == 1 || c_token->type == 2 || c_token->type == 3 || c_token->type == 4 || c_token->type == 5))
				c_token = c_step->input;
		}
		else if ((available_option == NULL) && def_option)
		{
			//si no coincide con ningun tipo de token, y tenemos default, hacemos default (volvemos al paso anterior)
			//aplicamos accion
			apply_action(def_option, &c_step, c_token, &end_flag);
			if (last_node_stack(c_step->tree_stack)->type >= 100)
				c_token = last_node_stack(c_step->tree_stack);

			if (c_step->state_nbr == 22)
				c_token = c_step->input;
		}
		else if ((available_option == NULL) && (def_option == NULL))
		{
			printf("\033[0;31mSYNTAX ERROR\033[0m\n");
			break;
		}
		end++;
	}
}
