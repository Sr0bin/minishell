/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:42:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/10 13:52:14 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	count_c(char const *s, char c)
{
	int	count;
	int	i;

	if (!s || !s[0])
		return (0);
	count = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
		}
		else
		{
			i++;
		}
	}
	if (s[i - 1] != c && i > 0)
		count++;
	return (count);
}

char	*split_word(char const *s, char c)
{
	char	*split_word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != c && s[i])
		i++;
	split_word = malloc(sizeof(char) * (i + 1));
	if (split_word == NULL)
		return (NULL);
	while (j < i)
	{
		split_word[j] = s[j];
		j++;
	}
	split_word[j] = '\0';
	return (split_word);
}

void	free_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**big_array;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	big_array = malloc(sizeof(char *) * (count_c(s, c) + 1));
	if (!big_array)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			big_array[i] = split_word(s, c);
			if (!big_array[i])
				return (free_array(big_array, i), NULL);
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	big_array[i] = NULL;
	return (big_array);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (0);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	if (!s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = malloc (sizeof(char) * i + 1);
	i = 0;
	if (dest == NULL)
		return (0);
	else
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
}