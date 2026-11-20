/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 09:53:15 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/20 23:40:18 by sancuta          ###   ########.fr       */
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
	int	x;
	int	y;

	y = LINES / 2;
	x = (COLS - ft_strlen(msg)) / 2;
	if (x < 0)
		x = 0;
	mvprintw(y, x, "%s", msg);
	refresh();
	key = ERR;
	while (!should_quit() && (key == ERR || key == KEY_RESIZE))
		key = getch();
	return (key);
}

static void	warning_message(const char *msg)
{
	int	key;

	move(LINES - 1, 0);
	clrtoeol();
	mvprintw(LINES - 1, 0, "%s", msg);
	refresh();
	key = ERR;
	while (!should_quit() && (key == ERR || key == KEY_RESIZE))
		key = getch();
}

static bool	handle_win(t_game *g)
{
	bool	was_won = g->win;

	check_win(g);
	if (!was_won && g->win)
		return (wait_message("You win! Any key to continue, ESC to quit.") == KEY_ESC);
	return (false);
}

static void	show_game_over(void)
{
	wait_message("Game over! Press any key to quit.");
}

static int	uint_len(uint64_t i)
{
	int	ret = 1;

	while (i >= 10)
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

static int	clamp(int v, int lo, int hi)
{
	return v < lo ? lo : v > hi ? hi : v;
}

static bool	layout(t_game *g, bool art, int *cw, int *ch)
{
	int	n = (int)g->size;
	int	digits = clamp(max_value_len(g), MIN_DIGITS, MAX_DIGITS);
	int	min_h = art ? ART_DIGIT_H : 1;
	int	min_w = art ? digits * ART_DIGIT_W + CELL_PAD : digits + CELL_PAD;
	int	fit_w = (COLS - MARGIN_X - FRAME) / n - CELL_BORDER;
	int	fit_h = (LINES - SCORE_GAP - SCORE_LINE_H - MIN_MARGIN_Y - FRAME) / n
		- CELL_BORDER;

	if (fit_w < min_w || fit_h < min_h)
		return false;
	*cw = art ? min_w
		: ((fit_h + CELL_BORDER) * CHAR_H + CHAR_W / 2) / CHAR_W
		- CELL_BORDER;
	*cw = clamp(*cw, min_w, fit_w);
	*ch = ((*cw + CELL_BORDER) * CHAR_W + CHAR_H / 2) / CHAR_H - CELL_BORDER;
	*ch = clamp(*ch, min_h, fit_h);
	return true;
}

static void draw_outer_frame(int top, int left, int w, int h)
{
	mvaddch(top, left, ACS_ULCORNER);
	for (int x = 1; x < w - 1; x++)
		mvaddch(top, left + x, ACS_HLINE);
	mvaddch(top, left + w - 1, ACS_URCORNER);

	for (int y = 1; y < h - 1; y++) {
		mvaddch(top + y, left, ACS_VLINE);
		mvaddch(top + y, left + w - 1, ACS_VLINE);
	}

	mvaddch(top + h - 1, left, ACS_LLCORNER);
	for (int x = 1; x < w - 1; x++)
		mvaddch(top + h - 1, left + x, ACS_HLINE);
	mvaddch(top + h - 1, left + w - 1, ACS_LRCORNER);
}

static void draw_cell_top(int y, int x, int cw)
{
	mvaddch(y, x, ACS_ULCORNER);
	for (int i = 1; i <= cw; i++)
		mvaddch(y, x + i, ACS_HLINE);
	mvaddch(y, x + cw + 1, ACS_URCORNER);
}

static void draw_cell_bottom(int y, int x, int cw)
{
	mvaddch(y, x, ACS_LLCORNER);
	for (int i = 1; i <= cw; i++)
		mvaddch(y, x + i, ACS_HLINE);
	mvaddch(y, x + cw + 1, ACS_LRCORNER);
}

static void draw(t_game *g)
{
	int		cw;
	int		ch;
	bool	art = true;

	if (!layout(g, art, &cw, &ch))
	{
		art = false;
		if (!layout(g, art, &cw, &ch))
		{
			erase();
			const char	*msg = "Terminal too small";
			int	x = (COLS - (int)ft_strlen(msg)) / 2;
			mvprintw(LINES / 2, x < 0 ? 0 : x, "%s", msg);
			refresh();
			return;
		}
	}

	int	grid_w = (int)g->size * (cw + CELL_BORDER) + FRAME;
	int	grid_h = (int)g->size * (ch + CELL_BORDER) + FRAME;
	int	top = (LINES - (grid_h + SCORE_GAP + SCORE_LINE_H)) / 2;
	int	left = (COLS - grid_w) / 2;
	if (top < 0)  top  = 0;
	if (left < 0) left = 0;

	erase();
	draw_outer_frame(top, left, grid_w, grid_h);

	for (uint64_t r = 0; r < g->size; r++)
	{
		for (uint64_t c = 0; c < g->size; c++)
		{
			uint64_t v = g->grid[r][c];
			int	len = uint_len(v);
			int	cx = left + 1 + (int)c * (cw + CELL_BORDER);
			int	cy = top  + 1 + (int)r * (ch + CELL_BORDER);

			draw_cell_top(cy, cx, cw);

			for (int k = 1; k <= ch; k++)
			{
				mvaddch(cy + k, cx, ACS_VLINE);
				if (v && has_colors())
					attron(COLOR_PAIR(tile_pair(v)) | A_BOLD);
				for (int i = 1; i <= cw; i++)
					mvaddch(cy + k, cx + i, ' ');
				if (v && has_colors())
					attroff(COLOR_PAIR(tile_pair(v)) | A_BOLD);
				mvaddch(cy + k, cx + cw + 1, ACS_VLINE);
			}
			draw_cell_bottom(cy + ch + 1, cx, cw);

			if (!v)
				continue;

			if (has_colors())
				attron(COLOR_PAIR(tile_pair(v)) | A_BOLD);
			if (art)
				draw_art(cy + 1 + (ch - ART_DIGIT_H) / 2,
						cx + 1 + (cw - len * ART_DIGIT_W) / 2, v, len);
			else
				mvprintw(cy + 1 + (ch - 1) / 2,
						cx + 1 + (cw - len) / 2, "%" PRIu64, v);
			if (has_colors())
				attroff(COLOR_PAIR(tile_pair(v)) | A_BOLD);
		}
	}

	uint64_t	*best = &g->best[g->size - 4];
	if (g->score > *best)
		*best = g->score;
	mvprintw(top + grid_h + SCORE_GAP, left,
			"Score: %" PRIu64 "   Best: %" PRIu64, g->score, *best);
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
	mousemask(ALL_MOUSE_EVENTS, NULL);
	curs_set(0);
	init_colors();
	set_escdelay(25);
	timeout(100);
	init_signals();

	if (!load_best(g.best))
		warning_message("Warning: couldn't load high scores. Press any key to continue.");

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
			if (key == KEY_ESC)
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
	if (!save_best(g.best))
		warning_message("Warning: couldn't save high scores. Press any key to exit.");
	endwin();
	return (0);
}
