/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analylizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:44:04 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/05 23:00:23 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int analylizer_pipe(t_data *data)
{
    int ft;

    ft = 1;
	t_tokenizer *tokens = data->tokenizer;

    while (tokens)
    {
        if (tokens->content)
        {
            if (ft && tokens->content[0] == '|')
                return 4;
            if (tokens->content[0] == '|' && tokens->content[1] == '|'
            && tokens->content[2] == '|')
                return 1;
            if (tokens->next)
            {
                if (tokens->content[0] == '|' && tokens->next->content[0] == '\0')
                    return 4;
            }
            else
            {
                if (tokens->content[0] == '|')
                    return (4);
            }
        }
        tokens = tokens->next;
        ft = 0;
    }
    return 0;
}


int analylizer_redi(t_data	*data)
{
	t_tokenizer *tokens = data->tokenizer;
    t_tokenizer *current = tokens;
    t_tokenizer *prev = NULL;

    while (current)
    {
        if (current->content)
        {
            if (current->content[0] == '>' && current->content[1] == '>'
            && current->content[2] == '>')
                return 3;
            if ((current->content[0] == '>' || current->content[0] == '<')
            && (current->next == NULL || current->next->content[0] == '\0'
            || (current->next->content[0] == '>'
            || current->next->content[0] == '<')))
                return 2;
        }

        prev = current;
        current = current->next;
    }

    return 0;
}

