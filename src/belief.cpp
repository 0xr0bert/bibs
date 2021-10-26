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

BIBS::IBelief::IBelief(const std::string name)
    : BIBS::IBelief(name, boost::uuids::random_generator_mt19937()()) {}

BIBS::IBelief::IBelief(const std::string name, const boost::uuids::uuid uuid)
    : name(name), uuid(uuid) {}

double BIBS::Belief::beliefRelationship(const IBelief *b2) const { return 0.0; }

void BIBS::Belief::setBeliefRelationship(const IBelief *b2,
                                         const double value) {}
