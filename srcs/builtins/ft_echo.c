/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:29 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/01 08:40:42 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_remove_quotes(char *s)
{
	char *res;
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != 34 && s[i] != 39)
			len++;
		i++;
	}
	res = ft_calloc(len, sizeof(char));
	i = 0;
	int j = 0;
	while (s[i])
	{
	    if (s[i] != 34 && s[i] != 39)
	    {
	        res[j] = s[i];
	        j++;
	    }
	    i++;
	}
	return (res);
}

void	ft_echo(char **args)
{
	char	*arg;
	int		i;
	int		n;

	i = 1;
	n = 0;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		n++;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
}




/*


setup pipes
{
		if (i == 0)
		{
			awal command
			read from input
			write to p1[1];
			close unused;
		}
		if (i % 2)
		{
			read from p1[0]
			write to p2[1];
			close unused;
		}
		if (i % 2 == 0)
		{
			read from p2[0]
			write to p1[1];
			close unused;
		}
		if (i == count)
		{
			akhir command
			if (i % 2 == 0)
				read from p2[0]
				write to output
				close unused;
			if (i % 2)
				read from p1[0]
				write to output
				close unused;
		}
}

setup pipe for next child
{
	if(i%2 == 0)
	{
		close(p2[0]);
		close(p2[1]);
		pipe(p2)
	}
	else{
		close(p1[0]);
		close(p1[1]);
		pipe(p1)
	}
}


	}
	int cout = cmd_cout;
	pipe p1 and p2;
	int i = 0;
	while (i <= cout)
	{
		int pid = fork();
		if (pid == 0)
		{
			1: setp pipes for child (p1, p2, i, count)
			2: setup redir
			3: execute cmd
			{

			}
		}
		setup pipe for next child(p1, p2, i)
		i++;
	}
	close p1 and p2;
	wait for childs;

*/
