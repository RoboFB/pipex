# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:21:00 by rgohrig           #+#    #+#              #
#    Updated: 2025/07/21 18:06:29 by rgohrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := libft.a
CC := cc
# CFLAGS := -Wall -Werror -Wextra

HEADERS := -I include

DIR_SRC := src
SRC := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
		ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_prf_char.c ft_prf_hex_pointer.c ft_prf_int_uint.c ft_prf_printf.c \
		ft_prf_str.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c \
		get_next_line_utils.c

DIR_OBJ := obj
OBJ := $(SRC:%.c=$(DIR_OBJ)/%.o)

# default Rule
all : $(NAME)

# objects
$(DIR_OBJ):
	mkdir $(DIR_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<
	@echo 🐸 $@

# arrive
$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo 📘📗📙 $(NAME)   \($(CFLAGS)\)

clean :
	@rm -f $(OBJ)
	@echo 🧹 cleaned all objects

fclean : clean
	@rm -f $(NAME)
	@echo 🧹🧹🧹 cleaned $(NAME)

re : fclean all

.PHONY : all clean fclean re
