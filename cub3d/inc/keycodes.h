/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:02:19 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 08:22:22 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H
# ifdef __linux__
#  define KEY_Q 113
#  define KEY_W 119
#  define KEY_E 101
#  define KEY_R 114
#  define KEY_T 116
#  define KEY_Y 121
#  define KEY_U 117
#  define KEY_I 105
#  define KEY_O 111
#  define KEY_P 112
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_F 102
#  define KEY_G 103
#  define KEY_H 104
#  define KEY_J 106
#  define KEY_K 107
#  define KEY_L 108
#  define KEY_Z 122
#  define KEY_X 120
#  define KEY_C 99
#  define KEY_V 118
#  define KEY_B 98
#  define KEY_N 110
#  define KEY_M 109
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307
#  define KEY_SHIFT 65505
# else
#  define KEY_Q 12
#  define KEY_W 13
#  define KEY_E 14
#  define KEY_R 15
#  define KEY_T 17
#  define KEY_Y 16
#  define KEY_U 32
#  define KEY_I 34
#  define KEY_O 31
#  define KEY_P 35
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_F 3
#  define KEY_G 5
#  define KEY_H 4
#  define KEY_J 38
#  define KEY_K 40
#  define KEY_L 37
#  define KEY_Z 6
#  define KEY_X 7
#  define KEY_C 8
#  define KEY_V 9
#  define KEY_B 11
#  define KEY_N 45
#  define KEY_M 46
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
#  define KEY_SHIFT 257
# endif
#endif
