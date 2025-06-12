/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:35:57 by xzhang            #+#    #+#             */
/*   Updated: 2024/05/15 13:36:01 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*To make sure the readline function works correctly after you have redirected
file descriptors, you need to restore the original file descriptors (stdin, 
stdout) after executing a command. This will ensure that subsequent calls to 
readline can read from the standard input again.*/
int	sub_redrectionstype1(t_instr *instr, int i, int fd)
{
	fd = open(instr->redir[i].str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(instr->redir[i].str);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	sub_redrectionstype2(t_instr *instr, int i, int fd)
{
	fd = open(instr->redir[i].str, O_RDONLY);
	if (fd < 0)
	{
		perror(instr->redir[i].str);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	sub_redrectionstype3(t_instr *instr, int i, int fd)
{
	fd = open(instr->redir[i].str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(instr->redir[i].str);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	checkredirections(t_instr *instr, int i, int fd)
{
	if (instr->redir[i].str == NULL)
		return (1);
	if (instr->redir[i].type == 1)
	{
		if (sub_redrectionstype1(instr, i, fd) == 1)
			return (1);
	}
	else if (instr->redir[i].type == 2)
	{
		if (sub_redrectionstype2(instr, i, fd) == 1)
			return (1);
	}
	else if (instr->redir[i].type == 3)
	{
		if (sub_redrectionstype3(instr, i, fd) == 1)
			return (1);
	}
	return (0);
}

int	handle_redirections(t_instr *instr, t_exitnum *exitnum)
{
	int		fd;
	int		i;

	i = 0;
	fd = 0;
	while (i < instr->redir_num)
	{
		if (instr->redir[i].type == 0)
			break ;
		else if (checkredirections(instr, i, fd) == 1)
			return (1);
		else if (instr->redir[i].type == 4)
		{
			heredoc(instr->redir[i].str, instr, exitnum);
		}
		i++;
	}
	return (0);
}
