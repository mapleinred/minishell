/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:53:28 by mertan            #+#    #+#             */
/*   Updated: 2024/06/30 17:11:50 by achak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>

extern int				g_exit;
typedef struct s_mini	t_mini;
typedef struct s_instr	t_instr;

typedef struct s_exitnum
{
	int					num;
}	t_exitnum;

typedef struct s_tkn
{
	char				*str;
	int					type;
	t_mini				*mini;
}	t_tkn;

typedef struct s_pipe
{
	t_mini				*mini;
	int					orgstdin;
	int					orgstdout;
	int					orgstderr;
}	t_pipe;

typedef struct s_redir
{
	char				*str;
	int					type;
	int					heredoc_fd;
	t_instr				*instr;
}	t_redir;

typedef struct s_instr
{
	char				**cmd_arr;
	char				*cmd;
	char				*arg;
	t_redir				redir[64];
	int					redir_num;
	t_mini				*mini;
}	t_instr;

typedef struct s_mini
{
	char				*input;
	t_tkn				tkn[128];
	int					tks_num;
	t_instr				instr[64];
	int					instr_num;
	int					env_count;
	char				**e;
	t_pipe				*pipe;
	int					exit_status;
}	t_mini;

//main.c
void	init_mini_instr(t_mini *mini);
void	init_mini(t_mini *mini);
void	init_env(t_mini *mini, char *envp[]);
//t		main(int ac, char **av, char *envp[]);

//signal.c
void	handler_ctl_c(int sig);
void	init_sighandler(t_mini *mini);

//lexer.c 	
int		find_strlen(char *str, int type, int i);
void	init_tkn_type1(char *str, t_tkn *tkn, int len, int str_pos);
int		init_tkn(char *str, t_tkn *tkn, int type, int str_pos);
//lexer1.c
int		make_tkn_error(t_mini *mini, int i);
void	make_tkn_var(t_mini *mini, int *i, int *j, int *k);
int		make_tkn(t_mini *mini);

//parser.c
int		parse_tkn_f1(t_mini *mini, int i);
int		parse_tkn_f2(t_mini *mini, int i);
int		parse_tkn(t_mini *mini, t_exitnum *exitnum);
//parser1.c
char	*ft_getenv(char *var, t_mini *mini);
char	*replace_str(char *var, t_mini *mini, int len);
int		parse_tkn(t_mini *mini, t_exitnum *exitnum);
void	expand_var_f1(char **str, int exitnum, int *i);
void	expand_var_f2(char **str, t_mini *mini, int *i);
char	*expand_var(char *str, t_mini *mini, t_exitnum *exitnum);

//instr.c
int		init_instr_f1(t_mini *mini, int i, t_instr *instr);
int		init_instr(t_mini *mini, int i, t_instr *instr);
int		init_instr_cmdarr1(t_mini *mini, int i, t_instr *instr, int *j);
int		init_instr_cmdarr(t_mini *mini, int i, t_instr *instr);
void	create_instr(t_mini *mini);
//instr1.c
int		init_arg_f2(t_mini *mini, int i, int j, t_instr *instr);
int		init_arg_f1(t_mini *mini, int i, t_instr *instr);
int		init_arg(t_mini *mini, int i, t_instr *instr);
int		init_arg1(t_mini *mini, int i, int *j, t_instr *instr);
//instr2.c
int		init_redir_f1(t_mini *mini, int i, t_instr *instr, int *k);
int		init_redir(t_mini *mini, int i, t_instr *instr);

//build_ins.c
int		ft_exit(t_instr *instr, t_exitnum *exitnum);
int		ft_cd(t_instr *instr);
int		ft_pwd(t_instr *instr);
int		ft_env(t_instr *instr);
int		ft_unset(t_instr *instr);
//build_ins1.c
int		ft_export_a1(t_instr *instr, int *i, char *var, int *j);
int		ft_export_a2(t_instr *instr, int *i, char *var, int *j);
int		ft_export_a3(t_instr *instr, int *i, int *j);
int		ft_export_a4(t_instr *instr, int i, int j, char *var);
int		ft_export(t_instr *instr);
//build_ins2.c
int		ft_echo_opt(t_instr *instr, int *flag, int k, int *j);
int		ft_echo_tkn(t_instr *instr, int *flag);
int		ft_echo(t_instr *instr);
//build_ins3.c
int		ft_export_error(t_instr *instr, char *var, char *str);
int		ft_export_exec_f1(char *str, int i);
int		ft_export_exec(t_instr *instr, char *str);
void	ft_export_nq(t_instr *instr);
int		check_omitspaces(t_instr *instr);
//build_ins_utils.c
int		update_env(char	*var, char *new_str, t_mini *mini);
char	*get_env_path(char *var, char **e);
int		update_cd_status(char *arg, t_mini *mini);
int		check_env(char *str, char *var, t_instr *instr);
int		declare_env(char **env, int env_count);
/*build_ins_utils1.c*/
void	sort_env_ascii(char **env, int env_count);
void	find_var_str(char **env);
void	ft_exit_a(t_mini *mini, int i);
void	ft_exit_sign(t_instr *instr);
int		ft_unset_exec(t_instr *instr, char *str);
/*build_ins_utils2.c*/
void	append_env(t_instr *instr, char *str, int count);

//utils.c
int		ft_isalnumus(int c);
int		check_alpha(char *str);
int		check_number(char *str);
int		varlen(char *str);
int		count_words(char *str, char c);
//utils1.c
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	ft_swap(char **a, char **b);
int		ft_error(t_mini *mini, char *str, int i);

//free.c
//void	free_str(char **str);
void	free_env(char **e);
void	free_tkn(t_mini *mini);
void	free_redir(t_instr *instr);
void	free_instr(t_mini *mini);
void	free_mini(t_mini *mini);
//free1.c
int		free_tokens(t_mini *mini);
void	freemem(char **str);
void	fterror(char *str);
int		check_buil(char *str);
void	ftperror(char *str);

//exec_inpipe.c
void	handle_builtin(t_instr *instr, char **envp, t_exitnum *exitnum);
void	handle_dot_slash_command(t_instr *instr, t_exitnum *exitnum);
void	handle_slash_command(t_instr *instr, char **envp, \
t_exitnum *exitnum);
int		exec_inthepipe(t_instr *instr, char **envp, t_exitnum *exitnum);

//exec_inpipeline.c
void	execute_command(char *path, char **cmd, t_instr *instr, \
t_exitnum *exitnum);
void	create_pipes(int pipes[][2], int num_pipes);
int		handle_single_command(t_mini *mini, t_exitnum *exitnum);
void	setup_signals_for_fork(t_mini *mini);

//exec_inpipeline1.c
void	setup_pipes_for_child(int pipes[][2], int i, int num_pipes);
void	fork_child_process(t_mini *mini, int pipes[][2], int i, \
t_exitnum *exitnum);
void	fork_processes(t_mini *mini, int pipes[][2], int pids[], \
t_exitnum *exitnum);
void	closepipes(int pipes[][2], int num_pipes);
void	wait_for_children(t_mini *mini, int pids[], int instr_num);

//exec.c
int		exec_buil(t_mini *mini, t_exitnum *exitnum);
int		exec_buil1(t_instr *instr, t_exitnum *exitnum);
int		exec_instr(t_mini *mini, t_exitnum *exitnum);
int		exec_pipeline(t_mini *mini, int instr_num, t_exitnum *exitnum);

//execute.c
char	**initialize_cmd(t_instr *instr);
char	*get_path_or_exit(char *cmd, t_instr *instr, char **envp, \
t_exitnum *exitnum);
char	*subfindpath(t_mini *mini, char *cmd, int i);
char	*findpath(char *cmd, t_mini *mini, t_exitnum *exitnum);
int		execute(t_instr *instr, char **envp, t_exitnum *exitnum);

//execve.c
int		checkexecve_program(t_instr *instr);
int		checkexecve(t_instr *instr);

//fd.c
void	initfd(t_mini *mini);
void	restorefd(t_mini *mini);
void	handle_sigint1(int sig);
void	signal_handler(int sig);
void	set_up_signals(void);

//heredocinp.c
void	handle_l(int sig);
void	child_process_setup(int fd[2], char *delimiter, \
	t_instr *instr, t_exitnum *exitnum);
int		parent_process_setup(int fd[2], int pid, t_instr *instr);
int		create_pipe_and_fork(int fd[2]);
int		heredoc(char *delimiter, t_instr *instr, t_exitnum *exitnum);

//heredocinpipe.c
void	signalinpipeheredocs(struct sigaction *sa);
int		is_heredoc_end(char *delimiter, char *str);
int		heredoc_loop(int pipefd, t_instr *instr, int j, t_exitnum *exitnum);
int		handle_heredocinpipe(t_instr *instr, int j, t_exitnum *exitnum);
int		open_all_heredocs(t_mini *mini, t_exitnum *exitnum);

//limiter.c
void	print_heredocwarninginp(char *limiter, char *input, \
	t_mini *mini, t_exitnum *exitnum);
int		check_heredocdelimiterinp(char *input, char *limiter);
void	free_resourcesinp(char *input, t_mini *mini, t_exitnum *exitnum);
int		f_n_c(char *str, int fd, t_mini *mini, t_exitnum *exitnum);
void	handle_sigint2(int sig);
//limiter1.c
int		limiter(char *limiter, int *fd, t_mini *mini, t_exitnum *exitnum);

//redirection.c  
int		sub_redrectionstype1(t_instr *instr, int i, int fd);
int		sub_redrectionstype2(t_instr *instr, int i, int fd);
int		sub_redrectionstype3(t_instr *instr, int i, int fd);
int		checkredirections(t_instr *instr, int i, int fd);
int		handle_redirections(t_instr *instr, t_exitnum *exitnum);

//utilsinexec.c
int		free_and_close(char *str, int fd);
void	print_heredoc_warning(char *delimiter);
int		handle_redirectionsinpipe(t_instr *instr, t_exitnum *exitnum);
void	handle_child_signals(int i);
void	handle_sigint(int sig);

#endif
