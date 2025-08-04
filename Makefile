# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 15:18:59 by rorollin          #+#    #+#              #
#    Updated: 2025/08/04 19:29:14 by rorollin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#SOURCES######################

SOURCES_DIR = src

SOURCES_NAME = main.c token_utils.c

SOURCES_AST = ast_generation.c  ast_utils.c token_to_node.c

SOURCES_PARSER_HANDLER = handle_normal.c handle_dquote.c handle_squote.c handle_op.c

SOURCES_PARSER_STATE = transition_utils.c

SOURCES_PARSER = $(addprefix handler/, $(SOURCES_PARSER_HANDLER))\
				 $(addprefix state/, $(SOURCES_PARSER_STATE)) \
				 parser_utils.c string_utils.c clean_token.c assign_token.c

SOURCES_DEBUG = debug.c

SOURCES = $(addprefix $(SOURCES_DIR)/,\
		  $(SOURCES_NAME)\
		  $(addprefix parser/, $(SOURCES_PARSER))\
		  $(addprefix ast/, $(SOURCES_AST))\
		  $(addprefix .hidden/, $(SOURCES_DEBUG))\
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

CFLAGS_DEBUG = -Wall -Wextra -Werror -MMD -MP -ggdb3 -Wshadow -Wconversion -Wsign-conversion -Wmissing-prototypes \
-Wformat=2 -Wformat-security -Wnull-dereference -Wstack-protector -Wfloat-equal -Wpointer-arith \
-Wcast-align -Wundef -Wbad-function-cast -Wstrict-overflow=4 -Wdouble-promotion -Walloca -Wvla \
-Wwrite-strings -Wuninitialized -fno-delete-null-pointer-checks -fno-omit-frame-pointer -std=c11

CFLAGS_PROD = -Wall -Wextra -Werror -MMD -MP -ggdb3 -O3

CFLAGS = $(CFLAGS_DEBUG)

export CFLAGS

all: make_libft $(NAME)

$(NAME):  $(OBJECTS) $(LIBFT_PATH)
	$(COMPILER) $(CFLAGS) $(INCLUDES) -lreadline $^ -o $@
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
