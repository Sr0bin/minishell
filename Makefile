# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 15:18:59 by rorollin          #+#    #+#              #
#    Updated: 2025/05/28 14:51:45 by lserodon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

#SOURCES######################

SOURCES_DIR = src

SOURCES_NAME = main.c

SOURCES_PIPEX = pipex.c ast_to_cmds.c main.c path.c pipes.c exec.c

SOURCES_DEBUG = debug.c

SOURCES = $(addprefix $(SOURCES_DIR)/,\
		  $(SOURCES_NAME)\
		  $(addprefix pipex/, $(SOURCES_PIPEX))\
		  )
		  # $(addprefix .hidden/, $(SOURCES_DEBUG))\
		  


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

all: git make_libft $(NAME)

$(NAME):  $(OBJECTS) $(LIBFT_PATH)
	$(COMPILER) $(CFLAGS) $(INCLUDES) $^ -o $@
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
