# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 15:56:27 by albbermu          #+#    #+#              #
#    Updated: 2024/06/19 16:27:12 by albbermu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CLIENT_SRCS := client.c
SERVER_SRCS := server.c
CLIENT_BONUS_SRCS := client_bonus.c
SERVER_BONUS_SRCS := server_bonus.c
LIBFT_PATH := libft
LIBFT_ARCHIVE := $(LIBFT_PATH)/libft.a
CLIENT_NAME := client
SERVER_NAME := server
CLIENT_BONUS_NAME := client_bonus
SERVER_BONUS_NAME := server_bonus
HEADER := minitalk.h

# ANSI escape codes for colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(CLIENT_NAME) $(SERVER_NAME)

bonus: $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

$(CLIENT_NAME): $(CLIENT_SRCS) $(LIBFT_ARCHIVE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_SRCS) -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft
	@echo "$(GREEN)Client compiled successfully.$(RESET)"

$(SERVER_NAME): $(SERVER_SRCS) $(LIBFT_ARCHIVE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(SERVER_SRCS) -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft
	@echo "$(GREEN)Server compiled successfully.$(RESET)"

$(CLIENT_BONUS_NAME): $(CLIENT_BONUS_SRCS) $(LIBFT_ARCHIVE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_BONUS_SRCS) -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft
	@echo "$(GREEN)Bonus client compiled successfully.$(RESET)"

$(SERVER_BONUS_NAME): $(SERVER_BONUS_SRCS) $(LIBFT_ARCHIVE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(SERVER_BONUS_SRCS) -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft
	@echo "$(GREEN)Bonus server compiled successfully.$(RESET)"

$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_PATH)
	@echo "$(GREEN)Libft compiled successfully.$(RESET)"

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	@echo "$(YELLOW)Cleaned object files.$(RESET)"

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)
	@echo "$(YELLOW)Cleaned all files.$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
