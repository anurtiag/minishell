/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_analyzer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:04:19 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/26 17:42:20 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Prints the token list
void	print_token_list(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		printf("Data: %s, Type: %d, Dir: %p, Next Dir %p\n", \
		current->data, current->type, current, current->next);
		current = current->next;
	}
}

//This function assign type depending on the data
t_token	*assign_token_types(char *raw)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (new_token);
	if (ft_strcmp(raw, "<") == 0)
		new_token->type = 2;
	else if ((ft_strcmp(raw, ">") == 0) || ft_strcmp(raw, "2>") == 0)
		new_token->type = 1;
	else if (ft_strcmp(raw, "<<") == 0)
		new_token->type = 3;
	else if (ft_strcmp(raw, ">>") == 0)
		new_token->type = 4;
	else if (ft_strcmp(raw, "|") == 0)
		new_token->type = 5;
	else if (ft_strcmp(raw, "$END") == 0)
		new_token->type = -2;
	else
		new_token->type = 0;
	new_token->data = ft_strdup(raw);
	new_token->left = NULL;
	new_token->right = NULL;
	new_token->middle = NULL;
	new_token->next = NULL;
	return (new_token);
}

//Creates the tokens taking the token_raw
// void create_tokens_analyzer(t_input **struct_input)
// {
// 	char **token_raw;
// 	t_token *tokens;
// 	int i;
// 	t_token *new_token;
// 	t_token *last_token;

// 	token_raw = (*struct_input)->token_raw;
// 	tokens = NULL;
// 	i = -1;
// 	while (token_raw[++i] != NULL)
// 	{
// 		new_token = assign_token_types(token_raw[i]);
// 		if (new_token == NULL)
// 			return;
// 		if (tokens == NULL)
// 		{
// 			tokens = new_token;
// 			last_token = tokens;
// 		}
// 		else
// 		{
// 			last_token->next = new_token;
// 			last_token = last_token->next;
// 		}
// 	}
// 	add_last_token(last_token, &tokens);
// 	start_anaylizer(struct_input, tokens);
// }

void	create_tokens_analyzer(t_input **struct_input)
{
	char	**token_raw;
	t_token	*tokens;
	int		i;
	t_token	*new_token;
	t_token	*last_token;

	i = -1;
	tokens = NULL;
	token_raw = (*struct_input)->token_raw;
	while (token_raw[++i])
	{
		new_token = assign_token_types(token_raw[i]);
		if (!new_token)
			return ;
		if (!tokens)
			tokens = new_token;
		else
		{
			last_token->next = new_token;
		}
		last_token = new_token;
	}
	add_last_token(last_token, &tokens);
	start_anaylizer(struct_input, tokens);
}

void	add_last_token(t_token *last_token, t_token **tokens)
{
	t_token	*end_token;

	end_token = assign_token_types("$END");
	if (end_token != NULL)
	{
		if (*tokens == NULL)
			*tokens = end_token;
		else
			last_token->next = end_token;
	}
}
