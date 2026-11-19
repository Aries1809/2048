/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:05:55 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/19 14:06:39 by kseltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"
#include <fcntl.h>
#include <unistd.h>

#define BEST_FILE ".2048_best"

void	load_best(uint64_t best[2])
{
	int	fd;

	best[0] = 0;
	best[1] = 0;
	fd = open(BEST_FILE, O_RDONLY);
	if (fd < 0)
		return ;
	if (read(fd, best, sizeof(uint64_t) * 2) != sizeof(uint64_t) * 2)
	{
		best[0] = 0;
		best[1] = 0;
	}
	close(fd);
}

void	save_best(uint64_t best[2])
{
	int	fd;

	fd = open(BEST_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	write(fd, best, sizeof(uint64_t) * 2);
	close(fd);
}
