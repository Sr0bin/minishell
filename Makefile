# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 15:18:59 by rorollin          #+#    #+#              #
#    Updated: 2025/08/30 11:46:40 by lserodon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#SOURCES######################

SOURCES_DIR = src

SOURCES_NAME = main.c

#---------------------------

SOURCES_DEBUG = debug.c

#---------------------------

SOURCES_PIPEX_EXEC = env_to_array.c error.c exec.c external.c free_utils.c io.c path.c pipes.c\
						status.c utils.c

SOURCES_BUILTINS = export.c export_args.c export_no_args.c cd.c echo.c env.c pwd.c\
				unset.c exit.c create_env.c builtins.c

SOURCES_PIPEX_AST = ast_to_cmds.c ast_utils.c\

#---------------------------

SOURCES_SIGNALS = signals.c\

#---------------------------

SOURCES_AST = ast_generation.c  ast_core.c token_to_node.c cmd_core.c node_generation.c\
			  redir_core.c redir_list_core.c pipe_find.c

#---------------------------

SOURCES_EXPAND = expand.c

#---------------------------

SOURCES_PARSER_HANDLER = handle_normal.c handle_dquote.c handle_squote.c handle_op.c handle_normal_end.c

SOURCES_PARSER_STATE = transition_utils.c

SOURCES_PARSER_TOKEN = token_assign.c token_core.c token_list_clean.c token_expand.c

SOURCES_PARSER = $(addprefix handler/, $(SOURCES_PARSER_HANDLER))\
				 $(addprefix state/, $(SOURCES_PARSER_STATE)) \
				 $(addprefix token/, $(SOURCES_PARSER_TOKEN)) \
				 parser_core.c string_utils.c 
#---------------------------

SOURCES = $(addprefix $(SOURCES_DIR)/,\
		  $(SOURCES_NAME)\
		  $(addprefix parser/, $(SOURCES_PARSER))\
		  $(addprefix ast_generation/, $(SOURCES_AST))\
		  $(addprefix .hidden/, $(SOURCES_DEBUG))\
		  $(addprefix exec/exec/, $(SOURCES_PIPEX_EXEC))\
		  $(addprefix exec/ast/, $(SOURCES_PIPEX_AST))\
		  $(addprefix builtins/, $(SOURCES_BUILTINS))\
		  $(addprefix expand/, $(SOURCES_EXPAND))\
		  $(addprefix signals/, $(SOURCES_SIGNALS))\
		  )
		  
#OBJECTS#######################

OBJ_DIR = obj

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

#DEPS##########################

DEPS = $(SOURCES:%.c=$(OBJ_DIR)/%.d)

#INCLUDES#######################

HEADERS_DIR = include/ libft/include/

INCLUDES = $(addprefix -I , $(HEADERS_DIR)) 

#LIBFT########################

LIBFT = libft

LIBFT_PATH = $(LIBFT)/$(LIBFT).a

#COMPILER#####################

COMPILER = cc

CFLAGS_DEBUG = -Wall -Wextra -Werror -MMD -MP -ggdb3 -Wshadow -Wconversion -Wsign-conversion \
-Wformat=2 -Wformat-security -Wnull-dereference -Wstack-protector -Wfloat-equal -Wpointer-arith \
-Wcast-align -Wundef -Wbad-function-cast -Wstrict-overflow=4 -Wdouble-promotion -Walloca -Wvla \
-Wwrite-strings -Wuninitialized -fno-delete-null-pointer-checks -fno-omit-frame-pointer -std=c11 \
-Iinclude

CFLAGS_PROD = -Wall -Wextra -MMD -MP -g

CFLAGS = $(CFLAGS_PROD)

export CFLAGS

all: make_libft $(NAME)

$(NAME):  $(OBJECTS) $(LIBFT_PATH)
	$(COMPILER) $(CFLAGS) $(INCLUDES) $^ -lreadline -o $@
	@echo "$(NAME) built succesfully."


$(OBJ_DIR)/%.o: %.c 
	mkdir -p $(dir $@)
	$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

git: 
	@git submodule update --init --remote --recursive

make_libft:
	$(MAKE) -C $(LIBFT)
	
clean:
	@$(MAKE) -s -C $(LIBFT) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf .cache/
	@rm -f .bonus
	@echo "Cleaned !"

fclean:
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) clean
	@rm -f $(NAME)
	@echo "Fcleaned !"

re:	
	$(MAKE) fclean 
	$(MAKE) all


.PHONY: all clean fclean re make_libft git
