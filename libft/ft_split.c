/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:18:25 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/29 23:55:04 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_count_words(char const *s)
{
	int	i;
	int	cnt;
	int quote;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i])
			cnt++;
		while(s[i] && s[i] != ' ')
		{
			quote = 0;
			if (s[i] == 34 || s[i] == 39)
				quote = s[i++];
			while (quote && s[i] != quote)
				i++;
			++i;
		}
	}
	return (cnt);
}

void	fill_s(char **dest, char const *s, char c, int words_nbr)
{
	int	i;
	int	j;
	int	count_char;
	int quote;

	(void)c;
	i = 0;
	j = 0;
	while (j < words_nbr)
	{
		count_char = 0;
		while (s[i] && s[i] == ' ')
			i++;
		while (s[i] && s[i] != ' ')
		{
			quote = 0;
			if (s[i] == 34 || s[i] == 39)
			{
				quote = s[i++];
				count_char++;
			}
			while (quote && s[i] != quote)
			{
				i++;
				count_char++;
			}
			count_char++;
			i++;
		}
		dest[j] = ft_substr(s, (i - count_char), count_char);
		j++;
	}
	dest[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		count_word;

	if (!s)
		return (NULL);
	count_word = ft_count_words(s);
	dest = malloc(sizeof(char *) * (count_word + 1));
	if (!dest)
		return (NULL);
	fill_s(dest, s, c, count_word);
	return (dest);
}
