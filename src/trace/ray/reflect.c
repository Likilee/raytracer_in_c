/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:56:03 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 13:57:31 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

/*
** v - 2 * dot(v, n) * n;
*/

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}
