/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:45:13 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/02 21:45:13 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*	Starting with the least significant bit, this function reconstructs a full
	byte and returns it. If SIGUSR1 is received, bit is set to 1, for SIGUSR2, 
	it is set to 0. The bit recieved is shifted to the left based on the
	number of bits already recieved until a full 8 bits have been constructed.
	It then returns the completed byte and resets the counter. When the byte
	is not fully constructed, it will return -1 to indicate the byte is not
	yet ready.	*/

int	reconstruct(int bit)
{
	static int		byte;
	static int		count;
	unsigned char	ret;

	if (bit == SIGUSR1)
		bit = 1;
	else
		bit = 0;
	byte += bit << count;
	count++;
	if (count == 8)
	{
		ret = byte;
		byte = 0;
		count = 0;
		return (ret);
	}
	return (-1);
}

/*	This function breaks bytes down into individual bits and sends a signal
	depending on the bit. Starting with the least significant bit, if it is
	a 1, SIGUSR1 is sent, if it is a 0, SIGUSR2 is sent. The byte is devided
	by two each time until it reaches 0. If it reaches 0 before the count has
	reached bit_num, it will send SIGUSR2 each time.	*/

void	deconstruct(int byte, int pid, int bit_num)
{
	int	count;

	count = 0;
	while (byte || count < bit_num)
	{
		if (byte % 2)
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		byte /= 2;
		usleep(100);
		count++;
	}
}
