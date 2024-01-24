/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:59:12 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/24 19:19:00 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void    ft_fill_var(char *token, int equal_pos, int start, int end)
{
    char    *var_name;
    char    *var_content;

    var_name = strndup(token + start, equal_pos - start);
    var_content = strndup(token + equal_pos + 2, (end - 1)- (equal_pos + 2));
    printf("name: %s, content: %s\n", var_name, var_content);

    //buscamos si hay alguna variable ya creada

    // si existe la sobreescribimos

    // si no existe creamos nuevo nodo y lo anadimos a la lista
}

int     ft_look_4_equal(char const *token, int start, int end)
{
    int i;
   
    i = start;
    while (i < end)
    {
        if (((((token[i - 1] >= 'a') && (token[i - 1] <= 'z')) || ((token[i - 1] >= 'A') && (token[i - 1] <= 'Z'))) && (token[i] == '=')) && (((token[i + 1] == '\'') || (token[i + 1] == '\"'))))
        {
            printf("variable de entorno encontrada\n");
            ft_fill_var((char *)token, i, start, end);
            return (0);
        }
        i++;
    }
    return (1);
}
