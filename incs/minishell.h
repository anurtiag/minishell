/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:42:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/25 15:25:30 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define SPACE_M 32

//main struct for the input
typedef struct s_input
{
	char				**token_raw;
	struct s_var_list	*ent_var;
}				t_input;

//linked list for the enviroment variables
typedef struct s_var_list
{
	char				*name;
	char				*content;
	struct	s_var_list 	*next;
}				t_var_list;

//MAIN
int	print_history(char *line, t_input **struct_input);

//BASH SPLIT
static void	ignore_separator(char const *s, int *control, int *i);
static	int	ft_count(char const *s, char c, int *control);
static void	freeall(char **splits);
static int	check_str(char **str, int j);
char	**ft_bash_split(char const *s, char c, int *control, t_var_list **variable_list);

//CHECK INPUT

//LOOK FOR EQUALS
void    ft_print_var(t_input *input);
void    ft_add_var(t_var_list **list, char* name, char *content);
int     ft_var_found(t_var_list **list, char* name, char* content);
void    ft_trim_var_equal(char *token, int equal_pos, int start, int end, t_var_list **variable_list);
int     ft_look_4_equal(char const *token, int start, int end, t_var_list **variable_list);

//LOOK FOR DOLLARS
int	ft_look_4_dollar(char const *token, int start, int end, t_var_list **variable_list, char **content);

//TOKENIZATION
int	tokenization(char *input, t_input **struct_input);

#endif