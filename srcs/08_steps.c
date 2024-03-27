/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:30:01 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/27 11:14:15 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Processes the parsed table to the pipex
void	process_p_table(t_input **s_input, t_step *c_step, t_step *step)
{
	walk_tree(&(*s_input)->parsed_table, c_step->tree_stack);
	config_parsed_table(&(*s_input)->parsed_table);
	expand_var_ent(&(*s_input)->parsed_table, s_input);
	remove_quotes(&(*s_input)->parsed_table);
	if (cmd_handle(&(*s_input)->parsed_table, s_input, step) == TRUE)
		pipex(s_input, step);
	read_tree(c_step->tree_stack, &(*s_input)->parsed_table, 2);
}

//Avail opt of the parsed table
void	avail_opt(t_input **s_input, t_step **c_step, t_token **c_token, int *end_flag, t_options *a_opt)
{
	apply_action(a_opt, c_step, *c_token, end_flag);
	add_step(*s_input, a_opt, (*c_step)->tree_stack, (*c_step)->input, c_step);
	if ((*c_step)->input && ((*c_token)->type >= 100 || \
	((*c_token)->type >= 1 && (*c_token)->type <= 5)))
		*c_token = (*c_step)->input;
}

//Null opt of the parsed table
void	null_opt(t_step **c_step, t_token **c_token, int *end, t_options *d_opt)
{
	apply_action(d_opt, c_step, *c_token, end);
	if (last_node_stack((*c_step)->tree_stack)->type >= 100)
		*c_token = last_node_stack((*c_step)->tree_stack);
	if (((*c_step)->state_nbr == 22 && (*c_token)->type == 105 && \
	(*c_step)->input->type == 1) || ((*c_step)->state_nbr == 22 && \
	(*c_token)->type == 105))
		*c_token = (*c_step)->input;
}

//Aux function of the analizer
int	analyzer_aux(t_input **s_input, t_step *step, t_step *c_step)
{
	t_token		*c_token;
	int			end_flag;
	t_options	*d_opt;
	t_options	*a_opt;

	end_flag = FALSE;
	c_token = step->input;
	while (end_flag == FALSE)
	{
		d_opt = find_option(c_step->state, -1);
		a_opt = find_option(c_step->state, c_token->type);
		if ((d_opt && (d_opt->next_state == c_token->type)) || ((a_opt == NULL) \
		&& \
		(d_opt == NULL) && (c_token->type >= 100) && (c_step->state_nbr != 0)))
			ret_to_prev(&c_step);
		else if (a_opt != NULL)
			avail_opt(s_input, &c_step, &c_token, &end_flag, a_opt);
		else if (a_opt == NULL && d_opt != NULL)
			null_opt(&c_step, &c_token, &end_flag, d_opt);
		else if (a_opt == NULL && d_opt == NULL)
			break ;
	}
}

//Main function of the analizer
int	start_anaylizer(t_input **s_input, t_token *input_token)
{
	t_step		*step;
	t_step		*c_step;

	c_step = init_first_step(s_input, input_token);
	step = c_step;
	if (step == NULL)
		return (print_error(6, NULL, NULL), FALSE);
	analyzer_aux(s_input, step, c_step);
	if (c_step->tree_stack && (stack_size(c_step->tree_stack) == 2) && \
	(last_node_stack(c_step->tree_stack)->type == -2))
		return (process_p_table(s_input, c_step, step), free_steps(step), TRUE);
	else
		return (free_steps(c_step), print_error(7, NULL, s_input), FALSE);
	return (FALSE);
}
