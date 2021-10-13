/* BIBS, the belief-induced behaviour simulation
 * Copyright (C) 2021 Robert Greener
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file      bibs.hpp
 * @brief     Header of bibs.cpp
 * @date      Wed Oct 13 14:41:21 2021
 * @author    Robert Greener
 * @copyright GPL-3.0-or-later
 *
 * This module currently only contains a squareRoot function as a demo...
 */

#ifndef BIBS_BIBS_H
#define BIBS_BIBS_H

/**
 * @brief Square root a number.
 * @details Square roots n.
 * @param n The number to square root.
 * @return -1.0 if NaN, sqrt(n) otherwise.
 */
double squareRoot(double n);

#endif // BIBS_BIBS_H
