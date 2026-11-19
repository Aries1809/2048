/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 13:54:44 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/19 13:58:31 by kseltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

uint64_t	menu(void)
{
	static const char	*items[] = {"Play 4x4", "Play 5x5", "Quit"};
	const int			count = 3;
	int					sel = 0;
	int					key;

	while (!should_quit())
	{
		erase();
		int	top = LINES / 2 - count;
		mvprintw(top - 2, (COLS - 4) / 2, "2048");
		for (int i = 0; i < count; i++)
		{
			int	x = (COLS - (int)strlen(items[i]) - 4) / 2;

			if (i == sel)
				attron(A_REVERSE);
			mvprintw(top + i * 2, x < 0 ? 0 : x, "  %s  ", items[i]);
			if (i == sel)
				attroff(A_REVERSE);
		}
		refresh();

		key = getch();
		if (key == 27)
			return (0);
		if (key == KEY_UP)
			sel = (sel + count - 1) % count;
		else if (key == KEY_DOWN)
			sel = (sel + 1) % count;
		else if (key == '\n' || key == KEY_ENTER)
		{
			if (sel == 0)
				return (4);
			if (sel == 1)
				return (5);
			return (0);
		}
	}
	return (0);
}
