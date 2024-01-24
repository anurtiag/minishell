/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:42:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/24 20:25:01 by emimenza         ###   ########.fr       */
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
# define SPACE_M 32

typedef struct s_input
{
	char				**token_raw;
	struct s_ent_var	*ent_var;
	
}				t_input;

typedef struct s_ent_var
{
	char				*name;
	char				*content;
	struct	s_ent_var 	*next;
}				t_ent_var;

int	check_special_character(char *input, char c);
//bash_split.c
char	**ft_bash_split(char const *s, char c, int *control, t_ent_var **variable_list);

//tokenization.c
int	tokenization(char *input, t_input *struct_input);

//ent_var.c
int     ft_look_4_equal(char const*token, int start, int end, t_ent_var **variable_list);
void    ft_print_var(t_input *input);

#endif