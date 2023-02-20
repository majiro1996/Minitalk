/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:15 by manujime          #+#    #+#             */
/*   Updated: 2023/02/20 15:47:51 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
/*sends the bits of byte, bit by bit to the server,
it checks if the bit is a 1 or a 0 with a bitwise AND,
-to do this it creates a mask with 1 (00000001) and moves the 1
bit_c positions to the left-
if the bit is 1 it send SIGUSR1
if the bit is 0 it sends SIGUSR2
after sending the signal the execution is paused 50 microseconds
to give the server time to respond to the signal*/
void	ft_send(int pid, char byte)
{
	int	bit_c;

	bit_c = 0;
	while (bit_c < 8)
	{
		if ((byte & (1 << bit_c)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
		bit_c++;
	}
}

/*This is the handler function called when the server has finished
 displaying the message and sent the SIGUSR1, it prints a message*/
void	ft_recon(int s)
{
	if (s == SIGUSR1)
		ft_printf("The message has been handled correctly");
}

/*takes the first argument as the pid of the server,
sets the ft_recon as the handler to be called when SIGURS1 is received
then calls ft_send for each character in the second argument including the \0
if the number of arguments is not 2 it prints a prompt with the proper format*/
int	main(int argc, char **argv)
{
	int					c;
	int					pid;
	struct sigaction	sign;

	c = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		sign.sa_handler = &ft_recon;
		sigaction(SIGUSR1, &sign, NULL);
		while (argv[2][c] != '\0')
		{
			ft_send(pid, argv[2][c]);
			c++;
		}
		ft_send(pid, argv[2][c]);
	}
	else
	{
		ft_printf("WRONG INPUT FORMAT\ntry with: ./client \"PID\" \"message\"");
	}
	return (0);
}
