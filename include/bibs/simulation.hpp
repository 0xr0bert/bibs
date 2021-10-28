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
 * @file      simulation.hpp
 * @brief     Header of simulation.hpp
 * @date      Thu Oct 28 14:12:06 2021
 * @author    Robert Greener
 * @copyright GPL-3.0-or-later
 *
 * This module contains an ISimulation interface and a SequentialSimulation
 * implementation.
 */

#ifndef BIBS_SIMULATION_H
#define BIBS_SIMULATION_H

#include "bibs/agent.hpp"
#include "bibs/behaviour.hpp"
#include "bibs/belief.hpp"

#include <vector>

namespace BIBS {

/**
 * The interface for a simulation.
 */
class ISimulation {
public:
  /**
   * Destroy ISimulation.
   */
  virtual ~ISimulation() {}

  /**
   * Run the simulation for n days.
   */
  virtual void run(sim_time_t nDays) = 0;
};

/**
 * A sequential simulation (no multiprocessing).
 */
class SequentialSimulation : public ISimulation {
protected:
  /**
   * The agents in the simulation.
   */
  std::vector<IAgent *> agents;

  /**
   * The (const) agents in the simulation.
   */
  std::vector<const IAgent *> constAgents;

  /**
   * The beliefs in the simulation.
   */
  std::vector<IBelief *> beliefs;

  /**
   * The (const) beliefs in the simulation.
   */
  std::vector<const IBelief *> constBeliefs;

  /**
   * The behaviours in the simulation.
   */
  std::vector<IBehaviour *> behaviours;

  /**
   * The const behaviours in the simulation.
   */
  std::vector<const IBehaviour *> constBehaviours;

public:
  /**
   * Create a new sequential simulation
   *
   * @param agents The agents.
   * @param beliefs The beliefs.
   * @param behaviours The behaviours.
   */
  SequentialSimulation(std::vector<IAgent *> agents,
                       std::vector<IBelief *> beliefs,
                       std::vector<IBehaviour *> behaviours);

  /**
   * Run the simulation for n days.
   *
   * @param nDays the number of days.
   */
  virtual void run(sim_time_t nDays);
};
} // namespace BIBS

#endif // BIBS_SIMULATION_H
