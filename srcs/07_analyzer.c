/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_analyzer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:04:19 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/27 16:27:58 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void print_token_list(t_token *tokens)
{
	t_token *current = tokens;

	while (current != NULL)
	{
		printf("Data: %s, Type: %d\n", current->data, current->type);
		current = current->next;
	}
}

// Función para asignar el tipo de data y el tipo de un token
t_token *assign_token_types(char *token_raw)
{
	t_token *new_token;
	new_token = (t_token *)malloc(sizeof(t_token));

	if (new_token == NULL)
		return (new_token);
	if (strcmp(token_raw, "<") == 0)
		new_token->type = 2;
	else if (strcmp(token_raw, ">") == 0)
		new_token->type = 1;
	else if (strcmp(token_raw, "<<") == 0)
		new_token->type = 3;
	else if (strcmp(token_raw, ">>") == 0)
		new_token->type = 4;
	else if (strcmp(token_raw, "|") == 0)
		new_token->type = 5;
	else
		new_token->type = 0;
	new_token->data = ft_strdup(token_raw);
	new_token->left = NULL;
	new_token->right = NULL;
	new_token->next = NULL;
	return (new_token);
}

// Función para crear tokens a partir de token_raw
void create_tokens_analyzer(t_input **struct_input)
{
	char		**token_raw;    //double ptr with the raw input
	t_token		*tokens;        //list with the tokens
	int			i;              //iterator for the double ptr
	t_token		*new_token;     //new token
	t_token		*last_token;       //current token

	token_raw = (*struct_input)->token_raw;
	tokens = NULL;
	i = 0;
	while (token_raw[i] != NULL)
	{
		new_token = assign_token_types(token_raw[i]);
		if (new_token == NULL)
			return;
		if (tokens == NULL)
		{
			tokens = new_token;
			last_token = tokens;
		}
		else
		{
			last_token->next = new_token;
			last_token = last_token->next;
		}
		i++;
	}
	//print_token_list(tokens);
	start_anaylizer(struct_input, tokens);
}
