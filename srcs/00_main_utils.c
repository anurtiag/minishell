/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:31:53 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/26 13:37:26 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
	pipe ++;
	while (*pipe != '\0')
	{
		if (*pipe != ' ' && *pipe != '\t')
		{
			*control = TRUE;
			return ;
		}
		pipe++;
	}
	*control = FALSE;
}

//If the last char is a pipe generates a line and joins it
char	*join_line(char *input, size_t *control, t_input **struct_input)
{
	char	*tmp;
	char	*line;

	write(1, ">", 1);
	input = ft_strjoin(input, " ", 3);
	if (!input)
		return (NULL);
	line = get_next_line(0);
	if (!line)
	{
		*control = TRUE;
		print_error(13, NULL, struct_input);
		return (NULL);
	}
	tmp = line;
	line = ft_strtrim(line, "\n");
	if (!line)
		return (free(tmp), NULL);
	free(tmp);
	input = ft_strjoin(input, line, 15);
	if (!input)
		return (NULL);
	beyond_pipe(input, control);
	return (input);
}

//If the redirect and the filename are joined adds a space
int	add_space(char **input, char c, t_input **struct_input)
{
	char	*s;
	char	*s1;
	char	*first;
	char	*last;
	char	*tmp;

	s = ft_strchr(*input, c);
	if (!s)
		return (TRUE);
	s1 = ft_strrchr(*input, c);
	if (*(s1 + 1) == '\0')
		return (print_error(7, NULL, struct_input), FALSE);
	while (*(s + 1) == c)
		s++;
	while (s && (*(s + 1) && (*(s + 1) != ' ' && *(s + 1) != '\t')))
	{
		first = ft_substr(*input, 0, (s - *input + 1));
		last = ft_strdup(s + 1);
		free(*input);
		first = ft_strjoin(first, " ", 3);
		*input = ft_strjoin(first, last, 15);
		s = ft_strchr((s + 1), c);
		if (s && *(s + 1) == c)
			s++;
	}
	return (TRUE);
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
		print_error(3, NULL, NULL);
		return (FALSE);
	}
	return (TRUE);
}
