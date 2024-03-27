/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:12:20 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/27 12:46:46 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Reduce the tokens of the stack
void	ft_reduce(t_options *options, t_step **c_step)
{
	t_token	*token_4;
	t_token	*token_3;
	t_token	*token_2;
	t_token	*token_1;
	t_token	*join_token;
	t_token	*start_stack;

	join_token = NULL;
	if (options->nbr_red == 1)
	{
		token_1 = last_node_stack((*c_step)->tree_stack);
		token_1->type = options->next_state;
	}
	else if (options->nbr_red == 2)
	{
		start_stack = (*c_step)->tree_stack;
		join_token = (t_token *)malloc(sizeof(t_token));
		if (join_token == NULL)
			return;
		join_token->data = ft_strdup("Joined token");
		join_token->type = options->next_state;
		join_token->left = NULL;
		join_token->right = NULL;
		join_token->middle = NULL;
		join_token->next = NULL;
		token_1 = last_node_stack(start_stack);
		token_2 = start_stack;
		token_3 = start_stack;
		while (token_2->next != token_1)
			token_2 = token_2->next;
		while ((token_3->next != token_2) && (token_3 != token_2))
			token_3 = token_3->next;
		join_token->left = token_2;
		join_token->right = token_1;
		join_token->left->next = NULL;
		join_token->right->next = NULL;
		if (token_2 == token_3)
		{
			(*c_step)->tree_stack = NULL;
			(*c_step)->tree_stack = join_token;
		}
		else
			token_3->next = join_token;
	}
	else if (options->nbr_red == 3)
	{
		start_stack = (*c_step)->tree_stack;
		join_token = (t_token *)malloc(sizeof(t_token));
		if (join_token == NULL)
			return;
		join_token->data = ft_strdup("Joined token");
		join_token->type = options->next_state;
		join_token->left = NULL;
		join_token->right = NULL;
		join_token->middle = NULL;
		join_token->next = NULL;
		token_1 = last_node_stack(start_stack);
		token_2 = start_stack;
		token_3 = start_stack;
		token_4 = start_stack;
		while (token_2->next != token_1)
			token_2 = token_2->next;
		while ((token_3->next != token_2) && (token_3 != token_2))
			token_3 = token_3->next;
		while ((token_4->next != token_3) && (token_4 != token_3) && (token_4 != token_2))
			token_4 = token_4->next;
		join_token->left = token_3;
		join_token->middle = token_2;
		join_token->right = token_1;
		join_token->left->next = NULL;
		join_token->middle->next = NULL;
		join_token->right->next = NULL;
		if (token_3 == token_4)
		{
			(*c_step)->tree_stack = NULL;
			(*c_step)->tree_stack = join_token;
		}
		else
			token_4->next = join_token;
	}
}

//Shifts the first node of the input to the last position of stack
void	ft_shift(t_token **stack, t_token **input)
{
	t_token	*c_token;
	t_token	*c_stack;

	if (*input == NULL)
		return ;
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

//Apply the action received 
void	apply_action(t_options *opts, t_step **c_step, \
t_token *c_token, int *end)
{
	int	action_type;

	action_type = opts->action;
	if (action_type == 0)
		ft_shift(&(*c_step)->tree_stack, &(*c_step)->input);
	else if (action_type == 1)
	{
		ft_reduce(opts, c_step);
		ret_to_prev(c_step);
	}
	else if (action_type == 2)
		*end = TRUE;
}
