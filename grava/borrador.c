#include "libs/Libft/libft.h"
#include "libs/GNL/get_next_line.h"
#include <fcntl.h>

#define WORD 0
#define RED_TO 1
#define RED_FROM 2
#define DLESS 3
#define DGREAT 4
#define PIPE 5
#define PIPE_SEQUENCE 100
#define SIMPLE_CMD 101
#define CMD_NAME 102
#define CMD_WORD 103
#define CMD_PREFIX 104
#define CMD_SUFFIX 105
#define IO_REDIRECT 106
#define IO_FILE 107
#define FILENAME 108
#define IO_HERE 109
#define HERE_END 110

typedef struct s_gram_rules
{
	int			state;
	int			token_type;
	int			action;
	int			next_state;
	int			nbr_red;//number of reduced tokens
	struct s_gram_rules	*next;
}				t_gram_rules;


typedef struct s_states
{
	int						state;
	struct s_states			*next;
	struct s_state_options	*state_options;
}				t_states;

typedef struct s_state_options
{
	int			token_type;
	int			action;
	int			next_state;
	int			nbr_red;//number of reduced tokens
	struct s_state_options	*next;
}				t_state_options;

typedef struct s_token
{
	char	*data;
	int		type;
	struct s_token	*next;
}				t_token;

void	freelist(t_gram_rules *node)
{
	t_gram_rules *tmp;

	while(node)
	{
		tmp = node;
		node= node->next;
		free(tmp);
	}
}

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
int	make_g_list(char *line, t_gram_rules *node)
{
	char	**matrix;
	t_gram_rules *tmp;

	matrix = NULL;
	tmp = (t_gram_rules *)malloc(sizeof(t_gram_rules));
	if(!node)
		return(1);
	matrix = ft_split(line, '\t');
	if (!matrix)
		return (1);
	node->state = ft_atoi(matrix[0]);
	node->token_type = ft_atoi(matrix[1]);
	node->action = ft_atoi(matrix[2]);
	node->next_state = ft_atoi(matrix[3]);
	node->nbr_red = ft_atoi(matrix[4]);
	node->next = tmp;
	freematrix(matrix);
	return (0);
}

int	charge_table(int fd, t_states *node)
{
	int		i;
	char	*line;

	i = -1;
	while(++i < 100)
	{
		line = get_next_line(fd);
		if (!line)
			return(free(line), 1);
		else
		{
			make_g_list(line, node);
			node = node->next;
			free(line);
		}
	}
	node->next = NULL;
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

int	shift_n_reduce(t_token *token, t_gram_rules *node)
{
	int new_s;

	while(token->type != node->token_type)//con esto ya tendria el primer tipo de token
		node = node->next;
	new_s = node->next_state;
	return (0);
}

int lexer(char **input)
{
	int 			fd;
	t_states		*g_node;
	t_token			*t_node;

	fd = open("parsing_table", O_RDONLY);
	if (fd < 0)
		return (1);
	g_node = (t_states *)malloc(sizeof(t_states));
	if(!g_node)
		return (1);
	t_node = (t_token *)malloc(sizeof(t_token));
	if(!t_node)
		return (1);
	charge_table(fd, g_node);
	tokenizer(input, t_node);
	shift_n_reduce(t_node, g_node);
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