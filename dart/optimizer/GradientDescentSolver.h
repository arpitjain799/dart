/*
 * Copyright (c) 2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Michael X. Grey <mxgrey@gatech.edu>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
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

#ifndef DART_OPTIMIZER_GRADIENTDESCENTSOLVER_H_
#define DART_OPTIMIZER_GRADIENTDESCENTSOLVER_H_

#include "dart/optimizer/Solver.h"

namespace dart {
namespace optimizer {

/// DefaultSolver is a Solver extension which is native to DART (rather than
/// relying on third-party libraries). It uses randomized gradient descent and
/// softened constraints (i.e. constraint functions are added into the
/// objective function and assigned weights) to solve nonlinear problems. Note
/// that this is not a good option for Problems with difficult constraint
/// functions that need to be solved exactly.
class GradientDescentSolver : public Solver
{
public:

  static const std::string Type;

  struct UniqueProperties
  {
    /// Value of the fixed step size
    double mStepSize;

    /// Number of attempts to make before quitting. Each attempt will start from
    /// the next seed provided by the problem. Once there are no more seeds,
    /// random starting configurations will be used.
    ///
    /// Set this to 0 to keep trying until a solution is found (the program will
    /// need to be interrupted in order to stop if no solution is being found).
    size_t mMaxAttempts;

    /// The number of steps between random perturbations being applied to the
    /// configuration. Set this to 0 to never apply randomized perturbations.
    size_t mPerturbationStep;

    /// The random perturbation works as follows: A random point in the domain
    /// of the Problem is selected, and then a random step size between 0 and
    /// mMaxPerturbationFactor is selected. The configuration will take a step
    /// of that random step size towards the random point.
    ///
    /// A maximum value of 1.0 is recommended for mMaxPerturbationFactor. A
    /// smaller value will result in smaller randomized perturbations. A value
    /// significantly larger than 1.0 could bias the configuration towards the
    /// boundary of the Problem domain.
    double mMaxPerturbationFactor;

    /// The largest permittable change in value when randomizing a configuration
    double mMaxRandomizationStep;

    /// This is the weight that will be applied to any constraints that do not
    /// have a corresponding weight specified by mEqConstraintWeights or by
    /// mIneqConstraintWeights
    double mDefaultConstraintWeight;

    /// Vector of weights that should be applied to the equality constraints.
    /// If there are fewer components in this vector than there are equality
    /// constraints in the Problem, then the remaining equality constraints will
    /// be assigned a weight of mDefaultConstraintWeight.
    Eigen::VectorXd mEqConstraintWeights;

    /// Vector of weights that should be applied to the inequality constraints.
    /// If there are fewer components in this vector than there are inequality
    /// constraints in the Problem, then the remaining inequality constraints
    /// will be assigned a weight of mDefaultConstraintWeight.
    Eigen::VectorXd mIneqConstraintWeights;

    UniqueProperties(
        double _stepMultiplier = 0.1,
        size_t _maxAttempts = 1,
        size_t _perturbationStep = 0,
        double _maxPerturbationFactor = 1.0,
        double _maxRandomizationStep = 1e10,
        double _defaultConstraintWeight = 1.0,
        Eigen::VectorXd _eqConstraintWeights = Eigen::VectorXd(),
        Eigen::VectorXd _ineqConstraintWeights = Eigen::VectorXd() );
  };

  struct Properties : Solver::Properties, UniqueProperties
  {
    Properties(
        const Solver::Properties& _solverProperties = Solver::Properties(),
        const UniqueProperties& _descentProperties = UniqueProperties() );
  };

  /// Default constructor
  explicit GradientDescentSolver(const Properties& _properties = Properties());

  /// Alternative constructor
  explicit GradientDescentSolver(std::shared_ptr<Problem> _problem);

  /// Destructor
  virtual ~GradientDescentSolver();

  // Documentation inherited
  virtual bool solve() override;

  // Documentation inherited
  Eigen::VectorXd getLastConfiguration() const override;

  // Documentation inherited
  virtual std::string getType() const override;

  // Documentation inherited
  virtual std::shared_ptr<Solver> clone() const override;

  /// Set the Properties of this GradientDescentSolver
  void setProperties(const Properties& _properties);

  /// Set the Properties of this GradientDescentSolver
  void setProperties(const UniqueProperties& _properties);

  /// Get the Properties of this GradientDescentSolver
  Properties getGradientDescentProperties() const;

  /// Copy the Properties of another GradientDescentSolver
  void copy(const GradientDescentSolver& _other);

  /// Copy the Properties of another GradientDescentSolver
  GradientDescentSolver& operator=(const GradientDescentSolver& _other);

  void setStepSize(double _newMultiplier);

  double getStepSize() const;

  void setMaxAttempts(size_t _maxAttempts);

  size_t getMaxAttempts() const;

  void setPerturbationStep(size_t _step);

  size_t getPerturbationStep() const;

  void setMaxPerturbationFactor(double _factor);

  double getMaxPerturbationFactor() const;

  void setDefaultConstraintWeight(double _newDefault);

  double getDefaultConstraintWeight() const;

  Eigen::VectorXd& getConstraintWeights();

  const Eigen::VectorXd& getConstraintWeights() const;

  void randomizeConfiguration(Eigen::VectorXd& _x);

  void clampToBoundary(Eigen::VectorXd& _x);

  /// Get the number of iterations used in the last attempt to solve the problem
  size_t getLastNumIterations() const;

protected:

  UniqueProperties mGradientP;

  size_t mLastNumIterations;

  std::random_device mRD;
  std::mt19937 mMT;
  std::uniform_real_distribution<double> mDistribution;

  Eigen::VectorXd mLastConfig;
};

} // namespace optimizer
} // namespace dart

#endif // DART_OPTIMIZER_GRADIENTDESCENTSOLVER_H_
