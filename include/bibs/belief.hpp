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
#include <map>
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

  /**
   * The relationship between beliefs.
   *
   * @param b2 The other belief.
   * @returns The relationship between this belief and b2, given that you
   *   already hold this.
   */
  virtual double beliefRelationship(const IBelief *b2) const = 0;

  /**
   * Set the relationship between beliefs.
   *
   * @param b2 The other belief.
   * @param value The relationship between this belief and b2, given that you
   *   already hold this.
   */
  virtual void setBeliefRelationship(const IBelief *b2, const double value) = 0;
};

/**
 * A belief in the simulation.
 */
class Belief : public IBelief {
  using IBelief::IBelief;

private:
  /**
   * The map used for storing belief relationships.
   * From const IBelief* to the relationship.
   */
  std::map<const IBelief *, double> beliefRelationshipMap;

public:
  /**
   * The relationship between beliefs.
   *
   * @param b2 The other belief.
   * @returns The relationship between this belief and b2, given that you
   *   already hold this.
   * @exception std::out_of_range If the belief is not found.
   */
  double beliefRelationship(const IBelief *b2) const override;

  /**
   * Set the relationship between beliefs.
   *
   * @param b2 The other belief.
   * @param value The relationship between this belief and b2, given that you
   *   already hold this.
   */
  void setBeliefRelationship(const IBelief *b2, const double value) override;
};
} // namespace BIBS

#endif // BIBS_BELIEF_H
