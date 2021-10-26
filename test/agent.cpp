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
#include "bibs/belief.hpp"

#include <boost/uuid/uuid_generators.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

class MockAgent : public BIBS::IAgent {
  using IAgent::IAgent;

  MOCK_METHOD(double, activation,
              (const BIBS::sim_time_t t, const BIBS::IBelief *b),
              (const, override));
};

class MockBelief : public BIBS::IBelief {
  using IBelief::IBelief;

  MOCK_METHOD(double, beliefRelationship, (const IBelief *b2),
              (const, override));
};

TEST(MockAgent, UUIDConstructor) {
  auto uuid = boost::uuids::random_generator_mt19937()();
  auto a = MockAgent(uuid);

  EXPECT_EQ(a.uuid, uuid);
}

TEST(Agent, EmptyConstructor) {
  auto a1 = BIBS::Agent();
  auto a2 = BIBS::Agent();

  EXPECT_NE(a1.uuid, a2.uuid);
}

TEST(Agent, UUIDConstructor) {
  auto uuid = boost::uuids::random_generator_mt19937()();
  auto a = BIBS::Agent(uuid);

  EXPECT_EQ(a.uuid, uuid);
}

TEST(Agent, activationMapConstructor) {
  std::map<BIBS::sim_time_t, std::map<const BIBS::IBelief *, double>> act;
  std::map<const BIBS::IBelief *, double> act0;
  auto b = std::make_unique<MockBelief>("b1");
  act0.insert({b.get(), 1.0});
  act.insert({0, act0});
  auto a1 = BIBS::Agent(act);
  auto a2 = BIBS::Agent(act);

  EXPECT_NE(a1.uuid, a2.uuid);
  EXPECT_EQ(a1.activation(0, b.get()), 1.0);
  EXPECT_EQ(a2.activation(0, b.get()), 1.0);
}

TEST(Agent, UUIDAndActivationMapConstructor) {
  auto uuid = boost::uuids::random_generator_mt19937()();
  std::map<BIBS::sim_time_t, std::map<const BIBS::IBelief *, double>> act;
  std::map<const BIBS::IBelief *, double> act0;
  auto b = std::make_unique<MockBelief>("b1");
  act0.insert({b.get(), 1.0});
  act.insert({0, act0});

  auto a = BIBS::Agent(uuid, act);

  EXPECT_EQ(a.uuid, uuid);
  EXPECT_EQ(a.activation(0, b.get()), 1.0);
}

TEST(Agent, activationWhenTNotFound) {
  auto a = BIBS::Agent();

  auto b = std::make_unique<MockBelief>("b1");
  EXPECT_THROW(a.activation(0, b.get()), std::out_of_range);
}

TEST(Agent, activationWhenBNotFound) {
  std::map<BIBS::sim_time_t, std::map<const BIBS::IBelief *, double>> act;
  std::map<const BIBS::IBelief *, double> act0;
  act.insert({0, act0});

  auto a = BIBS::Agent(act);
  auto b = std::make_unique<MockBelief>("b1");
  EXPECT_THROW(a.activation(0, b.get()), std::out_of_range);
}

TEST(Agent, activationWhenFound) {
  std::map<BIBS::sim_time_t, std::map<const BIBS::IBelief *, double>> act;
  std::map<const BIBS::IBelief *, double> act0;
  auto b = std::make_unique<MockBelief>("b1");
  act0.insert({b.get(), 1.0});
  act.insert({0, act0});

  auto a = BIBS::Agent(act);
  EXPECT_EQ(a.activation(0, b.get()), 1.0);
}
