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
#include "bibs/behaviour.hpp"
#include "bibs/belief.hpp"

#include "agent.hpp"
#include "behaviour.hpp"
#include "belief.hpp"
#include "bibs/bibs.hpp"
#include <boost/format.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <cstdio>
#include <gmock/gmock-actions.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <random>
#include <stdexcept>

TEST(MockAgent, UUIDConstructor) {
  auto uuid = boost::uuids::random_generator_mt19937()();
  auto a = BIBS::testing::MockAgent(uuid);

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
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");
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
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");
  act0.insert({b.get(), 1.0});
  act.insert({0, act0});

  auto a = BIBS::Agent(uuid, act);

  EXPECT_EQ(a.uuid, uuid);
  EXPECT_EQ(a.activation(0, b.get()), 1.0);
}

TEST(Agent, activationWhenTNotFound) {
  auto a = BIBS::Agent();

  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");
  EXPECT_THROW(a.activation(0, b.get()), std::out_of_range);
}

TEST(Agent, activationWhenBNotFound) {
  std::map<BIBS::sim_time_t, std::map<const BIBS::IBelief *, double>> act;
  std::map<const BIBS::IBelief *, double> act0;
  act.insert({0, act0});

  auto a = BIBS::Agent(act);
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");
  EXPECT_THROW(a.activation(0, b.get()), std::out_of_range);
}

TEST(Agent, activationWhenFound) {
  std::map<BIBS::sim_time_t, std::map<const BIBS::IBelief *, double>> act;
  std::map<const BIBS::IBelief *, double> act0;
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");
  act0.insert({b.get(), 1.0});
  act.insert({0, act0});

  auto a = BIBS::Agent(act);
  EXPECT_EQ(a.activation(0, b.get()), 1.0);
}

TEST(Agent, performedWhenNotFound) {
  auto a = BIBS::Agent();

  EXPECT_THROW(a.performed(10), std::out_of_range);
}

TEST(Agent, performWhenFound) {
  auto b = std::make_unique<BIBS::testing::MockBehaviour>("b1");
  auto a = BIBS::Agent();

  a._addPerformed(10, b.get());

  EXPECT_EQ(a.performed(10), b.get());
}

TEST(Agent, friendWeightWhenNotFound) {
  auto a1 = BIBS::Agent();
  auto a2 = std::make_unique<BIBS::testing::MockAgent>(
      boost::uuids::random_generator_mt19937()());

  EXPECT_THROW(a1.friendWeight(a2.get()), std::out_of_range);
}

TEST(Agent, friendWeightWhenFoundAndSet) {
  auto a1 = BIBS::Agent();
  auto a2 = std::make_unique<BIBS::testing::MockAgent>(
      boost::uuids::random_generator_mt19937()());

  a1.setFriendWeight(a2.get(), 5.0);

  EXPECT_EQ(a1.friendWeight(a2.get()), 5.0);
}

TEST(Agent, setFriendWeightUpdating) {
  auto a1 = BIBS::Agent();
  auto a2 = std::make_unique<BIBS::testing::MockAgent>(
      boost::uuids::random_generator_mt19937()());

  a1.setFriendWeight(a2.get(), 5.0);

  EXPECT_EQ(a1.friendWeight(a2.get()), 5.0);

  a1.setFriendWeight(a2.get(), 1.0);

  EXPECT_EQ(a1.friendWeight(a2.get()), 1.0);
}

class AgentWithObservedWrapper : public BIBS::Agent {
public:
  using Agent::Agent;

  double observedW(const BIBS::IBelief *b, const BIBS::sim_time_t t) const {
    return observed(b, t);
  }
};

TEST(Agent, observed) {
  auto a1 = AgentWithObservedWrapper();
  auto uuidGen = boost::uuids::random_generator_mt19937();

  auto beh1 = std::make_unique<BIBS::testing::MockBehaviour>("beh1");
  auto beh2 = std::make_unique<BIBS::testing::MockBehaviour>("beh2");

  std::unique_ptr<BIBS::testing::MockAgent> as[5];
  double weights[5];

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(0, 1);

  for (size_t i = 0; i < 5; ++i) {
    as[i] = std::make_unique<BIBS::testing::MockAgent>(uuidGen());
    EXPECT_CALL(*as[i], performed(2));

    if (i % 2 == 0) {
      ON_CALL(*as[i], performed(2)).WillByDefault(testing::Return(beh1.get()));
    } else {
      ON_CALL(*as[i], performed(2)).WillByDefault(testing::Return(beh2.get()));
    }

    weights[i] = distr(eng);
    a1.setFriendWeight(as[i].get(), weights[i]);
  }

  auto bel = std::make_unique<BIBS::testing::MockBelief>("b1");
  EXPECT_CALL(*bel, observedBehaviourRelationship(beh1.get())).Times(3);
  ON_CALL(*bel, observedBehaviourRelationship(beh1.get()))
      .WillByDefault(testing::Return(-1.2));
  EXPECT_CALL(*bel, observedBehaviourRelationship(beh2.get())).Times(2);
  ON_CALL(*bel, observedBehaviourRelationship(beh2.get()))
      .WillByDefault(testing::Return(1.4));

  double expected_ret = 0.0;

  for (size_t i = 0; i < 5; ++i) {
    if (i % 2 == 0) {
      expected_ret += -1.2 * weights[i];
    } else {
      expected_ret += 1.4 * weights[i];
    }
  }

  EXPECT_EQ(a1.observedW(bel.get(), 2), expected_ret);
}

class AgentWithContextualiseWrapper : public BIBS::Agent {
public:
  using Agent::Agent;

  double contextualiseW(const BIBS::IBelief *b,
                        const BIBS::sim_time_t t) const {
    return contextualise(b, t);
  }
};

TEST(Agent, contextualise) {
  std::unique_ptr<BIBS::testing::MockBelief> bs[5];
  std::map<const BIBS::IBelief *, double> activationMap;

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(0, 1);

  for (size_t i = 0; i < 5; ++i) {
    bs[i] = std::make_unique<BIBS::testing::MockBelief>(
        boost::str(boost::format("b%1%") % i));
    activationMap[bs[i].get()] = distr(eng);
  }

  EXPECT_CALL(*bs[0], beliefRelationship(bs[0].get()));
  ON_CALL(*bs[0], beliefRelationship(bs[0].get()))
      .WillByDefault(testing::Return(0.0));

  double rels[5];
  rels[0] = 0;

  for (size_t i = 1; i < 5; ++i) {
    rels[i] = distr(eng);
    EXPECT_CALL(*bs[0], beliefRelationship(bs[i].get()));
    ON_CALL(*bs[0], beliefRelationship(bs[i].get()))
        .WillByDefault(testing::Return(rels[i]));
  }

  std::map<BIBS::sim_time_t, std::map<const BIBS::IBelief *, double>>
      tActivationMap;
  tActivationMap.emplace(2, activationMap);

  auto a = AgentWithContextualiseWrapper(tActivationMap);

  double value_to_exp = 0.0;

  for (size_t i = 0; i < 5; ++i) {
    value_to_exp += activationMap[bs[i].get()] * rels[i];
  }

  EXPECT_DOUBLE_EQ(a.contextualiseW(bs[0].get(), 2), std::exp(value_to_exp));
}

class AgentContextualObservedTest : public BIBS::Agent {
public:
  using Agent::Agent;

  MOCK_METHOD(double, observed,
              (const BIBS::IBelief *b, const BIBS::sim_time_t t),
              (const, override));

  MOCK_METHOD(double, contextualise,
              (const BIBS::IBelief *b, const BIBS::sim_time_t t),
              (const, override));

  double contextualObservedW(const BIBS::IBelief *b,
                             const BIBS::sim_time_t t) const {
    return contextualObserved(b, t);
  }
};

TEST(Agent, contextualObserved) {
  AgentContextualObservedTest a;
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-1, 1);

  double obs = distr(eng);
  double context = distr(eng);
  double conObs = obs * context;

  EXPECT_CALL(a, observed(b.get(), 2));
  ON_CALL(a, observed(b.get(), 2)).WillByDefault(testing::Return(obs));

  EXPECT_CALL(a, contextualise(b.get(), 2));
  ON_CALL(a, contextualise(b.get(), 2)).WillByDefault(testing::Return(context));

  EXPECT_DOUBLE_EQ(a.contextualObservedW(b.get(), 2), conObs);
}

TEST(Agent, timeDeltaWhenNotFound) {
  BIBS::Agent a;
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");

  EXPECT_THROW(a.timeDelta(b.get()), std::out_of_range);
}

TEST(Agent, timeDeltaWhenFoundAndSet) {
  BIBS::Agent a;
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");

  a.setTimeDelta(b.get(), 2.0);

  EXPECT_DOUBLE_EQ(a.timeDelta(b.get()), 2.0);
}

TEST(Agent, setTimeDeltaUpdating) {
  BIBS::Agent a;
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");

  a.setTimeDelta(b.get(), 2.0);

  EXPECT_DOUBLE_EQ(a.timeDelta(b.get()), 2.0);

  a.setTimeDelta(b.get(), 5.0);

  EXPECT_DOUBLE_EQ(a.timeDelta(b.get()), 5.0);
}

class AgentUpdateActivationTest : public BIBS::Agent {
public:
  using Agent::Agent;

  MOCK_METHOD(double, contextualObserved,
              (const BIBS::IBelief *b, const BIBS::sim_time_t t),
              (const, override));

  MOCK_METHOD(double, timeDelta, (const BIBS::IBelief *b), (const, override));
  MOCK_METHOD(double, activation,
              (const BIBS::sim_time_t t, const BIBS::IBelief *b),
              (const, override));

  double activationW(const BIBS::sim_time_t t, const BIBS::IBelief *b) const {
    return BIBS::Agent::activation(t, b);
  }
};

TEST(Agent, updateActivation) {
  AgentUpdateActivationTest a;
  auto b = std::make_unique<BIBS::testing::MockBelief>("b1");

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(0, 1);

  double co = distr(eng);
  double td = distr(eng);
  double oldActivation = distr(eng);
  double newActivation = td * oldActivation + co;

  EXPECT_CALL(a, contextualObserved(b.get(), 4));
  ON_CALL(a, contextualObserved(b.get(), 4)).WillByDefault(testing::Return(co));

  EXPECT_CALL(a, timeDelta(b.get()));
  ON_CALL(a, timeDelta(b.get())).WillByDefault(testing::Return(td));

  EXPECT_CALL(a, activation(4, b.get()));
  ON_CALL(a, activation(4, b.get()))
      .WillByDefault(testing::Return(oldActivation));

  a.updateActivation(5, b.get());

  EXPECT_DOUBLE_EQ(a.activationW(5, b.get()), newActivation);
}

class AgentBeliefBehaviourTest : public BIBS::Agent {
public:
  using Agent::Agent;

  MOCK_METHOD(double, activation,
              (const BIBS::sim_time_t t, const BIBS::IBelief *b),
              (const, override));

  double beliefBehaviourW(const BIBS::IBelief *bel, const BIBS::IBehaviour *beh,
                          const BIBS::sim_time_t t) const {
    return beliefBehaviour(bel, beh, t);
  }
};

TEST(Agent, beliefBehaviour) {
  auto beh = std::make_unique<BIBS::testing::MockBehaviour>("b1");
  auto bel = std::make_unique<BIBS::testing::MockBelief>("b1");

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(0, 1);

  double rel = distr(eng);
  double act = distr(eng);
  double bb = act * rel;

  EXPECT_CALL(*bel, performingBehaviourRelationship(beh.get()));
  ON_CALL(*bel, performingBehaviourRelationship(beh.get()))
      .WillByDefault(testing::Return(rel));

  AgentBeliefBehaviourTest a;

  EXPECT_CALL(a, activation(5, bel.get()));
  ON_CALL(a, activation(5, bel.get())).WillByDefault(testing::Return(act));

  EXPECT_DOUBLE_EQ(a.beliefBehaviourW(bel.get(), beh.get(), 5), bb);
}

class AgentContextualBeliefBehaviourTest : public BIBS::Agent {
public:
  using Agent::Agent;

  MOCK_METHOD(double, beliefBehaviour,
              (const BIBS::IBelief *bel, const BIBS::IBehaviour *beh,
               const BIBS::sim_time_t t),
              (const, override));

  MOCK_METHOD(double, contextualise,
              (const BIBS::IBelief *bel, const BIBS::sim_time_t t),
              (const, override));

  double contextualBeliefBehaviourW(const BIBS::IBelief *bel,
                                    const BIBS::IBehaviour *beh,
                                    const BIBS::sim_time_t t) const {
    return contextualBeliefBehaviour(bel, beh, t);
  }
};

TEST(Agent, contextualBeliefBehaviour) {
  auto beh = std::make_unique<BIBS::testing::MockBehaviour>("b1");
  auto bel = std::make_unique<BIBS::testing::MockBelief>("b1");

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(0, 1);

  double context = distr(eng);
  double bb = distr(eng);
  double contextBB = context * bb;

  AgentContextualBeliefBehaviourTest a;

  EXPECT_CALL(a, contextualise(bel.get(), 5));
  ON_CALL(a, contextualise(bel.get(), 5))
      .WillByDefault(testing::Return(context));

  EXPECT_CALL(a, beliefBehaviour(bel.get(), beh.get(), 5));
  ON_CALL(a, beliefBehaviour(bel.get(), beh.get(), 5))
      .WillByDefault(testing::Return(bb));

  EXPECT_DOUBLE_EQ(a.contextualBeliefBehaviourW(bel.get(), beh.get(), 5),
                   contextBB);
}

class AgentContextualBehaviourTest : public BIBS::Agent {
public:
  using Agent::Agent;

  MOCK_METHOD(double, contextualBeliefBehaviour,
              (const BIBS::IBelief *bel, const BIBS::IBehaviour *beh,
               const BIBS::sim_time_t t),
              (const, override));

  double contextualBehaviourW(const BIBS::IBehaviour *b,
                              const BIBS::sim_time_t t) const {
    return contextualBehaviour(b, t);
  }
};

TEST(Agent, contextualBehaviour) {
  std::unique_ptr<BIBS::IBelief> beliefs[5];
  std::map<const BIBS::IBelief *, double> activations;
  double cbb[5];
  double cb = 0.0;

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(0, 1);

  for (size_t i = 0; i < 5; ++i) {
    beliefs[i] = std::make_unique<BIBS::testing::MockBelief>(
        boost::str(boost::format("b%1%") % i));
    activations.emplace(beliefs[i].get(), 0);
    cbb[i] = distr(eng);
    cb += cbb[i];
  }

  std::map<BIBS::sim_time_t, std::map<const BIBS::IBelief *, double>>
      activationTimes;
  activationTimes.emplace(5, activations);

  AgentContextualBehaviourTest a(activationTimes);
  auto beh = std::make_unique<BIBS::testing::MockBehaviour>("b1");

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_CALL(a, contextualBeliefBehaviour(beliefs[i].get(), beh.get(), 5));
    ON_CALL(a, contextualBeliefBehaviour(beliefs[i].get(), beh.get(), 5))
        .WillByDefault(testing::Return(cbb[i]));
  }

  EXPECT_DOUBLE_EQ(a.contextualBehaviourW(beh.get(), 5), cb);
}
