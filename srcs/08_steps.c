/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:30:01 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/18 11:54:14 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void print_step_list(t_step *step)
{
	printf("------------START------------\n");
	while (step != NULL)
	{

		printf("Step address: %p\n", (void *)step);
		printf("Step number: %d\n", step->step_nbr);
		printf("State number: %d\n", step->state_nbr);
		printf("Option number: %d\n", step->option_nbr);
		printf("Next step address: %p\n", (void *)step->next);
		printf("Previous step address: %p\n", (void *)step->prev);
		if (step->next)
			printf("-------------------------\n");
		step = step->next;
	}
	printf("-----------END--------------\n\n");
}

void remove_quotes_aux(char **cmd_ptr)
{
	int					start;
	int					end;
	char				*before;
	char				*mid;
	char				*after;
	char				*tmp;

	tmp = NULL;
	before = NULL;
	mid = NULL;
	after = NULL;
	start = 0;
	end = ft_strlen(*cmd_ptr);
	while (start <= end)
	{
		if((*cmd_ptr)[start] == '\'' || (*cmd_ptr)[start] == '\"')
			break;
		start++;
	}
	while (end >= 0)
	{
		if((*cmd_ptr)[end] == '\'' || (*cmd_ptr)[end] == '\"')
			break;
		end--;
	}

	before = ft_substr(*cmd_ptr, 0, start);
	mid = ft_substr(*cmd_ptr, start + 1, end - start - 1);
	after = ft_substr(*cmd_ptr, end + 1, ft_strlen(*cmd_ptr) - end);

	// printf("%s\n", *cmd_ptr);
	// printf("------------------\n");
	// printf("start %i\n", start);
	// printf("end %i\n", end);
	// printf("b %s\n", before);
	// printf("m %s\n", mid);
	// printf("a %s\n", after);

	
	if (end == -1 || (end == 0 && start == 0))
	{
		free(before);
		free(mid);
		free(after);
		return;
	}
	
	free(*cmd_ptr);
	tmp = ft_strjoin(before, mid);
	*cmd_ptr = ft_strjoin(tmp, after);
	free(tmp);
	free(before);
	free(mid);
	free(after);
}

//Removes the quotes
void remove_quotes(t_var_parsed_table **head)
{
	t_var_parsed_table	*first;
	int					i;

	first = *head;
	while ((*head) != NULL)
	{
		i = 0;
		if ((*head)->cmd_splited != NULL)
		{
			while ((*head)->cmd_splited[i] != NULL)
			{
				//printf("%i %s\n",i, (*head)->cmd_splited[i]);
				remove_quotes_aux(&((*head)->cmd_splited[i]));
				i++;
			}
		}
		(*head) = (*head)->next;
	}
	*head = first;
}

//Prints the parsed table content
void print_cmd_contents(t_var_parsed_table **head)
{
	t_var_parsed_table *current = *head;
	int i;
	if (current == NULL)
		printf("NO TENGO NADA\n");
	while (current != NULL)
	{
		if (current->cmd != NULL)
		{
			printf("--------------------\n");
			if (current->cmd_splited != NULL)
			{
				printf("cmd_splited: ");
				char **cmd_ptr = current->cmd_splited;
				i = 0;
				while (*cmd_ptr != NULL)
				{
					printf("%s %i", *cmd_ptr, i);
					cmd_ptr++;
					i++;
				}
				printf("\n");
			}
			printf("path: %s\n", current->path);
			printf("std in: %i\n", current->fd_in);
			printf("std out: %i\n", current->fd_out);
			printf("std error: %i\n", current->fd_error);
			printf("--------------------\n\n");
		}
		current = current->next;
	}
}

//Configs the parsed table (fd OUT fd IN)
void config_parsed_table(t_var_parsed_table **current)
{
	int i;
	int max;
	int		control[2];
	t_var_parsed_table *first_node;

	i = 0;
	max = 0;
	control[0] = TRUE;
	control[1] = TRUE;
	// Avanzar al primer nodo de la lista
	while ((*current)->prev != NULL)
	{
		max++;
		(*current) = (*current)->prev;
	}
	first_node = *current;
	//Realizar acciones en cada nodo de la lista
	while (first_node != NULL)
	{
		if (i == 0 && (first_node->fd_in == -1))
			first_node->fd_in = 0;
		
		if (first_node->cmd != NULL)
			first_node->cmd_splited = ft_bash_split(first_node->cmd, SPACE_M, control);

		if (i == max && first_node->fd_out == -1)
			first_node->fd_out = 1;

		first_node = first_node->next;
		i++;
	}
}

// Function to display the structure tree
void display_structure_tree(t_token *root, int depth)
{
	if (root == NULL)
		return;

	// Print right child
	display_structure_tree(root->right, depth + 1);

	// Print current node
	for (int i = 0; i < depth; i++)
		printf("    ");
	printf("|-- data: %s, type: %d\n", root->data, root->type);

	// Print middle child
	display_structure_tree(root->middle, depth + 1);
	
	// Print left child
	display_structure_tree(root->left, depth + 1);
}

//Inits the first step of the analizer
t_step	*init_first_step(t_input **struct_input, t_token *input_token)
{
	t_step		*first_step;
	t_states	*state;

	first_step = NULL;
	first_step = (t_step *)malloc(sizeof(t_step));
	if (first_step == NULL)
		return (first_step);
	// state = (t_states *)malloc(sizeof(t_states));
	// if (state == NULL)
	// 	return (free(first_step), first_step);
	first_step->step_nbr = 0;
	first_step->state_nbr = 0;
	if (find_state((*struct_input)->parsing_table, 0, &state) == FALSE)
	{
		//free(state);
		free(first_step);
		return (first_step);
	}
	first_step->state = state;
	first_step->option_nbr = 0;
	first_step->tree_stack = NULL;
	first_step->input = input_token;
	first_step->next = NULL;
	first_step->prev = NULL;
	return (first_step);
}

//Main function of the analizer
int	start_anaylizer(t_input **struct_input, t_token *input_token)
{
	t_step		*step;
	t_step		*c_step;
	t_token		*c_token;
	t_options	*def_option;
	t_options	*available_option;
	int			end_flag;
	int			end = 0;

	end_flag = FALSE;
	c_step = init_first_step(struct_input, input_token);
	step = c_step;
	if (step == NULL)
		return (printf("ERROR INIT THE FIRST STEP\n"), FALSE);

	//cogemos el primer nodo de input como nuestro token a evaluar
	c_token = step->input;
	
	while (end_flag == FALSE)
	{
		printf("\n\033[0;33m-----INPUT:---%i---\033[0m\n", end);
		print_token_list(c_step->input);
		printf("-----STACK:-----\n");
		print_token_list(c_step->tree_stack);
		printf("\n");
		//print_step_list(step);

		//conseguimos la opcion default siempre que la tengamos y la opcion disponible depende de nuestro c_token
		def_option = find_option(c_step->state, -1);
		available_option = find_option(c_step->state, c_token->type);
		printf("\033[0;32mevaluate node ->%s<- type ->%i<- \033[0m\n", c_token->data, c_token->type);
		
		if (def_option && (def_option->next_state == c_token->type))
		{
			//Volvemos a un estado anterior en el que el reduce del default es ya nuestro token
			//apply_action(def_option, &c_step, c_token, &end_flag);
			printf("\n\033[0;35mRETURNING TO %i WITH DEFAULT\n\033[0m\n", c_step->prev->state_nbr);
			ret_to_prev(&c_step);
		}
		else if ((available_option == NULL) && (def_option == NULL) && (c_token->type >= 100) && (c_step->state_nbr != 0))
		{
			//El estado no tiene default ni avail option y tenemos un token compuesto
			printf("\n\033[0;35mRETURNING TO %i\n\033[0m\n", c_step->prev->state_nbr);
			ret_to_prev(&c_step);
		}
		else if ((available_option != NULL))
		{
			//El estado tiene una opcion disponible
			//aplicamos accion
			apply_action(available_option, &c_step, c_token, &end_flag);
			add_step(*struct_input, available_option, c_step->tree_stack, c_step->input, &c_step);
			
			//(si vamos a un estado de una opcion que es token simple nuestro token a evaluar es el ultimo de stack, sino el primero del input)
			if (c_step->input && (c_token->type >= 100 || c_token->type == 1 || c_token->type == 2 || c_token->type == 3 || c_token->type == 4 || c_token->type == 5))
				c_token = c_step->input;
		}
		else if ((available_option == NULL) && def_option)
		{
			//si no coincide con ningun tipo de token, y tenemos default, hacemos default (volvemos al paso anterior)
			//aplicamos accion
			
			// printf("state nbr %i, input type %i\n", c_step->state_nbr, c_step->input->type);
				
			apply_action(def_option, &c_step, c_token, &end_flag);

			if (last_node_stack(c_step->tree_stack)->type >= 100)
				c_token = last_node_stack(c_step->tree_stack);

			if ((c_step->state_nbr == 22 && c_token->type == 105 && c_step->input->type == 1) || c_step->state_nbr == 22 && c_token->type == 105)
				c_token = c_step->input;
		}
		else if ((available_option == NULL) && (def_option == NULL))
			break;
		end++;
	}

	if ((stack_size(c_step->tree_stack) != 2) || (last_node_stack(c_step->tree_stack)->type != -2))
	{
		return (free_steps(step), printf("\033[0;31mKO\033[0m\n"), FALSE);
	}
	else
	{
		printf("\033[0;32mOK\033[0m\n");
		//display_structure_tree(c_step->tree_stack, 0);
		//print_token_list(c_step->tree_stack);
		
		walk_tree(&(*struct_input)->parsed_table, c_step->tree_stack);
		config_parsed_table(&(*struct_input)->parsed_table);
		//print_cmd_contents(&(*struct_input)->parsed_table);

		expand_var_ent(&(*struct_input)->parsed_table, struct_input);
		remove_quotes(&(*struct_input)->parsed_table);
		cmd_handle(&(*struct_input)->parsed_table, struct_input);
		pipex(struct_input);
		read_tree(c_step->tree_stack, &(*struct_input)->parsed_table, 2);
		return (free_steps(step), TRUE);
	}
	return (FALSE);
}
