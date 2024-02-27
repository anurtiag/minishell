/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:36:40 by anurtiag          #+#    #+#             */
/*   Updated: 2024/02/26 11:45:06 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void freematrix(char **matrix)
{
	int i;

	i = -1;
	while(matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
}

int	make_g_list(char *line, t_states **list, size_t *state, t_options *node)
{
	char		**matrix;
	t_options	*next;

	matrix = ft_split(line, '\t');
	if (!matrix)
		return (1);
	next = (t_options *)malloc(sizeof(t_options));
		if (!next)
			return(1);
	if ((int)*state != ft_atoi(matrix[0]))
	{
		list[++(*state)]->options = next;
		next->option_num = 0;
	}
	else
	{
		node = list[*state]->options;
		while(node->next)
			node = node->next;
		node->next = next;
		next->option_num = node->option_num + 1;
	}
	next->t_type = ft_atoi(matrix[1]);
	next->action = ft_atoi(matrix[2]);
	next->next_state = ft_atoi(matrix[3]);
	next->nbr_red = ft_atoi(matrix[4]);
	next->next = NULL;
	freematrix(matrix);
	return (0);
}

int	charge_table(int fd, t_states **list)
{
	size_t		i;
	size_t		state;
	char		*line;
	t_options	*options;

	options = (t_options *)malloc(sizeof(t_options));
	if (!options)
		return(1);
	i = -1;
	state = 0;
	list[state]->options = options;
	// options->option_num = 0;
	options->next = NULL;
	while (++i < 100)
	{
		line = get_next_line(fd);
		if (!line)
			return(1);
		make_g_list(line, list, &state, options);
		free(line);
	}
	return (0);
}

int	make_t_list(char *input, t_token *token, int type)
{
	t_token *next;
	size_t	len;

	next = (t_token *)malloc(sizeof(t_token));
	if(!next)
		return (1);
	len = ft_strlen(input) + 1;
	token->data = (char *)malloc(len * sizeof(char));
	if (!token->data)
		return(1);
	ft_strlcpy(token->data, input, len);
	token->type = type;
	token->next = next;
	return (0);
}

int	tokenizer(char **input, t_token *token)
{
	size_t	i;

	i = -1;
	while(input[++i])
	{
		if (ft_strlen(input[i]) == 1 && input[i][0] == '|')
			make_t_list(input[i], token, PIPE);
		else if (ft_strlen(input[i]) == 1 && input[i][0] == '<')
			make_t_list(input[i], token, RED_FROM);
		else if (ft_strlen(input[i]) == 1 && input[i][0] == '>')
			make_t_list(input[i], token, RED_TO);
		else if (ft_strlen(input[i]) == 2 && ft_strncmp(input[i], "<<", 2) == 0)
			make_t_list(input[i], token, DLESS);
		else if (ft_strlen(input[i]) == 2 && ft_strncmp(input[i], ">>", 2) == 0)
			make_t_list(input[i], token, DGREAT);
		else
			make_t_list(input[i], token, WORD);
		// printf("el token %zu tiene una direccion de %p y su contenido es de %s\n", i, token, token->data);
		token = token->next;
	}
	token->next = NULL;
	return(0);
}

t_token	*shift(t_token *stack, t_token *input)
{
	if(stack)
	{
		while(stack->next)
			stack = stack->next;
		stack->next = input;
	}
	else
		stack = input;
	stack->next = NULL;
	return(stack);
}

t_options	*find_rule(t_states **list, t_token *token, size_t state)
{
	while (list[state]->options->t_type != token->type && list[state]->options->next)
		list[state]->options = list[state]->options->next;
	if (list[state]->options->t_type == token->type || list[state]->options->t_type == -1)
		return (list[state]->options);
	else
		return (NULL);
}

void	action(t_parsing *parse, t_token *stack, t_token *input)
{
	if(parse->rule)
}

int shift_n_reduce(t_states **list, t_token *input)
{
	t_token	*stack;
	size_t	state;
	t_parsing	*parse;

	parse = (t_parsing *)malloc(sizeof(t_parsing) * 1);
	if(!parse)
		return (1);
	parse->state = 0;
	parse->prev = NULL;
	while (input)
	{
		parse->rule = find_rule(list, input, state);
	}
	return(0);
}


int lexer(char **input)
{
	int 			fd;
	t_states		**list;
	t_token			*t_node;
	size_t			i;
	t_options		*node;

	fd = open("parsing_table", O_RDONLY);
	if (fd < 0)
		return (1);
	i = -1;
	list = (t_states **)malloc(sizeof(t_states *) * 31);
	if(!list)
		return (1);
	while(++i < 31)
	{
		list[i] = (t_states *)malloc(sizeof(t_states) * 1);
		if (!list[i])
			return (1);
		list[i]->state = i;
	}
	t_node = (t_token *)malloc(sizeof(t_token));
	if(!t_node)
		return (1);
	charge_table(fd, list);
	tokenizer(input, t_node);
	// printf("La direccion de memoria es:%p y su contenido es de %s\n", t_node, t_node->data);
	// while(t_node->next)
	// {
	// 	printf("el dato es %s\n", t_node->data);
	// 	t_node = t_node->next;
	// }
	// i = -1;
	// while (++i <= 30)
	// {
	// 	node = list[i]->options;
	// 	while(node->next)
	// 	{
	// 		printf("%zu\t%d\t%d\t%d\t%d\t%d\n", i, node->t_type, node->action, node->next_state, node->nbr_red, node->option_num);
	// 		node = node->next;
	// 	}
	// 	printf("%zu\t%d\t%d\t%d\t%d\t%d\n", i, node->t_type, node->action, node->next_state, node->nbr_red, node->option_num);
	// }
	shift_n_reduce(list, t_node);
	return (0);
}

int	main(void)
{
	char	**input;
	char	*s = "echo \"patata\" | wc -l > outfile";
	input = ft_split(s, ' ');
	lexer(input);
	freematrix(input);
	return(0);
}

// while(g_node->next)
// 	{
// 		printf("El estado es %d\nel token es %d\nla accion es %d\nel siguiente estado es %d\nel reduced es %d\n\n",node->state, node->token_type, node->action, node->next_state, node->nbr_red);
// 		g_node = node->next;
// 	}

// while(t_node->next)
// 	{
// 		printf("El token es: %s\nsu tipo es %d\n\n",t_node->data, t_node->type);
// 		t_node = t_node->next;
// 	}
	// i = -1;
	// while (++i <= 30)
	// {
	// 	options = list[i]->state_options;
	// 	while(options->next)
	// 	{
	// 		printf("%zu\t%d\t%d\t%d\t%d\n", i, options->token_type, options->action, options->next_state, options->nbr_red);
	// 		options = options->next;
	// 	}
	// 	printf("%zu\t%d\t%d\t%d\t%d\n", i, options->token_type, options->action, options->next_state, options->nbr_red);
	// }