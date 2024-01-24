/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:42:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/24 16:10:22 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0
# define SPACE 32

typedef struct s_input
{
	char	**token_raw;
}				t_input;

int	check_special_character(char *input, char c);
//bash_split.c
char	**ft_bash_split(char const *s, char c, int *control);
//tokenization.c
int	tokenization(char *input, t_input *struct_input);

#endif