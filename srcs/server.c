/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:24:21 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/04 11:57:00 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	As each bit is recieved from the client, the information is built up bit by
	bit until we have a full byte. The first 4 bytes received will contain the
	client PID needed to send a confirmation back. Next, the string entered in
	the command line in the client program is reconstructed. Once a full byte
	has been made it is immediately printed. Finally, an empty byte is received
	indicating the message is complete. A newline is printed and a bit is
	returned to the client. The client PID and counter are then reset so the
	server can receive another message.	*/

void	build_byte(int bit)
{
	int			byte;
	static int	count;
	static int	client_pid;

	byte = reconstruct(bit);
	if (byte >= 0 && count < 4)
	{
		client_pid += byte << count * 8;
		count++;
		if (count == 4)
			ft_printf("Client PID: %i\n", client_pid);
	}
	else if (byte > 0)
		ft_printf("%c", byte);
	else if (!byte)
	{
		ft_printf("\n");
		usleep(1000);
		deconstruct(0, client_pid, 8);
		count = 0;
		client_pid = 0;
	}
}

/*	To keep the server running, a while loop that will never exit is pausing
	the program. Each time a signal is recieved it can be processed into a
	usuable byte. Receiving signal SIGUR1 will be a 1, SIGUSR2 will be a 0. */

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("Server PID: %i\n", pid);
	signal(SIGUSR1, &build_byte);
	signal(SIGUSR2, &build_byte);
	while (1)
		pause();
}
