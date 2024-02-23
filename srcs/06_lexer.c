/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:36:40 by anurtiag          #+#    #+#             */
/*   Updated: 2024/02/23 11:40:06 by anurtiag         ###   ########.fr       */
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
		list[++(*state)]->state_options = next;
	else
	{
		node = list[*state]->state_options;
		while(node->next)
			node = node->next;
		node->next = next;
	}
	next->token_type = ft_atoi(matrix[1]);
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

	// printf("La lista tiene una direccion de -->%p<--\n",list);
	options = (t_options *)malloc(sizeof(t_options));
	if (!options)
		return(1);
	i = -1;
	state = 0;
	list[state]->state_options = options;
	options->next = NULL;
	while (++i < 100)
	{
		// printf("i vale %zu\n", i);
		line = get_next_line(fd);
		if (!line)
			return(1);
		make_g_list(line, list, &state, options);
		// printf("%zu\t%d\t%d\t%d\t%d\n", state, list[state]->state_options->token_type, list[state]->state_options->action, list[state]->state_options->next_state, list[state]->state_options->nbr_red);
		free(line);
	}
	i = -1;
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
	int	i;

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
		token = token->next;
	}
	token->next = NULL;
	return(0);
}

int lexer(char **input)
{
	int 			fd;
	t_states		**list;
	t_token			*t_node;
	size_t			i;
	t_options		*options;

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
		// printf("en el bucle de lexer?  -->%p<--\ni vale %zu\n",list[i], i);
	}
	t_node = (t_token *)malloc(sizeof(t_token));
	if(!t_node)
		return (1);
	// printf("justo antes de charge table list es: %p\n", list);
	charge_table(fd, list);
	i = -1;
	while (++i <= 30)
	{
		options = list[i]->state_options;
		while(options->next)
		{
			printf("%zu\t%d\t%d\t%d\t%d\n", i, options->token_type, options->action, options->next_state, options->nbr_red);
			options = options->next;
		}
		printf("%zu\t%d\t%d\t%d\t%d\n", i, options->token_type, options->action, options->next_state, options->nbr_red);
	}
	tokenizer(input, t_node);
	return (0);
}

// int	main(void)
// {
// 	char	**input;
// 	char	*s = "echo \"patata\" | wc -l > outfile";
// 	input = ft_split(s, ' ');
// 	lexer(input);
// 	freematrix(input);
// 	return(0);
// }

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