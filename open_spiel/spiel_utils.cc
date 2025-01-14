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

#include "open_spiel/spiel_utils.h"

#include <iostream>
#include <string>

namespace open_spiel {

int NextPlayerRoundRobin(Player player, int nplayers) {
  if (player + 1 < nplayers) {
    return player + 1;
  } else {
    return 0;
  }
}

// Helper function to determine the previous player in a round robin.
int PreviousPlayerRoundRobin(Player player, int nplayers) {
  if (player - 1 >= 0) {
    return player - 1;
  } else {
    return nplayers - 1;
  }
}

std::pair<bool, std::string> ParseCmdLineArg(int argc, char** argv,
                                             const std::string& name) {
  std::string prefix = "--" + name + "=";

  for (int i = 0; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.find(prefix) == 0) {
      return std::pair<bool, std::string>(true, arg.substr(prefix.length()));
    }
  }

  return std::pair<bool, std::string>(false, "");
}

std::string ParseCmdLineArgDefault(int argc, char** argv,
                                   const std::string& name,
                                   const std::string& default_value) {
  std::pair<bool, std::string> ret_value = ParseCmdLineArg(argc, argv, name);
  if (ret_value.first) {
    return ret_value.second;
  } else {
    return default_value;
  }
}

// Used to convert actions represented as integers in mixed bases.
Action RankActionMixedBase(const std::vector<int>& bases,
                           const std::vector<int>& digits) {
  SPIEL_CHECK_EQ(bases.size(), digits.size());
  SPIEL_CHECK_GT(digits.size(), 0);

  Action action = 0;
  int one_plus_max = 1;
  for (int i = digits.size() - 1; i >= 0; --i) {
    SPIEL_CHECK_GE(digits[i], 0);
    SPIEL_CHECK_LT(digits[i], bases[i]);
    SPIEL_CHECK_GT(bases[i], 1);
    action += digits[i] * one_plus_max;
    one_plus_max *= bases[i];
    SPIEL_CHECK_LT(action, one_plus_max);
  }

  return action;
}

void UnrankActionMixedBase(Action action, const std::vector<int>& bases,
                           std::vector<int>* digits) {
  SPIEL_CHECK_EQ(bases.size(), digits->size());
  for (int i = digits->size() - 1; i >= 0; --i) {
    SPIEL_CHECK_GT(bases[i], 1);
    (*digits)[i] = action % bases[i];
    action /= bases[i];
  }
  SPIEL_CHECK_EQ(action, 0);
}

void SpielDefaultErrorHandler(const std::string& error_msg) {
  std::cerr << "Spiel Fatal Error: " << error_msg << std::endl << std::endl;
  std::exit(1);
}

ErrorHandler error_handler = SpielDefaultErrorHandler;

void SetErrorHandler(ErrorHandler new_error_handler) {
  error_handler = new_error_handler;
}

void SpielFatalError(const std::string& error_msg) {
  error_handler(error_msg);
  // The error handler should not return. If it does, we will abort the process.
  std::cerr << "Error handler failure - exiting" << std::endl;
  std::exit(1);
}

}  // namespace open_spiel
