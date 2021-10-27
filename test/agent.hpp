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

/**
 * @file      agent.hpp<test>
 * @brief     Header of MockAgent
 * @date      Tue Oct 26 15:29:47 2021
 * @author    Robert Greener
 * @copyright GPL-3.0-or-later
 *
 * This module contains Mock Agent
 */

#include "bibs/agent.hpp"
#include "bibs/bibs.hpp"
#include "gmock/gmock.h"

namespace BIBS::testing {
class MockAgent : public BIBS::IAgent {
  using IAgent::IAgent;

  MOCK_METHOD(double, activation,
              (const BIBS::sim_time_t t, const BIBS::IBelief *b),
              (const, override));

  MOCK_METHOD(const IBehaviour *, performed, (const sim_time_t t),
              (const, override));

  MOCK_METHOD(double, observed,
              (const BIBS::IBelief *b, const BIBS::sim_time_t t),
              (const, override));
};
} // namespace BIBS::testing
