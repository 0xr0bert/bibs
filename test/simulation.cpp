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
#include "agent.hpp"
#include "behaviour.hpp"
#include "belief.hpp"
#include "bibs/agent.hpp"
#include "bibs/behaviour.hpp"
#include "bibs/belief.hpp"
#include "bibs/bibs.hpp"
#include <boost/format.hpp>
#include <boost/uuid/random_generator.hpp>
#include <gtest/gtest.h>
#include <memory>

class SequentialSimulationConstructorTest : public BIBS::SequentialSimulation {
public:
  using SequentialSimulation::SequentialSimulation;

  [[nodiscard]] std::vector<BIBS::IAgent *> getAgents() const { return agents; }
  [[nodiscard]] std::vector<const BIBS::IAgent *> getConstAgents() const {
    return constAgents;
  }
  [[nodiscard]] std::vector<BIBS::IBelief *> getBeliefs() const {
    return beliefs;
  }
  [[nodiscard]] std::vector<const BIBS::IBelief *> getConstBeliefs() const {
    return constBeliefs;
  }
  [[nodiscard]] std::vector<BIBS::IBehaviour *> getBehaviours() const {
    return behaviours;
  }
  [[nodiscard]] std::vector<const BIBS::IBehaviour *>
  getConstBehaviours() const {
    return constBehaviours;
  }
};

TEST(SequentialSimulation, constructor) {
  std::vector<std::unique_ptr<BIBS::IAgent>> agents;
  std::vector<BIBS::IAgent *> ptrAgents;
  std::vector<const BIBS::IAgent *> constPtrAgents;
  std::vector<std::unique_ptr<BIBS::testing::MockBelief>> beliefs;
  std::vector<BIBS::IBelief *> ptrBeliefs;
  std::vector<const BIBS::IBelief *> constPtrBeliefs;
  std::vector<std::unique_ptr<BIBS::testing::MockBehaviour>> behaviours;
  std::vector<BIBS::IBehaviour *> ptrBehaviours;
  std::vector<const BIBS::IBehaviour *> constPtrBehaviours;

  auto uuidGen = boost::uuids::random_generator_mt19937();

  for (size_t i = 0; i < 1000; ++i) {
    agents.push_back(std::make_unique<BIBS::testing::MockAgent>(uuidGen()));
    ptrAgents.push_back(agents[i].get());
    constPtrAgents.push_back(agents[i].get());
  }

  for (size_t i = 0; i < 20; ++i) {
    beliefs.push_back(std::make_unique<BIBS::testing::MockBelief>(
        boost::str(boost::format("b%1%") % i)));
    ptrBeliefs.push_back(beliefs[i].get());
    constPtrBeliefs.push_back(beliefs[i].get());
  }

  for (size_t i = 0; i < 10; ++i) {
    behaviours.push_back(std::make_unique<BIBS::testing::MockBehaviour>(
        boost::str(boost::format("b%1%") % i)));
    ptrBehaviours.push_back(behaviours[i].get());
    constPtrBehaviours.push_back(behaviours[i].get());
  }

  SequentialSimulationConstructorTest sim(ptrAgents, ptrBeliefs, ptrBehaviours);

  EXPECT_EQ(sim.getAgents(), ptrAgents);
  EXPECT_EQ(sim.getConstAgents(), constPtrAgents);
  EXPECT_EQ(sim.getBeliefs(), ptrBeliefs);
  EXPECT_EQ(sim.getConstBeliefs(), constPtrBeliefs);
  EXPECT_EQ(sim.getBehaviours(), ptrBehaviours);
  EXPECT_EQ(sim.getConstBehaviours(), constPtrBehaviours);
}

class AgentSequentialSimTest : public BIBS::testing::MockAgent {
public:
  using MockAgent::MockAgent;

  MOCK_METHOD(void, tick,
              (const BIBS::sim_time_t t,
               const std::vector<const BIBS::IBehaviour *> &behs,
               const std::vector<const BIBS::IBelief *> &bels),
              (override));
};

TEST(SequentialSimulation, run) {
  std::vector<std::unique_ptr<AgentSequentialSimTest>> agents;
  std::vector<BIBS::IAgent *> ptrAgents;
  std::vector<const BIBS::IAgent *> constPtrAgents;
  std::vector<std::unique_ptr<BIBS::testing::MockBelief>> beliefs;
  std::vector<BIBS::IBelief *> ptrBeliefs;
  std::vector<const BIBS::IBelief *> constPtrBeliefs;
  std::vector<std::unique_ptr<BIBS::testing::MockBehaviour>> behaviours;
  std::vector<BIBS::IBehaviour *> ptrBehaviours;
  std::vector<const BIBS::IBehaviour *> constPtrBehaviours;

  auto uuidGen = boost::uuids::random_generator_mt19937();

  BIBS::sim_time_t t = 10;

  for (size_t i = 0; i < 20; ++i) {
    beliefs.push_back(std::make_unique<BIBS::testing::MockBelief>(
        boost::str(boost::format("b%1%") % i)));
    ptrBeliefs.push_back(beliefs[i].get());
    constPtrBeliefs.push_back(beliefs[i].get());
  }

  for (size_t i = 0; i < 10; ++i) {
    behaviours.push_back(std::make_unique<BIBS::testing::MockBehaviour>(
        boost::str(boost::format("b%1%") % i)));
    ptrBehaviours.push_back(behaviours[i].get());
    constPtrBehaviours.push_back(behaviours[i].get());
  }

  for (size_t i = 0; i < 100; ++i) {
    agents.push_back(std::make_unique<AgentSequentialSimTest>(uuidGen()));
    ptrAgents.push_back(agents[i].get());
    constPtrAgents.push_back(agents[i].get());
    for (size_t j = 0; j < t; ++j) {
      EXPECT_CALL(*agents[i], tick(j, constPtrBehaviours, constPtrBeliefs));
    }
  }

  BIBS::SequentialSimulation sim(ptrAgents, ptrBeliefs, ptrBehaviours);
  sim.run(t);
}
