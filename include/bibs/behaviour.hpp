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
 * @file      behaviour.hpp
 * @brief     Header of behaviour.cpp
 * @date      Wed Oct 13 15:27:09 2021
 * @author    Robert Greener
 * @copyright GPL-3.0-or-later
 *
 * This module contains a single Behaviour class and an IBehaviour interface.
 */

#ifndef BIBS_BEHAVIOUR_H
#define BIBS_BEHAVIOUR_H

#include <boost/uuid/uuid.hpp>
#include <string>

namespace BIBS {

/**
 * The interface for a behaviour which can be performed
 */
class IBehaviour {
public:
  /**
   * The name of the behaviour.
   */
  const std::string name;

  /**
   * The UUID of the behaviour
   */
  const boost::uuids::uuid uuid;

  /**
   * Destruct IBehaviour.
   */
  virtual ~IBehaviour() {}

  /**
   * Creates a new behaviour.
   *
   * @param name The name of the new behaviour.
   */
  explicit IBehaviour(const std::string name);

  /**
   * Creates a new behaviour
   *
   * @param name The name of the new behaviour.
   * @param uuid The UUID of the new behaviour.
   */
  explicit IBehaviour(const std::string name, const boost::uuids::uuid uuid);
};

/**
 * A behaviour which can be performed.
 */
class Behaviour : public IBehaviour {
  using IBehaviour::IBehaviour;
};
} // namespace BIBS

#endif // BIBS_BEHAVIOUR_H
