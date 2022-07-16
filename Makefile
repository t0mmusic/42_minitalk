# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 11:33:14 by jbrown            #+#    #+#              #
#    Updated: 2022/07/16 17:59:41 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders

SRCS = srcs/utils.c

PRINTF = printf/archives/libftprintf.a

RM = rm -f

OBJ_DEST = objects
HEADER_DEST = headers
ARCHIVE_DEST = archives

OBJS = $(SRCS:srcs/%.c=objects/%.o)

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

all: $(PRINTF) $(OBJS)
	@make $(SERVER) >/dev/null & $(SERVER_MSG)
	@make $(CLIENT) >/dev/null & $(CLIENT_MSG)
	@$(COMPLETE_MSG)

$(PRINTF):
	@if [ ! -d "printf/" ]; then\
		printf "printf dependency needed. Download now? [y/N]" \
		&& read ans && [ $${ans:-N} = y ] \
		&& git clone https://github.com/t0mmusic/ft_printf.git printf; \
	fi
	@$(PRINTF_MSG)
	$(MAKE) bonus -C ./printf --no-print-directory
	@cp -r printf/$(ARCHIVE_DEST) $(ARCHIVE_DEST)
	@cp -r printf/$(OBJ_DEST) $(OBJ_DEST)
	@cp -r printf/$(HEADER_DEST)/. $(HEADER_DEST)

objects/%.o: srcs/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "Linked source: %s into object: %s\n" $< $@

$(SERVER):
	@$(CC) $(CFLAGS) srcs/server.c objects/*.o -o $(SERVER)

$(CLIENT):
	@$(CC) $(CFLAGS) srcs/client.c objects/*.o -o $(CLIENT)

clean:
	@$(MAKE) clean -C ./printf >/dev/null & $(PRINTF_CLEAN_MSG)
	@$(MAKE) clean -C ./printf/libft >/dev/null & $(LIBFT_CLEAN_MSG)
	rm -rf $(OBJ_DEST) $(ARCHIVE_DEST) $(HDR_INCL)

fclean: clean
	@$(MAKE) fclean -C ./printf >/dev/null & $(PRINTF_FCLEAN_MSG)
	@$(MAKE) clean -C ./printf/libft >/dev/null & $(LIBFT_FCLEAN_MSG)
	@$(RM) $(SERVER) & $(SERVER_CLEAN_MSG)
	@$(RM) $(CLIENT) & $(CLIENT_CLEAN_MSG)

re: fclean all

git:
	@git remote set-url origin https://github.com/t0mmusic/42_minitalk.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

.PHONY: all clean fclean bonus re git
