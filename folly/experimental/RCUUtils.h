/*
 * Copyright 2017 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <urcu.h> // @manual

namespace folly {

/**
 * This must be called at least once from any thread, which uses RCUReadLock.
 * First call should happen before RCUReadLock is used for the first time. Can
 * be safely called more that once.
 *
 * Returns true when called for the first time from current thread.
 */
bool RCURegisterThread();

class RCUReadLock {
 public:
  static RCUReadLock& instance();

  static void lock() {
    assert(RCURegisterThread() == false);
    rcu_read_lock();
  }

  static void unlock() {
    rcu_read_unlock();
  }

 private:
  RCUReadLock() {}
};

}
