# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 22:34:49 by sgadinga          #+#    #+#              #
#    Updated: 2025/07/30 08:53:19 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libcore.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes
ARCHIVE = ar rcs

SRCS_DIR = src
OBJS_DIR = obj

SRCS = $(addprefix $(SRCS_DIR)/, \
		 core_isalpha.c core_isdigit.c core_isspace.c core_min.c core_max.c \
		 core_putendl_fd.c core_putstr_fd.c core_putnbr_fd.c core_tolower.c \
		 core_strtol.c core_usleep.c get_current_time.c fatal_error.c \
		 internal/core_strtol_utils.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(ARCHIVE) $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
