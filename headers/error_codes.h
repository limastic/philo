/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:39:30 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/19 17:33:51 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODES_H
# define ERROR_CODES_H

# define WRONG_N 	"Error: Wrong number of args! Expected 4 or 5 args\n"
# define WRONG_F 	"Error: Wrong args format! \
Expected numbers (between 1 and 2147483647)\n"
# define E_C_GMT	"Error: could not init global mutex\n"
# define E_C_MT		"Error: could not init mutex %li\n"
# define E_C_TH 	"Error: could not create thread %li\n"
# define E_W_TH		"Error: could not wait for thread %li\n"

#endif