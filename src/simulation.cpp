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

#include "bibs/simulation.hpp"
#include "bibs/agent.hpp"
#include "bibs/behaviour.hpp"
#include "bibs/bibs.hpp"
#include <iterator>
#include <stdexcept>
#include <vector>

BIBS::SequentialSimulation::SequentialSimulation(
    std::vector<IAgent *> agents, std::vector<IBelief *> beliefs,
    std::vector<IBehaviour *> behaviours)
    : agents(agents), beliefs(beliefs), behaviours(behaviours) {
  std::copy(agents.begin(), agents.end(), std::back_inserter(constAgents));
  std::copy(beliefs.begin(), beliefs.end(), std::back_inserter(constBeliefs));
  std::copy(behaviours.begin(), behaviours.end(),
            std::back_inserter(constBehaviours));
}

void BIBS::SequentialSimulation::run(sim_time_t nDays) {
  for (sim_time_t t = 0; t < nDays; ++t) {
    for (auto &agent : agents) {
      agent->tick(t, constBehaviours, constBeliefs);
    }
  }
}
