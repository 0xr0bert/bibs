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
#include <gtest/gtest.h>

TEST(Behaviour, NameOnlyConstructor) {
  std::string name1 = "B1";
  auto beh1 = BIBS::Behaviour(std::move(name1));

  std::string name2 = "B2";
  auto beh2 = BIBS::Behaviour(std::move(name2));

  ASSERT_NE(beh1.uuid, beh2.uuid);
  ASSERT_EQ(beh1.name, "B1");
  ASSERT_EQ(beh2.name, "B2");
}

TEST(Behaviour, NameAndUUIDConstructor) {
  std::string name = "B1";
  auto uuid = boost::uuids::random_generator_mt19937()();
  auto beh = BIBS::Behaviour(std::move(name), uuid);

  ASSERT_EQ(beh.name, "B1");
  ASSERT_EQ(beh.uuid, uuid);
}
