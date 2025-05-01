# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 10:27:31 by jnauroy           #+#    #+#              #
#    Updated: 2025/05/01 10:27:35 by jnauroy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = sources
HEAD_DIR = headers

NAME = philo

SOURCES = $(SRC_DIR)/philo.c \
		  $(SRC_DIR)/philo_utils.c \
		  $(SRC_DIR)/philo_utils2.c \
		  $(SRC_DIR)/print_messages.c \
		  $(SRC_DIR)/threads_routine.c

LIBFT = libft_philo/libft.a

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -fsanitize=thread -g -Wall -Wextra -Werror

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C libft_philo
	cc $(OBJECTS) $(LIBFT) $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C libft_philo
	rm -f $(OBJECTS)
fclean: clean
	$(MAKE) fclean -C libft_philo
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
