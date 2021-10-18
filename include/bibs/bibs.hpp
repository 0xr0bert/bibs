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
 * This module contains a top-level typedef for sim_time_t.
 */

#ifndef BIBS_BIBS_H
#define BIBS_BIBS_H

#include <cstdint>

/**
 * BIBS is the belief-induced behaviour simulation.
 *
 * This namespace contains a number of classes used to create your own
 * belief-induced behaviour simulation.
 */
namespace BIBS {
/**
 * Time in the simulations -- ticks since start.
 */
typedef uint32_t sim_time_t;
} // namespace BIBS

#endif // BIBS_BIBS_H
