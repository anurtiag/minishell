/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/29 12:42:36 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
 
int	print_history(char *line, t_input **struct_input)
{
	if (tokenization(line, struct_input) == FALSE)
	{
		return (printf("syntax error\n"), FALSE);
	}
	return (TRUE);
}

// void	print_env(char	**env)
// {
// 	while (*env)
// 	{
// 		printf("%s\n", *env);
// 		env++;
// 	}
// }

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
		{
			printf("donde petas\n");
			s++;
		}
	}
	return (input);
}

char	*analyze_input(char *input)
{
	char	*tmp;
	char	*line;
	size_t	control;

	control = TRUE;
	beyond_pipe(input, &control);
	while (control == FALSE)
	{
		input = join_line(input, tmp, line, &control);
		if (!input)
			return (NULL);
	}
	input = add_space(input, '>');
	input = add_space(input, '<');
	return(input);
}

void	open_quotes(char *input)
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
		write(2, "ERROR: open quotes\n", 19);
}

void	prepare_program(t_input **struct_input, char **envp)
{
	*struct_input = (t_input *)malloc(sizeof(t_input));
	load_history();
	save_env(envp, struct_input);
	//signal_receiver();
	read_table(struct_input);
}

 int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_input *struct_input;
	char	**prueba;
	int		control[2];

	(void)argc;
	(void)argv;
	control[0] = TRUE;
	control[1] = TRUE;
	input = NULL;
	prepare_program(&struct_input, envp);
	while (1)
	{
		input = readline("Minishell>>");
		if (input == NULL || ft_strncmp(input, "exit", 5) == 0)
			break ;

		//printf("el input es:--->%s<----\n", input);
		open_quotes(input);
		input = analyze_input(input);
		prueba = ft_bash_split(input, ' ', control);

		print_history(input, &struct_input);
		create_tokens_analyzer(&struct_input);
		save_history(input);
		free(input);
	}
	return (0);
}
