/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wkw.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:48:59 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/20 23:13:10 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WKW_H
# define WKW_H

# define MAX_SIZE 5

# define CHAR_W 11
# define CHAR_H 26

# include <stdint.h>
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <ncurses.h>
# include <time.h>
# include <inttypes.h>
# include <string.h>

# define ART_DIGIT_W	3
# define ART_DIGIT_H	3
# define CELL_PAD		2
# define CELL_BORDER	2
# define MIN_DIGITS		4
# define MAX_DIGITS		8

# define FRAME			2
# define MARGIN_X		2
# define SCORE_GAP		1
# define SCORE_LINE_H	1
# define MIN_MARGIN_Y	1

# define TITLE_H		7
# define TITLE_W		48
# define TITLE_GAP		2
# define PROMPT			"press any key"
# define BLINK_TICKS	5
# define SLIDE_MS		40
# define MENU_COUNT		3
# define BOX_W			18
# define BOX_PAD		1
# define BOX_H			(MENU_COUNT + 2 * BOX_PAD + 2)
# define BOX_INNER		(BOX_W - 2)
# define SPLASH_H		(TITLE_H + TITLE_GAP + 1)
# define MENU_H			(TITLE_H + TITLE_GAP + BOX_H)
# define KEY_ESC		27

enum	e_const
{
	WIN_VALUE = 2048,
};

typedef enum e_dir
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
}	t_dir;

typedef struct	s_game
{
	uint64_t	grid[MAX_SIZE][MAX_SIZE];
	uint64_t	size;
	uint64_t	score;
	bool		win;
	uint64_t	best[2];
}	t_game;

/* SLIDE.C */
int32_t	slide_line(uint64_t *line, uint64_t size, uint64_t *score);
int32_t	move_board(t_game *g, t_dir dir);

/* SIGNALS.C */
void	init_signals(void);
bool	should_quit(void);

/* GAME.C */
void	check_win(t_game *g);
bool	can_move(t_game *g);
void	spawn_tile(t_game *g);

/* COLORS.C */
void	init_colors(void);
short	tile_pair(uint64_t v);

/* MENU.C */

uint64_t	menu(void);

/* BEST.C */
bool	load_best(uint64_t best[2]);
bool	save_best(uint64_t best[2]);

/* ASCII.C */
void	draw_art(int y, int x, uint64_t v, int len);

/* GRID.C */
void	draw_grid(int y, int x, int n, int cw, int ch);

/* FT_STRLEN.C */
size_t	ft_strlen(const char *s);

#endif
