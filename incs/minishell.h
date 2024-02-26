/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:42:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/23 12:55:55 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/Libft/libft.h"
# include "../libs/GNL/get_next_line.h"


# define TRUE 1
# define FALSE 0
# define ERROR -1
# define SPACE_M 32
# define REDUCE -1
# define WORD 0
# define RED_TO 1
# define RED_FROM 2
# define DLESS 3
# define DGREAT 4
# define PIPE 5
# define PIPE_SEQUENCE 100
# define SIMPLE_CMD 101
# define CMD_NAME 102
# define CMD_WORD 103
# define CMD_PREFIX 104
# define CMD_SUFFIX 105
# define IO_REDIRECT 106
# define IO_FILE 107
# define FILENAME 108
# define IO_HERE 109
# define HERE_END 110

typedef struct	s_states
{
	int					state;
	struct s_options	*options;
}				t_states;

typedef struct	s_parsing
{
	int			step;
	int			state;
	int			option;
	t_options	*rule;
	t_token		*stack;
	t_token		*input;
	t_parsing	*next;
	t_parsing	*prev;
}				t_parsing;

typedef struct s_options
{
	int			t_type;
	int			action;
	int			next_state;
	int			nbr_red;//number of reduced tokens
	int			option_num;
	struct s_options	*next;
}				t_options;

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}				t_token;

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

typedef struct s_var_parsed_table
{
	char						**env;
	char						**cmd; //primera linea 'echo' segunda linea 'patata'
	char						*path; //nombre del comando con la ruta 'users/bin/ls'
	int							fd_in;
	int							fd_out;
	struct	s_var_parsed_table	*next;
}				t_var_parsed_table;

//MAIN
static int	print_history(char *line, t_input **struct_input);

//HISTORY
static int	check_history_file(void);
void		load_history(void);
void		save_history(char	*input);

//SIGNAL
static void	signal_handler(int	signal);
void		signal_receiver(void);

//VARIABLES
static void	print_env(char	**env);
void		save_env(char **envp, t_input **struct_input);

//LOOK FOR EQUALS
void		ft_print_var(t_input *input);
static void	ft_add_var(t_var_list **list, char *name, char *content);
static int	ft_var_found(t_var_list **list, char *name, char *content);
static void	ft_trim_var_equal(char *token, int equal_pos, int start, int end, t_var_list **variable_list);
int			ft_look_4_equal(char const *token, int start, int end, t_var_list **variable_list);

//LOOK FOR DOLLARS
static int	ft_find_variable(char *match_var_name, t_var_list **variable_list, char **content);
static int	ft_trim_var_dollar(char *token, int start, int end, t_var_list **variable_list, char **content);
int			ft_look_4_dollar(char const *token, int start, int end, t_var_list **variable_list, char **content);

//LEXER

//BASH SPLIT
static void	ignore_separator(char const *s, int *control, int *i);
static	int	ft_count(char const *s, char c, int *control);
static void	freeall(char **splits);
static int	check_str(char **str, int j);
char	**ft_bash_split(char const *s, char c, int *control, t_var_list **variable_list);

//TOKENIZATION
int	tokenization(char *input, t_input **struct_input);

#endif