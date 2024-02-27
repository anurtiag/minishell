/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:12:20 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/27 17:45:55 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//shifts the first node of the input to the last position of stack
void	ft_reduce(t_options *options, t_step *c_step)
{
	t_token *c_token;

	if (options->nbr_red == 1)
	{
		c_token = last_node_stack(c_step->tree_stack);
		c_token->type = options->next_state;
	}
	
	c_step = c_step->prev;
	free(c_step->next);
	c_step->next = NULL;
}
void 	ft_shift(t_token **stack, t_token **input)
{
	t_token *c_token;
	t_token *c_stack;

	if (*input == NULL)
		return;
	c_token = *input;
	*input = c_token->next;
	c_token->next = NULL;
	c_stack = *stack;
	while (c_stack != NULL && (c_stack->next != NULL))
		c_stack = c_stack->next;
	if (c_stack == NULL)
		*stack = c_token;
	else
		c_stack->next = c_token;
}

void		apply_action(t_options *options, t_step *c_step, t_token *c_token, int *end_flag)
{
	int	action_type;

	action_type = options->action;
	if (action_type == -1)
	{
		//go
		printf("GO TO %i\n", options->next_state);
	}
	else if (action_type == 0)
	{
		//shift and go
		printf("SHIFT AND GO TO %i\n", options->next_state);
		ft_shift(&c_step->tree_stack, &c_step->input);
	}
	else if (action_type == 1)
	{
		//reduce
		ft_reduce(options, c_step);
		printf("REDUCE TO %i BACT TO %i\n", last_node_stack(c_step->tree_stack)->type, c_step->prev->state_nbr);
	}
	else if (action_type == 2)
	{
		//accept
		printf("ACCEPT\n");
		*end_flag = TRUE;
	}
}
