/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_read_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:46:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/18 12:29:03 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Frees the parsed table node
void free_parsed_table(t_var_parsed_table **table)
{
	t_var_parsed_table *temp;

	while ((*table) != NULL)
	{
		//printf("cleaning parsed table %s\n", (*table)->cmd);
		temp = (*table)->next;
		free_double((*table)->cmd_splited);
		free((*table)->cmd);
		free((*table)->path);
		free(*table);

		(*table) = temp;
	}
}

//Inits and creates node for parsed table
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
		node->pid = 0;
		node->prev = prev_table;
	}
	return (node);
}

//Recursive function to read the data of the tree
void read_tree(t_token *tree, t_var_parsed_table **table_node, int mode)
{
	static int first_time = 1;
	static int red_to_flag = 0;
	static int red_from_flag = 0;
	static int here_doc = 0;
	static int append = 0;
	static int error_flag = 0;
	static int fd = -1;

	if (tree == NULL)
		return;
	
	if (mode == 2)
	{
		first_time = 1;
		free_parsed_table(table_node);
		return;
	}
	
	if (mode == 1)
	{
		//reset of the variables
		red_to_flag = 0;
		red_from_flag = 0;
		error_flag = 0;
		fd = -1;
		return ;
	}
	
	if (tree->type == 100 || tree->type == 101)
	{
		if (first_time == 1)
		{
			//printf("CREAMOS NODO PRINCIPAL\n");
			*table_node = init_parsed_table(*table_node);
			first_time = 0;
		}
		else
		{
			//printf("\nCREAMOS NODO SECUNDARIO\n");
			(*table_node)->next = init_parsed_table(*table_node);
			//printf("NEXT NODE: %p\n", (*table_node)->next);
			*table_node = (*table_node)->next;
		}
	}
	
	if (tree->type == 2)
		red_from_flag = 1;

	if (tree->type == 3)
		here_doc = 1;
	if (tree->type == 4)
		append = 1;
	
	if (tree->type == 1)
	{
		red_to_flag = 1;
		if (strcmp(tree->data, "2>") == 0)
			error_flag = 1;
	}
	
	if (tree->type == 108)
		fd = open(tree->data, O_RDWR);
	if (tree->type == 106)//infiles
	{
		printf("el arbol tiene %s\n", tree->data);
		if (tree->left)
			printf("a la izquierda hay %s\n", tree->left->data);
		if (tree->middle)
			printf("en medio hay %s\n", tree->middle->data);
		if (tree->right)
			printf("a la derecha hay %s\n", tree->right->data);
	}
	
	if (tree->type == 106)//aqui 
	{
		if (ft_strncmp(tree->left->data, ">>", 2) == 0)
		{
			// printf("Entramos a abrir en modo append\n");
			fd = open(tree->right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (ft_strncmp(tree->left->data, ">", 1) == 0)
		{
			// printf("entramos a modo output normal\n");
			fd = open(tree->right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (ft_strncmp(tree->left->data, "<<", 2) == 0)
		{
			// printf("Entramos a abrir en modo here doc\n");
			fd = ft_here_doc(tree->right->data, 0);
		}
		else if (ft_strncmp(tree->left->data, "<", 1) == 0)
		{
			// printf("entramos a modo input normal\n");
			fd = open(tree->right->data, O_RDONLY);
		}
		if (fd < 0)
			printf("Algo se ha hecho mal abriendo los archivos\n");
	}
	
	// Process left child
	if (tree->left != NULL)
		read_tree(tree->left, table_node, 0);
	
	// Process middle child
	if (tree->middle != NULL)
		read_tree(tree->middle, table_node, 0);
	
	// Process right child
	if (tree->right != NULL)
		read_tree(tree->right, table_node, 0);
	
	//Is the type of data we are looking for
	if (((tree->type == 0 || tree->type == 102 || tree->type == 103 || tree->type == 105 || tree->type == 100 || tree->type == 101) && (tree->left == NULL && tree->middle == NULL && tree->right == NULL)))
	{		
		if ((*table_node)->cmd == NULL)
			(*table_node)->cmd = strdup(tree->data);
		else
		{
			(*table_node)->cmd = realloc((*table_node)->cmd, ft_strlen((*table_node)->cmd) + ft_strlen(tree->data) + 2);
			ft_strlcat((*table_node)->cmd, " ", (ft_strlen((*table_node)->cmd) + ft_strlen(" ") + 1));
			ft_strlcat((*table_node)->cmd, tree->data, (ft_strlen((*table_node)->cmd) + ft_strlen(tree->data) + 1));
		}
	}
	if (red_from_flag == 1 || here_doc == 1)
	{
		// printf("entramos a guardar el input\n");
		(*table_node)->fd_in = fd;
		// printf("el fd del input es de %d con la direccion de memoria %p\n", (*table_node)->fd_in, (*table_node));
	}
	
	if (red_to_flag == 1 || append == 1)
	{
		// printf("entramos a guardar el output\n");
		if (error_flag == 1)
			(*table_node)->fd_error = fd;
		else
			(*table_node)->fd_out = fd;
	}
}

//Looks for sub_trees in the main tree
void	walk_tree(t_var_parsed_table **parsed_table, t_token *tree)
{	
	if (tree->left && tree->left->type == 100)
		walk_tree(parsed_table, tree->left);

	if (tree->left && tree->left->type == 100)
		read_tree(tree->right, parsed_table, 0);
	else
		read_tree(tree, parsed_table, 0);
	
	//Calling the function again to clear the static variables (mode 1)
	read_tree(tree, parsed_table, 1);
}
