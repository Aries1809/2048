/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 21:59:11 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/20 22:00:10 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

static chtype	joint(int r, int c, int n)
{
	if (r == 0)
		return (c == 0 ? ACS_ULCORNER : c == n ? ACS_URCORNER : ACS_TTEE);
	if (r == n)
		return (c == 0 ? ACS_LLCORNER : c == n ? ACS_LRCORNER : ACS_BTEE);
	return (c == 0 ? ACS_LTEE : c == n ? ACS_RTEE : ACS_PLUS);
}

void	draw_grid(int y, int x, int n, int cw, int ch)
{
	for (int i = 0; i <= n; i++)
	{
		mvhline(y + i * (ch + 1), x, ACS_HLINE, n * (cw + 1) + 1);
		mvvline(y, x + i * (cw + 1), ACS_VLINE, n * (ch + 1) + 1);
	}
	for (int r = 0; r <= n; r++)
		for (int c = 0; c <= n; c++)
			mvaddch(y + r * (ch + 1), x + c * (cw + 1), joint(r, c, n));
}
