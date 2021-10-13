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

#include "bibs/bibs.hpp"
#include <gtest/gtest.h>

TEST(SquareRootTest, Positive) {
  ASSERT_EQ(10, squareRoot(100.0));
  ASSERT_EQ(0, squareRoot(0.0));
}

TEST(SquareRootTest, Negative) { ASSERT_EQ(-1.0, squareRoot(-16.0)); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
