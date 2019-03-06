# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jocohen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 06:17:23 by jocohen           #+#    #+#              #
#    Updated: 2018/04/16 12:15:04 by jocohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = ft_ls

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -Llibft
LDLIBS = -lft

INCLUDE = ./includes
PATH_LIB = ./libft/
PATH_SRC = ./
PATH_OBJ = ./obj/

NAME_SRC = ft_ls.c \
		   get_options.c \
		   train.c \
		   display_all.c \
		   lst_creation.c \
		   sorter.c \
		   swapping_lst.c \
		   projection_room.c \
		   lonely_railman.c \
		   train_management.c \
		   swapping_tab.c \
		   railway_sorting.c \
		   get_uid.c \
		   formatting_vhs.c \
		   time_rights.c \
		   padd_materializing.c \
		   error.c \
		   fct_qsort.c

NAME_OBJ = $(NAME_SRC:.c=.o)

SRC = $(addprefix $(PATH_SRC),$(NAME_SRC))
OBJ = $(addprefix $(PATH_OBJ),$(NAME_OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PATH_LIB)
	@gcc $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "$(NAME) : DONE"

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@gcc $(CFLAGS) -I $(INCLUDE) -o $@ -c $<
	
clean:
	@rm -f $(OBJ)
	@make clean -C $(PATH_LIB) 
	@rmdir $(PATH_OBJ) 2> /dev/null || true
	@echo "$(NAME) : CLEANED"

fclean: clean
	@make fclean -C $(PATH_LIB)
	@rm -f $(NAME) 

re: fclean all

debug : $(OBJ)
	@make -C $(PATH_LIB)
	@gcc $(CFLAGS) $(LDFLAGS) $(LDLIBS) -fsanitize=address -g3 $^ -o $(NAME)
	@echo "$(NAME) : DEBUG MODE"
