# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xzhang <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 13:26:08 by xzhang            #+#    #+#              #
#    Updated: 2024/06/19 19:57:54 by xzhang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
RED    = '\033[1;31m'
GREEN  = '\033[1;32m'
BLUE   = '\033[1;34m'
CYAN   = '\033[0;36m'

#------------------------------------------------------------------------

#Variables
NAME   = minishell

#------------------------------------------------------------------------

# minishell targets
MAIN = srcs/main.c

# lexer
LEXER = lexer.c\
		lexer1.c 

LEXER_SRCS = $(addprefix srcs/lexer/, $(LEXER))

# parser
PARSER = parser.c\
		 parser1.c\
	     instr.c\
	     instr1.c\
	     instr2.c

PARSER_SRCS = $(addprefix srcs/parser/, $(PARSER))

# execute
EXEC = exec.c\
	   redirection.c\
	   exec_inpipe.c\
	   exec_inpipeline.c\
	   exec_inpipeline1.c\
	   execute.c\
	   execve.c\
	   limiter.c\
	   limiter1.c\
	   fd.c\
	   heredocinp.c\
	   heredocinpipe.c\
	   utilsinexec.c

EXEC_SRCS = $(addprefix srcs/execute/, $(EXEC))

# builtins
BUILTIN = build_ins.c\
		  build_ins1.c\
		  build_ins2.c\
		  build_ins3.c\
	      build_ins_utils.c\
	      build_ins_utils1.c\
	      build_ins_utils2.c

BUILTIN_SRCS = $(addprefix srcs/builtin/, $(BUILTIN))

#utils
UTIL = free.c\
	   free1.c\
	   utils.c\
	   utils1.c

UTIL_SRCS = $(addprefix srcs/utils/, $(UTIL))

# signals
SIG = signal.c #\
#	signals_utils.c
SIG_SRCS = $(addprefix srcs/signals/, $(SIG))

#------------------------------------------------------------------------

SRCS =  $(MAIN) $(BUILTIN_SRCS) $(LEXER_SRCS) $(PARSER_SRCS) $(EXEC_SRCS) \
		$(UTIL_SRCS) $(SIG_SRCS)
OBJS = $(SRCS:srcs/%.c=objs/%.o) #$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))


SRC_DIR = srcs/utils srcs/builtin srcs/execute srcs/parser srcs/lexer \
		  srcs/signals
OBJ_DIR = objs/

INC = -I ./include

LIBFT = libft.a
LIB_DIR = ./libft
LIB_FLAGS = -L $(LIB_DIR) -lreadline -lft


CC     = cc
RM     = rm -rf
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

#------------------------------------------------------------------------

# RULES
# all = create library from sub-make
#Main targets
all:  ${LIBFT} ${NAME}
	@echo
	@echo  Hello Welcome to Minishell!
	@echo #******************************************
	@echo *███╗xxx███╗██╗███╗xxx██╗██╗xxxxxxxxxxxxx*
	@echo *████╗x████║██║████╗xx██║██║xxxxxxxxxxxxx*
	@echo *██╔████╔██║██║██╔██╗x██║██║xxxxxxxxxxxxx*
	@echo *██║╚██╔╝██║██║██║╚██╗██║██║xxxxxxxxxxxxx*
	@echo *██║x╚═╝x██║██║██║x╚████║██║xxxxxxxxxxxxx*
	@echo *╚═╝xxxxx╚═╝╚═╝╚═╝xx╚═══╝╚═╝xxxxxxxxxxxxx*
	@echo *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*
	@echo *███████╗██╗xx██╗███████╗██╗xxxxx██╗xxxxx*
	@echo *██╔════╝██║xx██║██╔════╝██║xxxxx██║xxxxx*
	@echo *███████╗███████║█████╗xx██║xxxxx██║xxxxx*
	@echo *╚════██║██╔══██║██╔══╝xx██║xxxxx██║xxxxx*
	@echo *███████║██║xx██║███████╗███████╗███████╗*
	@echo *╚══════╝╚═╝xx╚═╝╚══════╝╚══════╝╚══════╝*
	@echo #******************************************
# can not use echo * it is the same as ls
$(NAME):  $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_FLAGS) $(INC)
	@echo $(CYAN) "$(NAME) made!"

$(LIBFT):
	@echo "\n"$(GREEN)"[ COMPILING: $(LIBFT) ]"
	@make  --no-print-directory -C ./libft
	@echo "\n"$(GREEN)"[ COMPILING: $(NAME) ]"

#$(OBJ_DIR)%.o: $(SRC_DIR)%.c
#	@mkdir -p $(OBJ_DIR)
objs/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\t$(CYAN)$< done."

# remove temporary generated files
clean:
	@make clean --no-print-directory -C ./$(LIB_DIR)
	@${RM} $(OBJ_DIR)
	@echo $(RED)"Removed $(OBJ_DIR)."

fclean: clean
	@make fclean  --no-print-directory -C ./$(LIB_DIR)
	@${RM} $(NAME)
	@echo $(RED)"Removed $(NAME) and $(LIBFT)."

re: fclean all

# declare phony
.PHONY: all clean fclean
