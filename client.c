/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:24:14 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/02 23:00:16 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	The server will return 8 1's to the client once it has printed the sent
	message. This function will print a confirmation message once this has
	happened to confirm that the message was sent succefully.	*/

void	confirm_send(int bit)
{
	if (bit == SIGUSR1)
	{
		ft_printf("Message Sent Successfully!\n");
		exit(0);
	}
	if (bit == SIGUSR2)
	{
		ft_printf("Something has gone horribly wrong...\n");
		exit (1);
	}
}

/*	The client's PID is broken down into a stream of bits and sent to the
	server. Once all 4 bytes (32 bits) have been sent, the message input in the
	command line is broken down into individual bytes, then individual
	bits, and sent to the server. Finally, an empty byte is sent to the
	server to indicate that the message is complete.	*/

void	send_message(int pid, char *str)
{
	int	i;
	int	client_pid;

	client_pid = getpid();
	deconstruct(client_pid, pid, 32);
	i = 0;
	while (str[i])
	{
		ft_printf("%c", str[i]);
		deconstruct(str[i], pid, 8);
		i++;
	}
	ft_printf("\n");
	deconstruct(0, pid, 8);
}

/*	Displays a message telling the user what information must be added in
	the command line in order to send a message to the server. It then
	pauses while it waits for the server to confirm that it has recieved
	the message.	*/

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Aruments must be server PID and text string.\n");
		return (1);
	}
	ft_printf("Client PID: %i\n", getpid());
	send_message(ft_atoi(argv[1]), argv[2]);
	signal(SIGUSR1, &confirm_send);
	signal(SIGUSR2, &confirm_send);
	while (1)
		pause();
}
