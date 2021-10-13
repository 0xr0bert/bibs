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
#include <gtest/gtest.h>

class MockAgent : public BIBS::IAgent {
  using IAgent::IAgent;
};

TEST(MockAgent, EmptyConstructor) {
  auto a1 = MockAgent();
  auto a2 = MockAgent();

  ASSERT_NE(a1.uuid, a2.uuid);
}

TEST(MockAgent, UUIDConstructor) {
  auto uuid = boost::uuids::random_generator_mt19937()();
  auto a = MockAgent(uuid);

  ASSERT_EQ(a.uuid, uuid);
}

TEST(Agent, EmptyConstructor) {
  auto a1 = BIBS::Agent();
  auto a2 = BIBS::Agent();

  ASSERT_NE(a1.uuid, a2.uuid);
}

TEST(Agent, UUIDConstructor) {
  auto uuid = boost::uuids::random_generator_mt19937()();
  auto a = BIBS::Agent(uuid);

  ASSERT_EQ(a.uuid, uuid);
}
