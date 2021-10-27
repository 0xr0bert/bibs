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

#include "bibs/behaviour.hpp"
#include "bibs/belief.hpp"
#include "bibs/bibs.hpp"

#include <boost/uuid/uuid.hpp>
#include <map>

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
   * @param uuid The UUID of the IAgent.
   */
  explicit IAgent(const boost::uuids::uuid uuid);

  /**
   * Gets the activation of a belief at a time.
   *
   * @param t The time.
   * @param b The belief.
   * @return The activation.
   */
  virtual double activation(const sim_time_t t, const IBelief *b) const = 0;

  /**
   * Gets the behaviour of the agent at a time.
   *
   * @param t The time.
   * @return The performed behaviour.
   */
  virtual const IBehaviour *performed(const sim_time_t t) const = 0;
};

/**
 * An agent in the simulation.
 */
class Agent : public IAgent {
private:
  /**
   * A map from time to another map of IBelief * to activation.
   */
  std::map<sim_time_t, std::map<const IBelief *, double>> activationMap;

  /**
   * A map from time to the performed behaviour.
   */
  std::map<sim_time_t, const IBehaviour *> performedMap;

  /**
   * The weights in social networks of agents
   */
  std::map<const IAgent *, double> friends;

  /**
   * The time deltas.
   */
  std::map<const IBelief *, double> timeDeltaMap;

public:
  /**
   * Create a new Agent.
   *
   * The UUID is generated using a Mersenne Twister.
   */
  explicit Agent();

  /**
   * Create a new Agent.
   *
   * @param uuid The UUID of the Agent.
   */
  explicit Agent(const boost::uuids::uuid uuid);

  /**
   * Create a new Agent.
   *
   * @param activationMap The activation from time -> (belief -> activation).
   */
  explicit Agent(const std::map<sim_time_t, std::map<const IBelief *, double>>
                     activationMap);

  /**
   * Create a new Agent.
   *
   * @param uuid The UUID of the Agent.
   * @param activationMap The activation from time -> (belief -> activation).
   */
  explicit Agent(const boost::uuids::uuid uuid,
                 const std::map<sim_time_t, std::map<const IBelief *, double>>
                     activationMap);

  /**
   * Gets the activation of a belief at a time.
   *
   * @param t The time.
   * @param b The belief.
   * @return The activation.
   * @exception std::out_of_range If the time or belief not found.
   */
  double activation(const sim_time_t t, const IBelief *b) const override;

  /**
   * Gets the behaviour of the agent at a time.
   *
   * @param t The time.
   * @return The performed behaviour.
   */
  const IBehaviour *performed(const sim_time_t t) const override;

  /**
   * Adds a behaviour to the performedMap.
   * Used only for testing.
   *
   * @private
   * @param t The time.
   * @param b The behaviour.
   */
  void _addPerformed(const sim_time_t t, const IBehaviour *b);

  /**
   * Gets the weight of relationship between this agent and another agent a.
   *
   * @param a The other agent.
   * @return The weight of relationship.
   * @exception std::out_of_range if this agent is not friends with a.
   */
  double friendWeight(const IAgent *a) const;

  /**
   * Sets the weight of relationship between this agent and another agent a.
   *
   * @param a The other agent.
   * @param w The new weight.
   */
  void setFriendWeight(const IAgent *a, double w);

  /**
   * The amount the activation of b changes (multiplicative) at each time step.
   *
   * @param b The belief.
   * @return The amount the activation of b changes (multiplicative) at each
   * time step.
   * @exception std::out_of_range If the belief is not found.
   */
  virtual double timeDelta(const IBelief *b) const;

  /**
   * Set the amount the activation of b changes (multiplicative) at each time
   * step.
   *
   * @param b The belief.
   * @param td The new time delta.
   */
  void setTimeDelta(const IBelief *b, const double td);

protected:
  /**
   * Calculates and returns the value of observing behaviour relevant to belief
   * b at time t.
   *
   * @param b The belief.
   * @param t The time.
   * @return The value of observing relevant behaviour.
   */
  virtual double observed(const IBelief *b, const sim_time_t t) const;

  /**
   * Put something into context of the other beliefs held.
   *
   * @param b The belief to put into context.
   * @param t The time.
   * @return The weight used to put into context.
   */
  virtual double contextualise(const IBelief *b, const sim_time_t t) const;

  /**
   * Calculates and returns the value of observing behaviour relevant to belief
   * b at time t, taking into context the beliefs this agent holds.
   *
   * @param b The belief.
   * @param t The time.
   * @return The contextual value of observing relevant behaviour.
   */
  virtual double contextualObserved(const IBelief *b, const sim_time_t t) const;
};
} // namespace BIBS

#endif // BIBS_AGENT_H
