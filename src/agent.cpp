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

#include "bibs/agent.hpp"

#include <boost/uuid/uuid_generators.hpp>

BIBS::IAgent::IAgent(const boost::uuids::uuid uuid) : uuid(uuid) {}

BIBS::Agent::Agent()
    : BIBS::Agent(boost::uuids::random_generator_mt19937()()) {}

BIBS::Agent::Agent(const boost::uuids::uuid uuid) : BIBS::IAgent(uuid) {}

BIBS::Agent::Agent(
    const std::map<sim_time_t, std::map<const IBelief *, double>> activationMap)
    : BIBS::IAgent(boost::uuids::random_generator_mt19937()()),
      activationMap(activationMap) {}

BIBS::Agent::Agent(
    const boost::uuids::uuid uuid,
    std::map<sim_time_t, std::map<const IBelief *, double>> activationMap)
    : BIBS::IAgent(uuid), activationMap(activationMap) {}

double BIBS::Agent::activation(const sim_time_t t, const IBelief *b) const {
  return this->activationMap.at(t).at(b);
}

const BIBS::IBehaviour *BIBS::Agent::performed(const sim_time_t t) const {
  return nullptr;
}
