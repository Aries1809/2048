/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 13:38:25 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/20 19:44:45 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

void	init_colors(void)
{
	static const short	bg256[] = {
		0, 255, 223, 215, 209, 203, 196, 228, 227, 226, 220, 214, 160
	};
	static const short	bg8[] = {
		0, COLOR_WHITE, COLOR_YELLOW, COLOR_RED, COLOR_RED, COLOR_MAGENTA,
		COLOR_MAGENTA, COLOR_BLUE, COLOR_BLUE, COLOR_CYAN, COLOR_CYAN,
		COLOR_GREEN, COLOR_GREEN
	};

	if (!has_colors())
		return ;
	start_color();
	use_default_colors();
	for (short i = 1; i <= 12; i++)
	{
		if (COLORS >= 256)
			init_pair(i, 235, bg256[i]);
		else
			init_pair(i, COLOR_BLACK, bg8[i]);
	}
}

short	tile_pair(uint64_t v)
{
	short	n = 0;

	while (v > 1 && n < 12)
	{
		v >>= 1;
		n++;
	}
	return (n);
}
