/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 13:54:44 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/20 22:35:15 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

static const char	*g_title[TITLE_H] = {
	"  _______  ________  ___   ___  ________     ",
	" /  ___  \\|\\   __  \\|\\  \\ |\\  \\|\\   __  \\    ",
	"/__/|_/  /\\ \\  \\|\\  \\ \\  \\\\_\\  \\ \\  \\|\\  \\   ",
	"|__|//  / /\\ \\  \\\\\\  \\ \\______  \\ \\   __  \\  ",
	"    /  /_/__\\ \\  \\\\\\  \\|_____|\\  \\ \\  \\|\\  \\ ",
	"   |\\________\\ \\_______\\     \\ \\__\\ \\_______\\",
	"    \\|_______|\\|_______|      \\|__|\\|_______|",
};

static void	draw_title(int y)
{
	int	x = (COLS - TITLE_W) / 2;

	for (int i = 0; i < TITLE_H; i++)
		mvaddstr(y + i, x, g_title[i]);
}

static void	draw_menu(int y, int sel, const char **items)
{
	int	x = (COLS - BOX_W) / 2;
	int	row;

	draw_grid(y, x, 1, BOX_INNER, BOX_H - 2);
	for (int i = 0; i < MENU_COUNT; i++)
	{
		row = y + 1 + BOX_PAD + i;
		mvaddstr(row, x + 1 + (BOX_INNER - (int)ft_strlen(items[i])) / 2,
				items[i]);
		if (i == sel)
			mvchgat(row, x + 1, BOX_INNER, A_REVERSE, 0, NULL);
	}
}

uint64_t	menu(void)
{
	static const char	*items[MENU_COUNT] = {"Play 4x4", "Play 5x5", "Quit"};
	int					sel = 0;
	int					key = ERR;
	int					y = 0;

	for (int t = 0; !should_quit() && (key == ERR || key == KEY_RESIZE); t++)
	{
		y = (LINES - SPLASH_H) / 2;
		erase();
		draw_title(y);
		if (t / BLINK_TICKS % 2 == 0)
			mvaddstr(y + TITLE_H + TITLE_GAP,
					(COLS - (int)ft_strlen(PROMPT)) / 2, PROMPT);
		refresh();
		key = getch();
	}
	if (key == KEY_ESC)
		return (0);
	for (; y > (LINES - MENU_H) / 2; y--)
	{
		erase();
		draw_title(y);
		refresh();
		napms(SLIDE_MS);
	}
	while (!should_quit())
	{
		erase();
		draw_title(y);
		draw_menu(y + TITLE_H + TITLE_GAP, sel, items);
		refresh();

		key = getch();
		if (key == KEY_ESC)
			return (0);
		if (key == KEY_UP)
			sel = (sel + MENU_COUNT - 1) % MENU_COUNT;
		else if (key == KEY_DOWN)
			sel = (sel + 1) % MENU_COUNT;
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
