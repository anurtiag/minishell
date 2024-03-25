/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:17:49 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/24 17:16:29 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Función para liberar un árbol de tokens recursivamente
void free_tree(t_token *root)
{
	if (root == NULL)
		return;

	free_tree(root->left);
	free_tree(root->middle);
	free_tree(root->right);
	free(root->data);
	root->data = NULL;
	free(root);
	root = NULL;
}

void free_token_tree(t_token *head)
{
	t_token *temp;
	int		flag;

	flag = 0;
	while (head != NULL && flag != 1)
	{
		temp = head->next;
		if (temp && temp->type && (temp->type == -2))
			flag = 1;
		free_tree(head);
		head = temp;
	}
}


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

void free_double(char **double_ptr)
{
	char	**temp;

	if (double_ptr == NULL)
		return;

	temp = double_ptr;

	while (*double_ptr != NULL)
	{
		// printf("no deberiammos de entrar aqui no\n");
		free(*double_ptr);
		*double_ptr = NULL;
		double_ptr++;
	}
	free(temp); // Liberamos la memoria del puntero doble en sí
}

void	free_tokens(t_token *token)
{
	t_token		*tmp_token;
	while (token != NULL)
	{
		tmp_token = token->next;
		free(token->data);
		free(token);
		token = tmp_token;
	}
}

void	free_steps(t_step *steps)
{
	t_step		*tmp_step;

	free_tokens(steps->input);
	free_token_tree(steps->tree_stack);
	while (steps != NULL)
	{
		tmp_step = steps->next;
		free(steps);
		steps = tmp_step;
	}
}

//Function to clear all
void	free_all(t_input *struct_input, char *history)
{
	t_var_list	*tmp_env;
	t_var_parsed_table	*tmp_parsed;
	free(history);

	//free env variables
	while ((struct_input)->ent_var)
	{
		tmp_env = (struct_input)->ent_var->next;
		free((struct_input)->ent_var->name);
		free((struct_input)->ent_var->content);
		free((struct_input)->ent_var);
		(struct_input)->ent_var = tmp_env;
	}

	free_parsed_table(&(struct_input)->parsed_table);
	
	free_states((struct_input)->parsing_table);
	
	free_double((struct_input)->token_raw);

	free(struct_input);
}