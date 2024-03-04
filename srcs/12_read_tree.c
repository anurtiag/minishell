/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_read_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:46:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/02 15:51:21 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Creation of a node
t_var_parsed_table *init_parsed_table(t_var_parsed_table *prev_table)
{
	t_var_parsed_table *node;

	node = (t_var_parsed_table *)malloc(sizeof(t_var_parsed_table));
	if (node)
	{
		node->cmd = NULL;
		node->cmd_splited = NULL;
		node->env = NULL;
		node->fd_error = -1;
		node->fd_in = -1;
		node->fd_out = -1;
		node->next = NULL;
		node->path = NULL;
		return (node);
	}
	else
		return (node);
}

//Recursive function to read the data of the tree
void read_tree(t_token *tree, t_var_parsed_table **table_node, int mode, int *control)
{
	t_var_parsed_table *prueba;

	int first_time = mode;
	static int red_to_flag = 0;
	static int red_from_flag = 0;
	static int fd = -1;

	if (tree == NULL)
		return;
	
	if (mode == 1)
	{
		//reset of the variables
		first_time = 1;
		red_to_flag = 0;
		red_from_flag = 0;
		fd = -1;
		return ;
	}
	// printf("1llegamos aqui?\nel tipo de token es %d\n",tree->type);
	if (tree->type == 100 || tree->type == 101)
	{
		
		if (*control == 1)
		{
			printf("CREAMOS NODO PRINCIPAL\n");
			*table_node = init_parsed_table(*table_node);
			prueba = *table_node;
			// printf("las direcciones de la tabla y su copia son %p y %p\n", *table_node, prueba);
			*control = 0;
		}
		else
		{
			printf("\nCREAMOS NODO SECUNDARIO\n");
			(*table_node)->next = init_parsed_table(*table_node);
			printf("%s\n", (*table_node)->cmd);
			*table_node = (*table_node)->next;
		}
	}
	// printf("el comando es %s\n",(*table_node)->cmd);
	if (tree->type == 2)
		red_from_flag = 1;
		
	if (tree->type == 1)
		//printf("RED TO FOUND\n");
		red_to_flag = 1;
	
	if (tree->type == 108)
		fd = open(tree->data, O_RDONLY);

	// Process left child
	
	if (tree->left != NULL){
		// printf("LLEGO LEFT\n\n");
		read_tree(tree->left, table_node, 0, control);
	}
		
		
	// Process middle child
	if (tree->middle != NULL){
		// printf("LLEGO MIDDLE\n\n");
		read_tree(tree->middle, table_node, 0, control);
	}
		
	// Process right child
	if (tree->right != NULL)
	{
		// printf("LLEGO RIGHT\n\n");
		read_tree(tree->right, table_node, 0, control);
	}
		
	//Is the type of data we are looking for
	// write(1,"patata3\n", 8);
	if ((tree->type == 0 || tree->type == 102 || tree->type == 103 || tree->type == 105) && (tree->left == NULL && tree->middle == NULL && tree->right == NULL))
	{		
		if ((*table_node) == NULL || (*table_node)->cmd == NULL)
		{
			(*table_node)->cmd = strdup(tree->data);
		}
		else
		{
			// printf("la tabla tiene una direccion de %p\nsu data es de %s\nla data del arbol es %s", *table_node, (*table_node)->cmd, tree->data);
						
			size_t x = ft_strlen((*table_node)->cmd) + ft_strlen(tree->data) + 1;
			(*table_node)->cmd = realloc((*table_node)->cmd, x);//parte aqui
			ft_strlcat((*table_node)->cmd, " ", ft_strlen(" "));
			ft_strlcat((*table_node)->cmd, tree->data, ft_strlen(tree->data));
			// printf("1llegamos aqui?\nel arbol tiene una direccion de %p\nel esdiferentetipo de token es %d\ntree data : %s", tree, tree->type, tree->data);
		}
		//printf("cmd: %s\n", (*table_node)->cmd);
	}
	// printf("4llegamos aqui?\n");
	if (red_from_flag == 1)
		(*table_node)->fd_in = fd;
	if (red_to_flag == 1)
		(*table_node)->fd_out = fd;
	// if (*table_node && prueba)
	// 	*table_node = prueba;
}


//HAGO UNA COPIA PORSEACA, ESTA ES LA QUE TENIAS TU 
// void	walk_tree(t_var_parsed_table **parsed_table, t_token *tree)
// {
// 	if (tree->left && tree->left->type == 100)
// 		walk_tree(parsed_table, tree->left);
// 	if (tree->left->type == 100)
// 		read_tree(tree->right, parsed_table, 0);
// 	else
// 		read_tree(tree, parsed_table, 0);
		
// 	//Calling the function again to clear the static variables (mode 1)
// 	read_tree(tree, parsed_table, 1);
// }

void	walk_tree(t_var_parsed_table **parsed_table, t_token *tree)
{
	int control;

	control = 1;
	if (tree->left && tree->left->type == 100)
		walk_tree(parsed_table, tree->left);
	if (tree->left->type == 100)
		read_tree(tree->right, parsed_table, 0, &control);
	else
		read_tree(tree, parsed_table, 0, &control);
		
	//Calling the function again to clear the static variables (mode 1)
	read_tree(tree, parsed_table, 1, &control);
}