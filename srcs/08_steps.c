/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:30:01 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/28 14:55:45 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


void print_steps_info(t_step *first_step) {
    t_step *current_step = first_step;
    int step_count = 0;

    printf("Steps Information:\n");
    printf("-------------------\n");

    while (current_step != NULL) {
        printf("Step %d:\n", step_count);
        printf("  Step Number: %d\n", current_step->step_nbr);
        printf("  State Number: %d\n", current_step->state_nbr);
        // Aquí puedes imprimir más información sobre el estado, la pila de árboles, etc.
        // Por ejemplo:
        // printf("  State Info: ...\n");
        // printf("  Tree Stack: ...\n");
        // printf("  Input Token: ...\n");
        
        step_count++;
        current_step = current_step->next;
    }

    printf("-------------------\n");
    printf("Total Steps: %d\n", step_count);
}

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
	
	//end_flag == FALSE ||
	while (end_flag == FALSE)
	{	
		printf("\n\033[0;33m-----START OF BUCLE INPUT:---%i---\033[0m\n", end);
		print_token_list(c_step->input);
		printf("-----STACK:-----\n");
		print_token_list(c_step->tree_stack);
		printf("\n");
	
		if (step->input == NULL && step->tree_stack != NULL && stack_size(step->tree_stack) == 1)
		{
			t_token *stack_top = last_node_stack(step->tree_stack);
			if (stack_top->type == 100)
			{
				// Regresa hasta el paso 0
				while (c_step->step_nbr != 0)
				{
					ret_to_prev(&c_step);
				}
			}
		}
		//conseguimos la opcion default siempre que la tengamos y la opcion disponible depende de nuestro c_token
		def_option = find_option(c_step->state, -1);
		available_option = find_option(c_step->state, c_token->type);
		printf("\033[0;32mevaluate node ->%s<- type ->%i<- \033[0m\n", c_token->data, c_token->type);
		
		//miramos si nuestro token es el mismo que el default (volvemos al paso anterior)
		if (def_option && (def_option->next_state == c_token->type))
		{
			//volvemos al paso anterior manteniendo nuestro c_token;
			printf("MISMO QUE EL DEFAULT\n");
			apply_action(def_option, &c_step, c_token, &end_flag);
		}
		//miramos si es mismo tipo que un token simple (si es asi aplicamos la accion y movemos al siguiente paso creandolo)
		else if ((available_option != NULL))
		{
			//aplicamos accion
			apply_action(available_option, &c_step, c_token, &end_flag);
			add_step(*struct_input, available_option, c_step->tree_stack, c_step->input, &c_step);
			
			//(si vamos a un estado de una opcion que es token simple nuestro token a evaluar es el ultimo de stack, sino el primero del input)
			if (c_step->input && (c_token->type >= 100 || c_token->type == 5))
				c_token = c_step->input;
		}
		else if ((available_option == NULL) && def_option)
		{
			//si no coincide con ningun tipo de token, y tenemos default, hacemos default (volvemos al paso anterior)
			//aplicamos accion
			apply_action(def_option, &c_step, c_token, &end_flag);
			if (last_node_stack(c_step->tree_stack)->type >= 100)
				c_token = last_node_stack(c_step->tree_stack);
		}
		else if ((available_option == NULL) && (def_option == NULL))
		{
			//si no coincide con ninguno y no tenemos default, systax error;
			if ((c_step->input->type -2 ) && (stack_size(c_step->tree_stack) == 0) && (last_node_stack(c_step->tree_stack)->type == 100))
			{
				printf("\n\033[0;35mRETURNING TO 0\n\033[0m\n");
				while (c_step->step_nbr != 0)
					ret_to_prev(&c_step);
			}
			else
				break;
		}
		end++;
	}

	// print_steps_info(step);
	// printf("-----INPUT:-----\n");
	// print_token_list(step->input);
	// printf("-----STACK:-----\n");
	// print_token_list(step->tree_stack);
	
	// if ((step->tree_stack != NULL) && ((stack_size(step->tree_stack) == 1) && (step->tree_stack->type == 100)))
	// {
	// 	return (TRUE);
	// }
	// else
	// 	return (FALSE);
}
