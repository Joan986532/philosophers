# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 10:27:31 by jnauroy           #+#    #+#              #
#    Updated: 2025/05/28 15:31:24 by jnauroy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = sources
HEAD_DIR = headers

NAME = philo

SOURCES = $(SRC_DIR)/philo.c \
		  $(SRC_DIR)/philo_utils.c \
		  $(SRC_DIR)/philo_utils2.c \
		  $(SRC_DIR)/print_messages.c \
		  $(SRC_DIR)/routine.c \
		  $(SRC_DIR)/threads.c \
		  $(SRC_DIR)/manager.c \
		  $(SRC_DIR)/thinking.c \

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -g -Wall -Wextra -Werror

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	cc $(OBJECTS) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: clean fclean re all
