# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 11:33:14 by jbrown            #+#    #+#              #
#    Updated: 2022/04/04 12:39:49 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

BONUS_SERVER = bonus_server
BONUS_CLIENT = bonus_client

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders

SRCS = srcs/

PRINTF_A = printf/libftprintf.a

RM = rm -f

PRINTF_MSG = echo "ft_printf library compiling..."
SERVER_MSG = echo "server compiling"
CLIENT_MSG = echo "client compiling"
COMPLETE_MSG = echo "Ready! run ./server to get server PID, then ./client <PID> <MESSAGE>"
PRINTF_CLEAN_MSG = echo "Removing printf object files"
PRINTF_FCLEAN_MSG = echo "Removing printf"
LIBFT_CLEAN_MSG = echo "Removing libft object files"
LIBFT_FCLEAN_MSG = echo "Removing libft"
CLIENT_CLEAN_MSG = echo "Removing client"
SERVER_CLEAN_MSG = echo "Removing server"

all:
	@$(PRINTF_MSG)
	@$(MAKE) bonus -C ./printf >/dev/null
	@make $(SERVER) >/dev/null & $(SERVER_MSG)
	@make $(CLIENT) >/dev/null & $(CLIENT_MSG)
	@$(COMPLETE_MSG)

$(SERVER):
	@$(CC) $(CFLAGS) $(SRCS)server.c $(SRCS)utils.c $(PRINTF_A) -o $(SERVER)

$(CLIENT):
	@$(CC) $(CFLAGS) $(SRCS)client.c $(SRCS)utils.c $(PRINTF_A) -o $(CLIENT)

bonus: 
	@$(PRINTF_MSG)
	@$(MAKE) bonus -C ./printf >/dev/null
	@make $(SERVER) >/dev/null & $(SERVER_MSG)
	@make $(CLIENT) >/dev/null & $(CLIENT_MSG)
	@$(COMPLETE_MSG)

$(BONUS_SERVER):
	@$(CC) $(CFLAGS) $(SRCS)$(BONUS_SERVER).c $(SRCS)utils.c $(PRINTF_A) -o $(SERVER)

$(BONUS_CLIENT):
	@$(CC) $(CFLAGS) $(SRCS)$(BONUS_CLIENT).c $(SRCS)utils.c $(PRINTF_A) -o $(CLIENT)

clean:
	@$(MAKE) clean -C ./printf >/dev/null & $(PRINTF_CLEAN_MSG)
	@$(MAKE) clean -C ./printf/libft >/dev/null & $(LIBFT_CLEAN_MSG)

fclean: clean
	@$(MAKE) fclean -C ./printf >/dev/null & $(PRINTF_FCLEAN_MSG)
	@$(MAKE) clean -C ./printf/libft >/dev/null & $(LIBFT_FCLEAN_MSG)
	@$(RM) $(SERVER) & $(SERVER_CLEAN_MSG)
	@$(RM) $(CLIENT) & $(CLIENT_CLEAN_MSG)

re: fclean all

.PHONY: all clean fclean bonus re
