/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:53:19 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/27 09:55:27 by emimenza         ###   ########.fr       */
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

//Prints the parsed table content
void print_cmd_contents(t_var_parsed_table **head)
{
	t_var_parsed_table *current = *head;
	int i;
	if (current == NULL)
		printf("NO TENGO NADA\n");
	while (current != NULL)
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
			printf ("cmd : %s\n", current->cmd);
			if (current->path)
				printf("path: %s\n", current->path);
			printf("std in: %i\n", current->fd_in);
			printf("std out: %i\n", current->fd_out);
			printf("std error: %i\n", current->fd_error);
			printf("next dir %p\n", current->next);
			printf("--------------------\n\n");
		current = current->next;
	}
}

// Function to display the structure tree
void display_structure_tree(t_token *root, int depth)
{
	if (root == NULL)
		return;

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
