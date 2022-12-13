/*
Copyright 2017-2019 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "lullaby/modules/script/function_binder.h"

namespace lull {

FunctionBinder::FunctionBinder(Registry* registry) : registry_(registry) {
#if !LULLABY_DISABLE_FUNCTION_BINDER
  RegisterBuiltInFunctions(this);
#endif
}

FunctionBinder* FunctionBinder::Create(Registry* registry) {
  return registry->Create<FunctionBinder>(registry);
}

void FunctionBinder::UnregisterFunction(string_view name) {
#if !LULLABY_DISABLE_FUNCTION_BINDER
  auto* script_engine = registry_->Get<ScriptEngine>();
  if (script_engine) {
    script_engine->UnregisterFunction(std::string(name));
  }

  auto iter = functions_.find(Hash(name));
  if (iter == functions_.end()) {
    LOG(DFATAL) << "Cannot unregister non-existent function: " << name;
    return;
  }
  functions_.erase(iter);
#endif
}

bool FunctionBinder::IsFunctionRegistered(string_view name) const {
  return IsFunctionRegistered(Hash(name));
}

bool FunctionBinder::IsFunctionRegistered(HashValue id) const {
  return functions_.count(id) != 0;
}

Variant FunctionBinder::Call(FunctionCall* call) {
#if !LULLABY_DISABLE_FUNCTION_BINDER
  const auto iter = functions_.find(call->GetId());
  if (iter == functions_.end()) {
    if (call->GetName().empty()) {
      LOG(DFATAL) << "Unknown function: " << call->GetId();
    } else {
      LOG(DFATAL) << "Unknown function: " << call->GetName();
    }
    return Variant();
  }
  iter->second->Call(call);
  return call->GetReturnValue();
#else
  return Variant();
#endif
}

}  // namespace lull
