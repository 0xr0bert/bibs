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
 * @file      agent.hpp
 * @brief     Header of agent.cpp
 * @date      Wed Oct 13 17:43:34 2021
 * @author    Robert Greener
 * @copyright GPL-3.0-or-later
 *
 * This module contains an IAgent interface and an Agent implementation.
 */

#ifndef BIBS_AGENT_H
#define BIBS_AGENT_H

#include <boost/uuid/uuid.hpp>

namespace BIBS {
/**
 * The interface for an agent in the simulation.
 */
class IAgent {
public:
  /**
   * Destroy IAgent.
   */
  virtual ~IAgent() {}

  /**
   * The UUID of the agent.
   */
  const boost::uuids::uuid uuid;

  /**
   * Create a new IAgent.
   *
   * The UUID is generated using a Mersenne Twister.
   */
  IAgent();

  /**
   * Create a new IAgent.
   *
   * @param uuid The UUID of the IAgent.
   */
  IAgent(const boost::uuids::uuid uuid);
};

/**
 * An agent in the simulation
 */
class Agent : public IAgent {
  using IAgent::IAgent;
};
} // namespace BIBS

#endif // BIBS_AGENT_H
