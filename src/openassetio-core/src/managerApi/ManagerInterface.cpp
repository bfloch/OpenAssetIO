// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#include <stdexcept>

#include <openassetio/managerApi/ManagerInterface.hpp>

namespace openassetio {
inline namespace OPENASSETIO_CORE_ABI_VERSION {
namespace managerApi {

ManagerInterface::ManagerInterface() = default;

InfoDictionary ManagerInterface::info() const { return {}; }

InfoDictionary ManagerInterface::settings(
    [[maybe_unused]] const HostSessionPtr& hostSession) const {
  return openassetio::InfoDictionary{};
}

ManagerStateBasePtr ManagerInterface::createState(
    [[maybe_unused]] const HostSessionPtr& hostSession) {
  return nullptr;
}

ManagerStateBasePtr ManagerInterface::createChildState(
    [[maybe_unused]] const ManagerStateBasePtr& parentState,
    [[maybe_unused]] const HostSessionPtr& hostSession) {
  throw std::runtime_error(
      "createChildState called on a manager that does not implement a custom state.");
}

Str ManagerInterface::persistenceTokenForState(
    [[maybe_unused]] const ManagerStateBasePtr& state,
    [[maybe_unused]] const HostSessionPtr& hostSession) {
  throw std::runtime_error(
      "persistenceTokenForState called on a manager that does not implement a custom state.");
}

ManagerStateBasePtr ManagerInterface::stateFromPersistenceToken(
    [[maybe_unused]] const Str& token, [[maybe_unused]] const HostSessionPtr& hostSession) {
  throw std::runtime_error(
      "stateFromPersistenceToken called on a manager that does not implement a custom state.");
}

// To avoid changing this to non-static in the not too distant, when we
// add manager validation (see https://github.com/OpenAssetIO/OpenAssetIO/issues/553).
// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
EntityReference ManagerInterface::createEntityReference(Str entityReferenceString) const {
  return EntityReference(std::move(entityReferenceString));
}
}  // namespace managerApi
}  // namespace OPENASSETIO_CORE_ABI_VERSION
}  // namespace openassetio
