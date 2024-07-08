/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:14 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (-(unsigned char)s2[i]);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*result;
	size_t	max_size;

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_calloc(1, new_size));
	result = ft_calloc(1, new_size);
	if (new_size >= old_size)
		max_size = old_size;
	else
		max_size = new_size;
	ft_memmove(result, ptr, max_size);
	free(ptr);
	return (result);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*Need not free as it will loop to next readline. 
By then shd free_mini within main.c*/
int	ft_error(t_mini *mini, char *str, int i)
{
	printf("%s\n", str);
	mini->exit_status = i;
	return (i);
}
