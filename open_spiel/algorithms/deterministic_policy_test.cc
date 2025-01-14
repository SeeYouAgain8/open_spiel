// Copyright 2019 DeepMind Technologies Ltd. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "open_spiel/algorithms/deterministic_policy.h"

#include "open_spiel/games/kuhn_poker.h"

namespace open_spiel {
namespace algorithms {
namespace {

void KuhnDeterministicPolicyTest() {
  kuhn_poker::KuhnGame kuhn_game({});

  int p0_policies = 1;
  int p1_policies = 1;

  DeterministicTabularPolicy p0_policy(kuhn_game, Player{0});
  while (p0_policy.NextPolicy()) {
    p0_policies += 1;
  }
  SPIEL_CHECK_EQ(p0_policies, 64);  // 2^6

  DeterministicTabularPolicy p1_policy(kuhn_game, Player{1});
  while (p1_policy.NextPolicy()) {
    p1_policies += 1;
  }
  SPIEL_CHECK_EQ(p1_policies, 64);  // 2^6
}

}  // namespace
}  // namespace algorithms
}  // namespace open_spiel

int main(int argc, char** argv) {
  open_spiel::algorithms::KuhnDeterministicPolicyTest();
}
