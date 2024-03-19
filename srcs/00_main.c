/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/18 16:54:15 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
int		g_main_loop;

//If a pipe is the last char opens a here doc to complete it
void	beyond_pipe(char *input, size_t *control)
{
	char	*pipe;

	pipe = ft_strrchr(input, '|');
	if (!pipe)
	{
		*control = TRUE;
		return ;
	}
	pipe++;
	while(*pipe != '\0')
	{
		if(*pipe != ' ' && *pipe != '\t')
		{
			*control = TRUE;
			return ;
		}
		pipe++;
	}
	*control = FALSE;
}

//If the last char is a pipe generates a line and joins it
char	*join_line(char *input, char *tmp, char *line, size_t *control)
{
	write(1,">", 1);
	tmp = input;
	input = ft_strjoin(input, " ");
	if (!input)
		return (free(tmp), NULL);
	free(tmp);
	line = get_next_line(0);
	if (!line)
		return (NULL);
	tmp = line;
	line = ft_strtrim(line, "\n");
	if (!line)
		return (free(tmp), NULL);
	free(tmp);
	tmp = input;
	input = ft_strjoin(input, line);
	if (!input)
		return (free(tmp), free(line), NULL);
	free(tmp);
	free(line);
	beyond_pipe(input, control);
	return(input);
}

//If the redirect and the filename are joined adds a space
char	*add_space(char *input, char c)
{
	char	*s;
	char	*first;
	char	*last;
	char	*tmp;


	s = ft_strchr(input, c);
	if (!s)
		return (input);
	if(*(s + 1) == c)
		s++;
	while (s && (ft_isalnum((int)*(s + 1)) == 1))
	{
		first = ft_substr(input, 0, (s - input + 1));
		last = ft_strdup(s + 1);
		free(input);
		tmp = first;
		first = ft_strjoin(first, " ");
		free(tmp);
		input = ft_strjoin(first, last);
		free(first);
		free(last);
		s = ft_strchr((s + 1), c);
		if(s && *(s + 1) == c)
			s++;
	}
	return (input);
}

//Checks if there are any open quotes
int	open_quotes(char *input)
{
	size_t	s_quote;
	size_t	d_quote;

	s_quote = TRUE;
	d_quote = TRUE;
	while (*input != '\0')
	{
		if (*input == '\"' && (s_quote == TRUE && d_quote == TRUE))
			d_quote = FALSE;
		else if (*input == '\"' && (s_quote == TRUE && d_quote == FALSE))
			d_quote = TRUE;
		if (*input == '\'' && (s_quote == TRUE && d_quote == TRUE))
			s_quote = FALSE;
		else if (*input == '\'' && (s_quote == FALSE && d_quote == TRUE))
			s_quote = TRUE;
		input++;
	}
	if (s_quote == FALSE || d_quote == FALSE)
	{
		printf("\033[0;31mERROR: open quotes\033[0m\n");
		return (FALSE);
	}
	return (TRUE);		
}

//Analize the input looking for errors
int		analyze_input(char **input)
{
	char	*tmp;
	char	*line;
	size_t	control;

	control = TRUE;
	beyond_pipe(*input, &control);
	if (open_quotes(*input) == FALSE)
		return (FALSE);
	while (control == FALSE)
	{
		*input = join_line(*input, tmp, line, &control);
		if (!input)
			return (FALSE);
	}
	*input = add_space(*input, '>');
	*input = add_space(*input, '<');
	return (TRUE);
}

//Prepares the variables and structures for the program
void	prepare_program(t_input **struct_input, char **envp)
{
	*struct_input = (t_input *)malloc(sizeof(t_input));

	load_history();
	save_env(envp, struct_input);
	signal_receiver();
	read_table(struct_input);
}

//Checks the input 
int	check_input(char **line, t_input **struct_input)
{
	if (ft_strlen(*line) == 0)
		return (FALSE);
		
	if (analyze_input(line) == FALSE)
		return (FALSE);
	
	//ft_print_var(*struct_input);
	if (tokenization(*line, struct_input) == FALSE)
	{
		return (printf("\033[0;31mSYNTAX ERROR TOKENIZATION\033[0m\n"), FALSE);
	}
	return (TRUE);
}

 int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_input *struct_input;

	if (argc > 1)
		return (printf("Invalid input\n"), 2);
	(void)argv;
	input = NULL;
	g_main_loop = 1;
	prepare_program(&struct_input, envp);
	while (1)
	{
		input = readline("Patata>>");
		if (input == NULL)
			break ;
		if (ft_strncmp(input, "clear", 5) == 0)
			printf("\033[H\033[2J");
		g_main_loop = 0;
		if (check_input(&input, &struct_input) == TRUE)
			create_tokens_analyzer(&struct_input);
		save_history(input);
		free(input);
		g_main_loop = 1;
	}
	free(input);
	free_all(struct_input, input);
	return (0);
}
