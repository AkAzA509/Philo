/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:43:19 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/24 10:57:07 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char *av[])
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Error : wrong numbers of parameters\n", 36);
		return (0);
	}
	init_stack(av, ac);
	return (0);
}