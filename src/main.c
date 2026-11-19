/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 09:53:15 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/19 14:33:47 by kseltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

static bool	is_arrow(int key)
{
	return (key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_UP || key == KEY_DOWN);
}

static t_dir	key_to_dir(int key)
{
	if (key == KEY_LEFT)
		return (DIR_LEFT);
	if (key == KEY_RIGHT)
		return (DIR_RIGHT);
	if (key == KEY_UP)
		return (DIR_UP);
	return (DIR_DOWN);
}

static int	wait_message(const char *msg)
{
	int	key;

	mvprintw(LINES - 1, 0, "%s", msg);
	refresh();
	key = ERR;
	while (!should_quit() && (key == ERR || key == KEY_RESIZE))
		key = getch();
	return (key);
}

static bool	handle_win(t_game *g)
{
	bool	was_won = g->win;

	check_win(g);
	if (!was_won && g->win)
		return (wait_message("You win! Any key to continue, ESC to quit.") == 27);
	return (false);
}

static void	show_game_over(void)
{
	wait_message("Game over! Press any key to quit.");
}

static int	uint_len(uint64_t i)
{
	int	ret = 0;

	while (i)
	{
		ret++;
		i /= 10;
	}
	return ret;
}

static int	max_value_len(t_game *g)
{
	int	max = 0;

	for (uint64_t i = 0; i < g->size; i++)
	{
		for (uint64_t j = 0; j < g->size; j++)
		{
			if (max < uint_len(g->grid[i][j]))
				max = uint_len(g->grid[i][j]);
		}
	}
	return max;
}

static bool	layout(t_game *g, bool art, bool square, int *cw, int *ch)
{
	int	digits = max_value_len(g);

	if (digits < 4)
		digits = 4;
	*cw = art ? digits * 3 + 2 : digits + 2;
	*ch = art ? 3 : 1;
	if (square)
	{
		int	h = ((*cw + 1) * CHAR_W + CHAR_H / 2) / CHAR_H - 1;

		if (h > *ch)
			*ch = h;
	}
	return (COLS >= (int)g->size * (*cw + 1) + 1
		&& LINES >= (int)g->size * (*ch + 1) + 2);
}

static void	draw(t_game *g)
{
	int		cw;
	int		ch;
	bool	art = true;

	erase();
	if (!layout(g, true, true, &cw, &ch))
	{
		art = false;
		if (!layout(g, false, true, &cw, &ch)
			&& !layout(g, false, false, &cw, &ch))
		{
			const char	*msg = "Terminal too small";
			int			x = (COLS - (int)ft_strlen(msg)) / 2;

			mvprintw(LINES / 2, x < 0 ? 0 : x, "%s", msg);
			refresh();
			return ;
		}
	}
	int	grid_w = g->size * (cw + 1) + 1;
	int	grid_h = g->size * (ch + 1) + 1;
	int	top = (LINES - (grid_h + 1)) / 2;
	int	left = (COLS - grid_w) / 2;

	for (uint64_t r = 0; r <= g->size; r++)
	{
		int	y = top + r * (ch + 1);

		for (int x = 0; x < grid_w; x++)
			mvaddch(y, left + x, (x % (cw + 1) == 0) ? '+' : '-');
		if (r == g->size)
			break ;
		for (int k = 1; k <= ch; k++)
			for (uint64_t c = 0; c <= g->size; c++)
				mvaddch(y + k, left + c * (cw + 1), '|');
	}
	for (uint64_t r = 0; r < g->size; r++)
	{
		for (uint64_t c = 0; c < g->size; c++)
		{
			uint64_t	v = g->grid[r][c];
			int			y = top + r * (ch + 1) + 1;
			int			x0 = left + 1 + c * (cw + 1);
			int			len = uint_len(v);

			if (!v)
				continue ;
			if (has_colors())
				attron(COLOR_PAIR(tile_pair(v)) | A_BOLD);
			for (int k = 0; k < ch; k++)
				mvprintw(y + k, x0, "%*s", cw, "");
			if (art)
				draw_art(y + (ch - 3) / 2, x0 + (cw - len * 3) / 2, v, len);
			else
				mvprintw(y + ch / 2, x0 + (cw - len) / 2, "%" PRIu64, v);
			if (has_colors())
				attroff(COLOR_PAIR(tile_pair(v)) | A_BOLD);
		}
	}

	uint64_t	*best = &g->best[g->size - 4];

	if (g->score > *best)
		*best = g->score;
	mvprintw(top + grid_h, left, "Score: %" PRIu64 "   Best: %" PRIu64,
		g->score, *best);

	refresh();
}

int	main(void)
{
	t_game	g = {0};
	int		key;

	srand(time(NULL));

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	init_colors();
	set_escdelay(25);
	timeout(100);
	init_signals();
	load_best(g.best);

	g.size = menu();
	if (!g.size)
	{
		endwin();
		return (0);
	}
	spawn_tile(&g);
	spawn_tile(&g);
	draw(&g);
	if (!handle_win(&g))
	{
		while (!should_quit())
		{
			key = getch();
			if (key == ERR)
				continue ;
			if (key == 27)
				break ;
			if (is_arrow(key) && move_board(&g, key_to_dir(key)))
			{
				spawn_tile(&g);
				draw(&g);
				if (handle_win(&g))
					break ;
				if (!can_move(&g))
				{
					show_game_over();
					break ;
				}
			}
			else
				draw(&g);
		}
	}
	save_best(g.best);
	endwin();
	return (0);
}
