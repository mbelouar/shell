/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 04:31:55 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/24 18:40:17 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to print the name of an enum value
void printEnumName(enum e_type value)
{
	// An array of strings to map enum values to their names
	const char *e_type_names[] = {
		"CMD",
		"BUILTIN",
		"PIPE",
		"RED_OUT_TRUNC",
		"RED_OUT_APPEND",
		"RED_IN",
		"HEREDOC"
	};

	if (value == CMD)
		printf("Type: %s\n", e_type_names[0]);
	if (value == BUILTIN)
		printf("Type: %s\n", e_type_names[1]);
	if (value == PIPE)
		printf("Type: %s\n", e_type_names[2]);
	if (value == RED_OUT_TRUNC)
		printf("Type: %s\n", e_type_names[3]);
	if (value == RED_OUT_APPEND)
		printf("Type: %s\n", e_type_names[4]);
	if (value == RED_IN)
		printf("Type: %s\n", e_type_names[5]);
	if (value == HEREDOC)
		printf("Type: %s\n", e_type_names[6]);
}

void	free_token_list(t_tokenizer **lst)
{
	t_tokenizer	*p;

	if (!lst)
		return ;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		free(p->content);
		free(p);
	}
	*lst = NULL;
}

void	free_double_pointer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void printList(t_tokenizer *head)
{
	t_tokenizer *current = head;
	while (current != NULL)
	{
		printf("Content: %s\t", current->content);
		printEnumName(current->type);
		current = current->next;
	}
}
