/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:24:14 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/01 16:26:30 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_message(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i / 8])
	{
		if (str[i / 8] & (0x80 >> i % 8))
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		usleep(100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Not enough arguments.\n");
		return (1);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
}
