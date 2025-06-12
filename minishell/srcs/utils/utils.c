/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:14 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//return 0 if char is not alpha, num or "_"
int	ft_isalnumus(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	else
		return (0);
}

//if not any char not alpha, return (0)
int	check_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0)
			return (0);
		i++;
	}
	if (!str[0])
		return (0);
	return (1);
}

//if not any char not number, return (0)
int	check_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1 && str[i] != '+' && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

//len of str where all char are either alnum or '_'
int	varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalnumus(str[i]) == 1)
		i++;
	return (i);
}

int	count_words(char *str, char c)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	if (str[0] == '\0')
		return (1);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}
