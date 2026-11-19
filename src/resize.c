/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   resize.c                                          :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kseltenr <kseltenr@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 07:51:13 by kseltenr         #+#    #+#              */
/*   Updated: 2026/11/19 07:56:45 by kseltenr        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

static volatile sig_atomic_t	g_resized = 0;

static void	on_resize(int sig)
{
	(void)sig;
	g_resized = 1;
}

void	init_signals(void)
{
	signal(SIGWINCH, on_resize);
}

int32_t	consume_resize(void)
{
	if (!g_resized)
		return (0);
	g_resized = 0;
	return (1);
}
