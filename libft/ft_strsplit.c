/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 15:55:35 by jpfeffer          #+#    #+#             */
/*   Updated: 2016/09/30 21:53:30 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *str, char delim)
{
	int i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == delim)
		{
			i++;
			if (str[i] == '\0')
				return (words);
		}
		words++;
		while (str[i] != delim)
		{
			i++;
			if (str[i] == '\0')
				return (words);
		}
	}
	return (words);
}

static int	ft_wordlength(char const *str, char delim, int i)
{
	int	length;

	length = 0;
	while (str[i] != delim && str[i])
	{
		length++;
		i++;
	}
	return (length);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	i = 0;
	if (!(str = (char**)ft_memalloc(sizeof(char*) * (ft_wordcount(s, c) + 1))))
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!(str[j] = ft_strnew(sizeof(char) * ft_wordlength(s, c, i))))
			return (0);
		k = 0;
		while (s[i] != c && s[i])
			str[j][k++] = s[i++];
		j++;
	}
	str[ft_wordcount(s, c)] = 0;
	return (str);
}
