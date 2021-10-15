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
 * @file      belief.hpp
 * @brief     Header of belief.cpp
 * @date      Wed Oct 13 16:27:57 2021
 * @author    Robert Greener
 * @copyright GPL-3.0-or-later
 *
 * This module contains an interface for a belief and an implementation.
 */

#ifndef BIBS_BELIEF_H
#define BIBS_BELIEF_H

#include <boost/uuid/uuid.hpp>
#include <string>

namespace BIBS {
/**
 * The interface for a belief in the simulation
 */
class IBelief {
public:
  /**
   * Destruct IBelief.
   */
  virtual ~IBelief(){};

  /**
   * The name of the belief.
   */
  const std::string name;

  /**
   * The UUID of the belief.
   */
  const boost::uuids::uuid uuid;

  /**
   * Create a new IBelief.
   *
   * uuid is randomly generated using a Mersenne Twister.
   *
   * @param name The name of the belief.
   */
  explicit IBelief(const std::string name);

  /**
   * Create a new IBelief.
   *
   * @param name The name of the belief.
   * @param uuid The UUID of the belief.
   */
  explicit IBelief(const std::string name, const boost::uuids::uuid uuid);
};

/**
 * A belief in the simulation.
 */
class Belief : public IBelief {
  using IBelief::IBelief;
};
} // namespace BIBS

#endif // BIBS_BELIEF_H
