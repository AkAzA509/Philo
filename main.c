/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:43:19 by ggirault          #+#    #+#             */
/*   Updated: 2025/02/18 11:55:30 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char *av[])
{
	if (ac < 6 || ac > 7)
	{
		write(2, "Error : wrong numbers of parameters\n", 36);
		return (0);
	}
	simulation(av, ac);
	return (0);
}

// 1 verifier si on a l'arguemnt optionnel
// 2 cree les threads
// 3 commencer la simulation
// 4 ??????


// les parametre a prendre : 1 nb de treads (autant de fourchette que de threads)
//                           2 le temps qui met a mourrir s'il ne mange pas en ms
//                           3 le temps quil met pour manger (il doit tenir2 fourchette)
//                           4 le temps quil passe a dormir en ms
//                           5 (le nb de fois que le philo doit manger si atteind fin)

// quand ils ne peuvent faire aucune actions ils pensent (dormir ou manger)