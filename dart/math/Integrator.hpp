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

#ifndef DART_INTEGRATION_INTEGRATOR_HPP_
#define DART_INTEGRATION_INTEGRATOR_HPP_

#include <dart/math/Fwd.hpp>

#include <vector>

namespace dart {
namespace math {

/// \brief Any class that uses an integrator should implement this interface
class IntegrableSystem
{
public:
  /// \brief Constructor
  IntegrableSystem();

  /// \brief Destructor
  virtual ~IntegrableSystem();

public:
  /// \brief Set configurations
  virtual void setConfigs(const VectorXd& _configs) = 0;

  /// \brief Set generalized velocities
  virtual void setGenVels(const VectorXd& _genVels) = 0;

  /// \brief Get configurations
  virtual VectorXd getConfigs() const = 0;

  /// \brief Get generalized velocities
  virtual VectorXd getGenVels() const = 0;

  /// \brief Evaulate generalized accelerations
  virtual VectorXd evalGenAccs() = 0;

  /// \brief Integrate configruations and store them in the system
  virtual void integrateConfigs(const VectorXd& _genVels, double _dt) = 0;

  /// \brief Integrate generalized velocities and store them in the system
  virtual void integrateGenVels(const VectorXd& _genVels, double _dt) = 0;
};

// TODO(kasiu): Consider templating the class (which currently only works on
// arbitrarily-sized vectors of doubles)
/// \brief class Integrator
class Integrator
{
public:
  /// \brief Constructor
  Integrator();

  /// \brief Destructor
  virtual ~Integrator();

public:
  /// \brief Integrate the system with time step dt
  virtual void integrate(IntegrableSystem* _system, double _dt) = 0;

  /// \brief Integrate velocity of the system with time step dt
  virtual void integratePos(IntegrableSystem* _system, double _dt) = 0;

  /// \brief Integrate velocity of the system with time step dt
  virtual void integrateVel(IntegrableSystem* _system, double _dt) = 0;
};

} // namespace math
} // namespace dart

#endif // DART_INTEGRATION_INTEGRATOR_HPP_
