/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   signals.c                                         :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kseltenr <kseltenr@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 07:51:13 by kseltenr         #+#    #+#              */
/*   Updated: 2026/11/19 07:56:45 by kseltenr        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

static volatile sig_atomic_t	g_quit = 0;

static void	on_sigint(int sig)
{
	(void)sig;
	g_quit = 1;
}

void	init_signals(void)
{
	signal(SIGINT, on_sigint);
}

bool	should_quit(void)
{
	return (g_quit);
}
