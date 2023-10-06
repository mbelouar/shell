/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:51:59 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/04 18:43:35 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_simple_cmd(t_data *data)
{
	pid_t		pid;
	t_tokenizer	*tmp;
	char		**cmd;
	char		*cmd_name;

	tmp = data->tokenizer;
	cmd_name = NULL;
	while (tmp)
	{
		if (tmp->type == BUILTIN)
		{
			cmd = ft_split(tmp->content, ' ');
			int save_fd[2];
			save_fd[0] = dup(0);
			save_fd[1] = dup(1);
			setup_redirections(tmp);
			exec_builtin(cmd, data);
			dup2(save_fd[0], 0);
			dup2(save_fd[1], 1);
			close(save_fd[0]);
			close(save_fd[1]);
			free_double_pointer(cmd);
			return ;
		}
		tmp = tmp->next;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("error in fork:");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		setup_redirections(data->tokenizer);
		exec_cmd(data, cmd, cmd_name);
	}
	else
		waitpid(pid, 0, 0);
}
