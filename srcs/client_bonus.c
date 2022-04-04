/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:32:51 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/04 12:35:22 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/*	The server will return SIGUSR1 to the client once it has printed the sent
	message. This function will print a confirmation message once this has
	happened to confirm that the message was sent succefully. The other message
	should never occour.	*/

void	confirm_send(int bit)
{
	if (bit == SIGUSR2)
	{
		ft_printf("Message Sent Successfully!\n");
		exit(0);
	}
	if (bit == SIGUSR1)
	{
		ft_printf("Something has gone horribly wrong...\n");
		exit (1);
	}
}

/*	The client's PID is broken down into a stream of bits and sent to the
	server. Once all 4 bytes (32 bits) have been sent, the message input in
	the command line is broken down into individual bytes cast as unsigned
	chars to allow unicode characters to be sent, then turned into individual
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
		deconstruct((unsigned char)str[i], pid, 8);
		i++;
	}
	deconstruct(0, pid, 8);
}

/*	A 3 second delay is given for the server to return a signal to the client.
	If the signal is not received, an error message is displayed and the
	program terminates. Also gives the user a message detailing the expected
	input for the program.	*/

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Expected: ./client <PID> <MESSAGE>\n");
		return (1);
	}
	signal(SIGUSR1, &confirm_send);
	signal(SIGUSR2, &confirm_send);
	send_message(ft_atoi(argv[1]), argv[2]);
	ft_printf("Client PID: %i\n", getpid());
	sleep(3);
	ft_printf("Confirmation from server not received.\n");
	ft_printf("Check server PID is correct.\n");
	return (1);
}
