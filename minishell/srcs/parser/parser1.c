/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getenv(char *var, t_mini *mini)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	len = ft_strlen(var);
	while (mini->e[i])
	{
		if (ft_strnstr(mini->e[i], var, len) != NULL)
		{
			path = mini->e[i] + len + 1;
			return (path);
		}
		i++;
	}
	return ("");
}

char	*replace_str(char *var, t_mini *mini, int len)
{
	int		i;
	int		j;
	char	*tmp;
	char	*exp_var;
	char	*remainder;

	i = ft_strlen(var);
	j = i - len;
	remainder = (char *)malloc(sizeof(char) * (j + 1));
	i = -1;
	while (++i < j)
		remainder[i] = var[len + i];
	remainder[j] = '\0';
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(tmp, var, len + 1);
	exp_var = ft_getenv(tmp, mini);
	free(tmp);
	tmp = ft_strjoin("", exp_var);
	free(var);
	var = ft_strjoin(tmp, remainder);
	free(remainder);
	free(tmp);
	return (var);
}

void	expand_var_f1(char **str, int exitnum, int *i)
{
	char	*var;
	char	*remainder;
	char	*tmp;
	char	*ptr;

	if ((*str)[*i] == '$' && (*str)[*i + 1] == '?')
	{
		var = (char *)ft_itoa(exitnum);
		remainder = ft_substr(*str, *i + 2, ft_strlen(*str));
		ptr = ft_substr(*str, 0, *i);
		tmp = ft_strjoin(ptr, var);
		free(var);
		var = *str;
		*str = ft_strjoin(tmp, remainder);
		free(ptr);
		free(var);
		free(tmp);
		free(remainder);
		*i = 0;
	}
}

void	expand_var_f2(char **str, t_mini *mini, int *i)
{
	char	*var;
	char	*remainder;
	char	*tmp;

	if ((*str)[*i] == '$' && (*str)[*i + 1] != '\0' \
		&& (*str)[*i + 1] != '$' && (*str)[*i + 1] != '?')
	{
		var = ft_substr(*str, 0, *i);
		remainder = ft_substr(*str, *i + 1, ft_strlen(*str));
		tmp = replace_str(remainder, mini, varlen(remainder));
		remainder = *str;
		*str = ft_strjoin(var, tmp);
		free(var);
		free(remainder);
		free(tmp);
		*i = -1;
	}
}

char	*expand_var(char *str, t_mini *mini, t_exitnum *exitnum)
{
	int		i;

	i = 0;
	while (ft_strlen(str) > (size_t)i && str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '\0' || str[i + 1] == ' '))
			return (str);
		if (str[i] == '$' && str[i + 1] == '$')
			return (str);
		expand_var_f1(&str, exitnum->num, &i);
		expand_var_f2(&str, mini, &i);
		i++;
	}
	return (str);
}
