/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_read_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:33:58 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/27 10:40:02 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Función para imprimir las opciones de un estado dado
void print_options_for_state(t_states *states_list, int state_number)
{
    t_states *current_state = states_list;

    printf("current state: %i\n", current_state->state);
    // Busca el estado con el número especificado
    while (current_state != NULL && current_state->state != state_number) {
        current_state = current_state->next;
    }

    // Si se encontró el estado
    if (current_state != NULL)
    {
        printf("Opciones para el estado %d:\n", current_state->state);
        t_options *current_option = current_state->options;
        while (current_option != NULL)
        {
            printf("Index: %d, State: %d, Type: %d, Action: %d, Next State: %d, Red: %d\n",
                   current_option->index, current_option->state, current_option->t_type,
                   current_option->action, current_option->next_state, current_option->nbr_red);
            current_option = current_option->next;
        }
    }
    else
        printf("No se encontró el estado %d\n", state_number);
}

// Función para crear un nuevo nodo de opción
static t_options *create_option_node(int index, int state, int t_type, int action, int next_state, int nbr_red)
{
    t_options *new_node;

    new_node = (t_options *)malloc(sizeof(t_options));
    if (new_node == NULL)
        return (new_node);
    new_node->index = index;
    new_node->state = state;
    new_node->t_type = t_type;
    new_node->action = action;
    new_node->next_state = next_state;
    new_node->nbr_red = nbr_red;
    new_node->next = NULL;
    return (new_node);
}

// Función para crear un nuevo nodo de estado
static t_states *create_state_node(int state)
{
    t_states *new_node;

    new_node = (t_states *)malloc(sizeof(t_states));
    if (new_node == NULL)
        return (new_node);
    new_node->state = state;
    new_node->options = NULL;
    new_node->next = NULL;
    return new_node;
}

// Función para agregar una opción a la lista de opciones de un estado
static void add_option_to_state(t_states *state, t_options *option)
{
    t_options   *current;

    if (state->options == NULL)
        state->options = option;
    else
    {
        current = state->options;
        while (current->next != NULL)
            current = current->next;
        current->next = option;
    }
}

void read_table(t_input **struct_input)
{
    int         fd;
    char        *line;
    t_states    *states_list;
    t_states    *current_state;
    t_options   *new_option ;

    int         option_index ;
    char        **tokens;
    int         state;
    int         t_type;
    int         action;
    int         next_state;
    int         nbr_red;
    

    states_list = NULL;
    current_state = NULL;
    option_index = 0;
    fd = open("parsing_table", O_RDONLY);
    if (fd == -1)
        return((void)printf("Error reading the file(parsing table)\n"));

    line = get_next_line(fd);
    while (line != NULL)
    {
        tokens = ft_split(line, '\t');

        // Convierte cada token en un entero
        state = ft_atoi(tokens[0]);
        t_type = ft_atoi(tokens[1]);
        action = ft_atoi(tokens[2]);
        next_state = ft_atoi(tokens[3]);
        nbr_red = ft_atoi(tokens[4]);

        // Crea un nuevo nodo de estado si es necesario
        if (current_state == NULL || current_state->state != state)
        {
            current_state = create_state_node(state);
            current_state->next = states_list;
            states_list = current_state;
            option_index = 0;
        }

        // Crea un nuevo nodo de opción
        new_option = create_option_node(option_index++, state, t_type, action, next_state, nbr_red);

        // Agrega la opción al estado actual
        add_option_to_state(current_state, new_option);

        // Liberar la memoria de la línea leída por get_next_line
        free(line);
        free(tokens);
        line = get_next_line(fd);
    }
    close(fd);
    (*struct_input)->parsing_table = states_list;
    
    return;
}
