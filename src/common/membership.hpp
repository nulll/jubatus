// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2011 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#pragma once
#include "lock_service.hpp"

#include <string>
#include <vector>
#include <map>

namespace jubatus {
namespace common {

static const std::string JUBATUS_BASE_PATH = "/jubatus";
static const std::string JUBAVISOR_BASE_PATH = "/jubatus/supervisors";
static const std::string JUBAKEEPER_BASE_PATH = "/jubatus/jubakeepers";
static const std::string ACTOR_BASE_PATH = "/jubatus/actors";

// "127.0.0.1" -> 9199 -> "127.0.0.1_9199"
std::string build_loc_str(const std::string&, int, unsigned int = 0);

// /path/base -> 127.0.0.1 -> 9199 -> /path/base/127.0.0.1_9199
void build_existence_path(const std::string&, const std::string&, int, std::string&);

void build_actor_path(std::string&, const std::string& type, const std::string& name);

// 127.0.0.1_9199 -> (127.0.0.1, 9199)
bool revert(const std::string&, std::string&, int&);

// zk -> name -> ip -> port -> bool
bool register_actor(lock_service&, const std::string& type, const std::string& name,
                    const std::string& ip, int port);
// zk -> name -> ip -> port -> bool
bool register_keeper(lock_service&, const std::string& type, const std::string& ip, int);
// zk -> name -> list( (ip, rpc_port) )
bool get_all_actors(lock_service&, const std::string& type, const std::string&,
                    std::vector<std::pair<std::string, int> >&);

bool push_cleanup(lock_service&, pfi::lang::function<void()>&);

void force_exit();

void prepare_jubatus(lock_service& ls,
                     const std::string& type, const std::string& name = "");

} // common
} // jubatus
