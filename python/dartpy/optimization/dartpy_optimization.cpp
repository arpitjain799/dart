/*
 * Copyright (c) 2011-2023, The DART development contributors
 * All rights reserved.
 *
 * The list of contributors can be found at:
 *   https://github.com/dartsim/dart/blob/master/LICENSE
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#include <dart/optimization/optimization.hpp>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dart::python {

void Solver(py::module& sm);
void GradientDescentSolver(py::module& sm);
#if DART_HAS_NLOPT
void NloptSolver(py::module& sm);
#endif // DART_HAS_NLOPT

void Function(py::module& sm);

void Problem(py::module& sm);

PYBIND11_MODULE(dartpy_optimization, sm)
{
  sm.doc() = "dartpy.optimization";

#ifdef DARTPY_VERSION_INFO
  sm.attr("__version__") = DARTPY_VERSION_INFO;
#else
  sm.attr("__version__") = "dev";
#endif

  Solver(sm);
  GradientDescentSolver(sm);
#if DART_HAS_NLOPT
  NloptSolver(sm);
#endif // DART_HAS_NLOPT

  Function(sm);

  Problem(sm);
}

} // namespace dart::python
