# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:21:00 by rgohrig           #+#    #+#              #
#    Updated: 2025/07/21 14:03:10 by rgohrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------- GENERAL ----------------------------------------

NAME :=			pipex
CC :=			cc
# CFLAGS :=		-Wall -Werror -Wextra # standard flags
CFLAGS :=		-Wall -Werror -Wextra -g -fsanitize=address,undefined # debug flags temporary

LIBFT :=		./libft
LIBS :=			$(LIBFT)/libft.a
HEADERS :=		-I ./include -I $(LIBFT)/include

# ----------------------------- NORMAL -----------------------------------------

DIR_SRC :=		src
SRC :=			child_processes.c \
				error_exit.c \
				exe_command.c \
				get_path.c \
				main.c \
				parser_check.c \
				split_command.c \
				split_processes.c \
				utils.c \
				utils_free.c

DIR_OBJ :=		obj
OBJ :=			$(SRC:%.c=$(DIR_OBJ)/%.o)

# ------------------------------------------------------------------------------

all: $(LIBFT)/libft.a $(NAME)

$(LIBFT)/libft.a:
	@$(MAKE) -C $(LIBFT)

$(DIR_OBJ):
	mkdir $(DIR_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<
	@echo 🖇 $@

# executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\n🖇🖇🖇 $(NAME)\n"

# ---------------------------- BONUS -------------------------------------------

BONUS_NAME :=		$(NAME)_bonus
BONUS_DIR_SRC :=	src/bonus
BONUS_SRC :=		child_processes_bonus.c \
					main_bonus.c \
					split_processes_bonus.c

BONUS_DIR_OBJ :=	obj/bonus
BONUS_OBJ :=		$(BONUS_SRC:%.c=$(BONUS_DIR_OBJ)/%.o)

# ------------------------------------------------------------------------------

bonus: all $(BONUS_NAME)

$(BONUS_DIR_OBJ):
	mkdir $(BONUS_DIR_OBJ)

$(BONUS_DIR_OBJ)/%.o : $(BONUS_DIR_SRC)/%.c | $(BONUS_DIR_OBJ)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<
	@echo 🖇🎁 $@

# executable
$(BONUS_NAME): $(BONUS_OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\n🖇🖇🖇🎁🎁🎁 $(NAME)\n"

# ------------------------------------------------------------------------------

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)
	@echo 🧹 cleaned all objects
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@echo 🧹🧹🧹 cleaned $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all bonus clean fclean re
