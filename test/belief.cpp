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
#include <gtest/gtest.h>

class MockBelief : public BIBS::IBelief {
  using IBelief::IBelief;
};

TEST(MockBelief, NameOnlyConstructor) {
  std::string name1 = "B1";
  auto b1 = MockBelief(std::move(name1));

  std::string name2 = "B2";
  auto b2 = MockBelief(std::move(name2));

  ASSERT_NE(b1.uuid, b2.uuid);
  ASSERT_EQ(b1.name, "B1");
  ASSERT_EQ(b2.name, "B2");
}

TEST(MockBelief, NameAndUUIDConstructor) {
  std::string name = "B1";
  auto uuid = boost::uuids::random_generator_mt19937()();
  auto b = MockBelief(std::move(name), uuid);

  ASSERT_EQ(b.name, "B1");
  ASSERT_EQ(b.uuid, uuid);
}

TEST(Belief, NameOnlyConstructor) {
  std::string name1 = "B1";
  auto b1 = BIBS::Belief(std::move(name1));

  std::string name2 = "B2";
  auto b2 = BIBS::Belief(std::move(name2));

  ASSERT_NE(b1.uuid, b2.uuid);
  ASSERT_EQ(b1.name, "B1");
  ASSERT_EQ(b2.name, "B2");
}

TEST(Belief, NameAndUUIDConstructor) {
  std::string name = "B1";
  auto uuid = boost::uuids::random_generator_mt19937()();
  auto b = BIBS::Belief(std::move(name), uuid);

  ASSERT_EQ(b.name, "B1");
  ASSERT_EQ(b.uuid, uuid);
}
