/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 09:11:29 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/19 09:11:41 by kseltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

int32_t	slide_line(uint64_t *line, uint64_t size, uint64_t *score);

static void	check(uint64_t in[4], uint64_t want[4])
{
	uint64_t	score = 0;
	uint64_t	l[4];

	memcpy(l, in, sizeof(l));
	slide_line(l, 4, &score);
	printf("%s [%"PRIu64",%"PRIu64",%"PRIu64",%"PRIu64"]\n",
		memcmp(l, want, sizeof(l)) ? "KO" : "OK",
		l[0], l[1], l[2], l[3]);
}

int	main(void)
{
	check((uint64_t[]){2,2,2,2}, (uint64_t[]){4,4,0,0});
	check((uint64_t[]){2,2,4,0}, (uint64_t[]){4,4,0,0});
	check((uint64_t[]){4,0,0,4}, (uint64_t[]){8,0,0,0});
	check((uint64_t[]){2,2,2,0}, (uint64_t[]){4,2,0,0});
	check((uint64_t[]){0,0,0,2}, (uint64_t[]){2,0,0,0});
	check((uint64_t[]){2,4,8,16}, (uint64_t[]){2,4,8,16});
	return (0);
}
