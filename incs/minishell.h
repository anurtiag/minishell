/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:42:23 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/04 13:47:38 by anurtiag         ###   ########.fr       */
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
# include <stdint.h>

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

//Options of a state
typedef struct s_options
{
	int			index;
	int			state;
	int			t_type;
	int			action;
	int			next_state;
	int			nbr_red;
	struct s_options	*next;
}				t_options;

//State
typedef struct	s_states
{
	int					state;
	struct s_options	*options;
	struct s_states 	*next;
}				t_states;

//Tokens of the analyzer
typedef struct s_token
{
	char			*data;			//data of the token
	int				type;			//type of the token
	struct s_token	*next;			//ptr to the next token

	struct s_token	*left;			//once reduced ptr to the left token
	struct s_token	*right;			//once reduced ptr to the right token
	struct s_token	*middle;		//once reduced ptr to the middle token
}				t_token;

//Steps of the analyzer
typedef struct	s_step
{
	int				step_nbr;			//nbr of the current step
	int				state_nbr;			//nbr of the current state
	struct s_states *state;			//ptr to the current state
	int				option_nbr;			//nbr of the current option of the state
	struct s_token	*tree_stack;		//ptr to the tree/ stack
	struct s_token	*input;			//ptr to the input

	struct s_step	*next;			//ptr to the next step
	struct s_step	*prev;			//ptr to the prev step
}				t_step;


//main struct for the input
typedef struct s_input
{
	char				**token_raw;
	struct s_var_list	*ent_var;
	struct s_states		*parsing_table;
	struct s_var_parsed_table	*parsed_table;
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
	char						**cmd_splited; //primera linea 'echo' segunda linea 'patata' cat -e 
	char						*cmd;
	char						*path; //nombre del comando con la ruta 'users/bin/ls'
	int							fd_in;
	int							fd_out; 
	int							fd_error;
	struct	s_var_parsed_table	*next;
	struct	s_var_parsed_table	*prev;
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

//READ TABLE
void		print_options_for_state(t_states *states_list, int state_number);
void		read_table(t_input **struct_input);

//ANALYZER
void		create_tokens_analyzer(t_input **struct_input);
void		print_token_list(t_token *tokens);


//STEPS
int		start_anaylizer(t_input **struct_input, t_token *input_token);

//STEPS UTILS
int			find_state(t_states *states_list, int state_number, t_states **state);
int			stack_size(t_token *stack);
t_options	*find_option(t_states *state, int token_type);
void		add_step(t_input *struct_input, t_options *options, t_token *tree_stack, t_token *input_token, t_step **c_step);
t_token		*last_node_stack(t_token *stack);
void		ret_to_prev(t_step **c_step);

//ACTIONS
void		apply_action(t_options *options, t_step **c_step, t_token *c_token, int *end_flag);

//READ_TREE
void		walk_tree(t_var_parsed_table **table, t_token *tree);

//BASH SPLIT
static void	ignore_separator(char const *s, int *control, int *i);
static	int	ft_count(char const *s, char c, int *control);
static void	freeall(char **splits);
static int	check_str(char **str, int j);
char	**ft_bash_split(char const *s, char c, int *control);

//TOKENIZATION
int	tokenization(char *input, t_input **struct_input);

//PIPEX_UTILS
void	cmd_handle(t_var_parsed_table **cmd_list);

#endif