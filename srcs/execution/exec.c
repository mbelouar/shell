/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:42:40 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/04 23:13:14 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *get_absolute_path(const char *command_name, t_data *data)
{
	int	i;
    char *path_env;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH", 4) == 0)
		{
			path_env = data->env[i];
			break ;
		}
		i++;
	}
    if (path_env == NULL) {
        fprintf(stderr, "PATH environment variable is not set\n");
        return (NULL);
    }

    char *path_copy = ft_strdup(path_env);
    if (path_copy == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    char *path = path_copy;
    char *token;
    char *result = NULL;

    while ((token = strsep(&path, ":")) != NULL) {
        char absolute_path[MAX_PATH_LENGTH];
        snprintf(absolute_path, sizeof(absolute_path), "%s/%s", token, command_name);

        if (access(absolute_path, X_OK) == 0) {
            result = ft_strdup(absolute_path);
            break ;
        }
    }
	free(path_copy);
    return (result);
}

void	setup_redirections(t_tokenizer *head)
{
	t_tokenizer	*curr;

	curr = head;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == RED_OUT_TRUNC)
		{
			int fd = open(curr->content, O_RDWR | O_CREAT | O_TRUNC , 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (curr->type == RED_OUT_APPEND)
		{
			int fd = open(curr->content, O_RDWR | O_CREAT | O_APPEND , 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (curr->type == RED_IN)
		{
			if (access(curr->content, F_OK) == 0)
			{
				int fd = open(curr->content, O_RDONLY);
				dup2(fd, STDIN_FILENO);
			}
			else
			{
				dprintf(2, "minishell: %s: No such file or directory\n", curr->content);
				exit(EXIT_FAILURE);
			}
		}
		curr = curr->next;
	}
}

void	execute(t_data *data)
{
	if (check_pipe(data->tokenizer) == 0)
		execute_simple_cmd(data);
	else
		execute_compound_command(data);
}
