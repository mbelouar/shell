/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:22:02 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/05 22:47:34 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to create a new node
t_tokenizer *new_node(char *content, t_type type)
{
	t_tokenizer *newNode = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (newNode == NULL)
		exit(EXIT_FAILURE);

	newNode->content = ft_strdup(content);
	newNode->type = type;
	newNode->next = NULL;

	return (newNode);
}

// Function to add a node to the back of the linked list
void ft_create_node(t_tokenizer **head, char *content, t_type type)
{
	t_tokenizer *newNode = new_node(content, type);

	if (*head == NULL)
		*head = newNode;
	else
	{
		// Traverse the list to find the last node
		t_tokenizer *current = *head;
		while (current->next != NULL)
			current = current->next;
		// Add the new node to the back
		current->next = newNode;
	}
}

void ft_redirection(t_list *curr_node, t_data *data)
{
	t_type	type;
	char	*content;

	if (curr_node->content[0] == '>' && curr_node->content[1] == '>')
	{
		type = RED_OUT_APPEND;
		content = curr_node->next->content;
	}
	else if (curr_node->content[0] == '>')
	{
		type = RED_OUT_TRUNC;
		content = curr_node->next->content;
	}
	else if (curr_node->content[0] == '<' && curr_node->content[1] == '<')
	{
		type = HEREDOC;
		content = curr_node->next->content;
	}
	else if (curr_node->content[0] == '<')
	{
		type = RED_IN;
		content = curr_node->next->content;
	}
	ft_create_node(&data->tokenizer, content, type);
}

int	builtin_check(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	return (0);
}

void tokenizer(t_data *data)
{
	t_list		*curr;
	t_type		type;
	char		*content;

	curr = data->lst;
	while (curr)
	{
		if (curr->content[0] == '<' || curr->content[0] == '>')
		{
			ft_redirection(curr, data);
			curr = curr->next;
		}
		else if (curr->content[0] == '|')
			ft_create_node(&data->tokenizer, ft_strdup("|"), PIPE);
		else
		{
			content = ft_strdup("");
			while (curr)
			{
				content = ft_strjoin(content, curr->content);
				content = ft_strjoin(content, " ");
				if (curr->next && (curr->next->content[0] == '|' || curr->next->content[0] == '<' || curr->next->content[0] == '>'))
					break ;
				curr = curr->next;
			}
			content = ft_strtrim(content, " ");
			char	**tmp = ft_split(content, ' ');
			if (builtin_check(tmp[0]))
				type = BUILTIN;
			else
				type = CMD;
			free_double_pointer(tmp);
			ft_create_node(&data->tokenizer, content, type);
		}
		if (curr == NULL)
			break ;
		curr = curr->next;
	}
}
