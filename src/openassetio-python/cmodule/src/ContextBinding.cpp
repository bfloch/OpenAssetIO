// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <openassetio/Context.hpp>
#include <openassetio/TraitsData.hpp>
#include <openassetio/managerApi/ManagerStateBase.hpp>

#include "PyRetainingSharedPtr.hpp"
#include "_openassetio.hpp"

void registerContext(const py::module& mod) {
  using openassetio::Context;
  using openassetio::ContextPtr;
  using openassetio::TraitsDataPtr;
  using openassetio::managerApi::ManagerStateBasePtr;
  using PyRetainingManagerStateBasePtr =
      openassetio::PyRetainingSharedPtr<openassetio::managerApi::ManagerStateBase>;

  py::class_<Context, ContextPtr> context{mod, "Context", py::is_final()};

  py::enum_<Context::Access>{context, "Access"}
      .value("kRead", Context::Access::kRead)
      .value("kReadMultiple", Context::Access::kReadMultiple)
      .value("kWrite", Context::Access::kWrite)
      .value("kWriteMultiple", Context::Access::kWriteMultiple)
      .value("kUnknown", Context::Access::kUnknown);

  context.def_readonly_static("kAccessNames", &Context::kAccessNames);

  py::enum_<Context::Retention>{context, "Retention"}
      .value("kIgnored", Context::Retention::kIgnored)
      .value("kTransient", Context::Retention::kTransient)
      .value("kSession", Context::Retention::kSession)
      .value("kPermanent", Context::Retention::kPermanent);

  context.def_readonly_static("kRetentionNames", &Context::kRetentionNames);

  context
      .def(py::init(RetainCommonPyArgs::forFn<&Context::make>()),
           py::arg_v("access", Context::Access::kUnknown),
           py::arg_v("retention", Context::Retention::kTransient),
           py::arg_v("locale", TraitsDataPtr{}), py::arg_v("managerState", ManagerStateBasePtr{}))
      .def_readwrite("access", &Context::access)
      .def_readwrite("retention", &Context::retention)
      .def_readwrite("locale", &Context::locale)
      .def_property(
          "managerState", [](const Context& self) { return self.managerState; },
          [](Context& self, PyRetainingManagerStateBasePtr managerState) {
            self.managerState = std::move(managerState);
          })
      .def("isForRead", &Context::isForRead)
      .def("isForWrite", &Context::isForWrite)
      .def("isForMultiple", &Context::isForMultiple);
}
