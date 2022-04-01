/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:24:21 by jbrown            #+#    #+#             */
/*   Updated: 2022/04/01 16:24:23 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	build_byte(int sig)
{
	static int	byte;
	static int	count;

	if (sig == SIGUSR1)
		sig = 1;
	else
		sig = 0;
	byte = byte << 1 | sig;
	count++;
	if (!(count % 8))
	{
		ft_printf("%c", byte);
		byte = 0;
		count = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("PID: %i\n", pid);
	signal(SIGUSR1, &build_byte);
	signal(SIGUSR2, &build_byte);
	while (1)
		pause();
}
