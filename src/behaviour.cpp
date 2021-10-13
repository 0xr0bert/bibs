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

#include "bibs/behaviour.hpp"

#include <boost/uuid/uuid_generators.hpp>

using namespace BIBS;

IBehaviour::IBehaviour(const std::string name)
    : IBehaviour::IBehaviour(name, boost::uuids::random_generator_mt19937()()) {
}

IBehaviour::IBehaviour(const std::string name, boost::uuids::uuid uuid)
    : name(name), uuid(uuid) {}
