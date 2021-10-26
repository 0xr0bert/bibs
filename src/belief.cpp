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

#include "bibs/belief.hpp"

#include <boost/uuid/uuid_generators.hpp>
#include <stdexcept>

BIBS::IBelief::IBelief(const std::string name)
    : BIBS::IBelief(name, boost::uuids::random_generator_mt19937()()) {}

BIBS::IBelief::IBelief(const std::string name, const boost::uuids::uuid uuid)
    : name(name), uuid(uuid) {}

double BIBS::Belief::beliefRelationship(const IBelief *b2) const {
  return beliefRelationshipMap.at(b2);
}

void BIBS::Belief::setBeliefRelationship(const IBelief *b2,
                                         const double value) {
  beliefRelationshipMap.insert_or_assign(b2, value);
}

double
BIBS::Belief::observedBehaviourRelationship(const IBehaviour *beh) const {
  return observedBehaviourRelationshipMap.at(beh);
}

void BIBS::Belief::setObservedBehaviourRelationship(const IBehaviour *beh,
                                                    const double value) {
  observedBehaviourRelationshipMap.insert_or_assign(beh, value);
}

double
BIBS::Belief::performingBehaviourRelationship(const IBehaviour *beh) const {
  throw std::logic_error("Not implemented");
}

void BIBS::Belief::setPerformingBehaviourRelationship(const IBehaviour *beh,
                                                      const double value) {
  throw std::logic_error("Not implemented");
}
