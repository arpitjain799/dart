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

#include "dart/math/math.hpp"
#include "dart/test/math/GTestUtils.hpp"

#include <gtest/gtest.h>

#include <iostream>

using namespace dart;
using namespace math;
using namespace Eigen;

#define LIE_GROUP_OPT_TOL 1e-12

/******************************************************************************/
math::Matrix4d toMatrixForm(const math::Vector6d& v)
{
  math::Matrix4d result = math::Matrix4d::Zero();

  result(0, 1) = -v(2);
  result(1, 0) = v(2);
  result(0, 2) = v(1);
  result(2, 0) = -v(1);
  result(1, 2) = -v(0);
  result(2, 1) = v(0);

  result(0, 3) = v(3);
  result(1, 3) = v(4);
  result(2, 3) = v(5);

  return result;
}

/******************************************************************************/
math::Vector6d fromMatrixForm(const math::Matrix4d& m)
{
  math::Vector6d ret;
  ret << m(2, 1), m(0, 2), m(1, 0), m(0, 3), m(1, 3), m(2, 3);
  return ret;
}

/******************************************************************************/
void testEulerAngles(const math::Vector3d& angle)
{
  math::Matrix3d mat1;
  math::Matrix3d mat2;

  // XYX
  mat1 = math::eulerXYXToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitX())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitY())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitX());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  EXPECT_TRUE(test::equals(mat1, eulerXYXToMatrix(matrixToEulerXYX(mat1))));

  // XYZ
  mat1 = math::eulerXYZToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitX())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitY())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitZ());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  EXPECT_TRUE(test::equals(mat1, eulerXYZToMatrix(matrixToEulerXYZ(mat1))));

  // XZX
  mat1 = math::eulerXZXToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitX())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitZ())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitX());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  // EXPECT_TRUE(equals(mat1, eulerXZXToMatrix(matrixToEulerXZX(mat1))));

  // XZY
  mat1 = math::eulerXZYToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitX())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitZ())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitY());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  EXPECT_TRUE(test::equals(mat1, eulerXZYToMatrix(matrixToEulerXZY(mat1))));

  // YXY
  mat1 = math::eulerYXYToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitY())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitX())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitY());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  // EXPECT_TRUE(equals(mat1, eulerYXYToMatrix(matrixToEulerYXY(mat1))));

  // YXZ
  mat1 = math::eulerYXZToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitY())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitX())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitZ());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  EXPECT_TRUE(test::equals(mat1, eulerYXZToMatrix(matrixToEulerYXZ(mat1))));

  // YZX
  mat1 = math::eulerYZXToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitY())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitZ())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitX());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  EXPECT_TRUE(test::equals(mat1, eulerYZXToMatrix(matrixToEulerYZX(mat1))));

  // YZY
  mat1 = math::eulerYZYToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitY())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitZ())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitY());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  // EXPECT_TRUE(equals(mat1, eulerYZYToMatrix(matrixToEulerYZY(mat1))));

  // ZXY
  mat1 = math::eulerZXYToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitZ())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitX())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitY());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  EXPECT_TRUE(test::equals(mat1, eulerZXYToMatrix(matrixToEulerZXY(mat1))));

  // ZYX
  mat1 = math::eulerZYXToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitZ())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitY())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitX());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  EXPECT_TRUE(test::equals(mat1, eulerZYXToMatrix(matrixToEulerZYX(mat1))));

  // ZXZ
  mat1 = math::eulerZXZToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitZ())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitX())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitZ());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  // EXPECT_TRUE(equals(mat1, eulerZXZToMatrix(matrixToEulerZXZ(mat1))));

  // ZYZ
  mat1 = math::eulerZYZToMatrix(angle);
  mat2 = math::AngleAxisd(angle(0), math::Vector3d::UnitZ())
         * math::AngleAxisd(angle(1), math::Vector3d::UnitY())
         * math::AngleAxisd(angle(2), math::Vector3d::UnitZ());

  EXPECT_TRUE(math::verifyRotation(mat1));
  EXPECT_TRUE(math::verifyRotation(mat2));
  EXPECT_TRUE(test::equals(mat1, mat2));
  // EXPECT_TRUE(equals(mat1, eulerZYZToMatrix(matrixToEulerZYZ(mat1))));
}

/******************************************************************************/
TEST(LIE_GROUP_OPERATORS, EULER_ANGLES)
{
  // TODO: Special angles such as (PI, 0, 0)

  //
  int numTest = 1;
  for (int i = 0; i < numTest; ++i) {
    math::Vector3d angle = math::Vector3d::Random();
    testEulerAngles(angle);
  }
}

/******************************************************************************/
#define EPSILON_EXPMAP_THETA 1.0e-3
TEST(LIE_GROUP_OPERATORS, EXPONENTIAL_MAPPINGS)
{
  int numTest = 100;

  // Exp
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd s = math::SE3Tangentd::Random();
    math::Isometry3d Exp_s = s.exp().toIsometry3();
    math::Matrix4d Exp_s_2 = math::Matrix4d::Identity();

    double theta = s.params().head<3>().norm();
    math::Matrix3d R = Matrix3d::Zero();
    math::Matrix3d qss = skew(s.params().head<3>());
    math::Matrix3d qss2 = qss * qss;
    math::Matrix3d P = math::Matrix3d::Zero();

    if (theta < EPSILON_EXPMAP_THETA) {
      R = Matrix3d::Identity() + qss + 0.5 * qss2;
      P = Matrix3d::Identity() + 0.5 * qss + (1 / 6) * qss2;
    } else {
      R = Matrix3d::Identity() + (sin(theta) / theta) * qss
          + ((1 - cos(theta)) / (theta * theta)) * qss2;
      P = Matrix3d::Identity() + ((1 - cos(theta)) / (theta * theta)) * qss
          + ((theta - sin(theta)) / (theta * theta * theta)) * qss2;
    }

    Exp_s_2.topLeftCorner<3, 3>() = R;
    Exp_s_2.topRightCorner<3, 1>() = P * s.params().tail<3>();

    //
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        EXPECT_NEAR(Exp_s(i, j), Exp_s_2(i, j), LIE_GROUP_OPT_TOL);
  }

  // ExpAngular
  for (int i = 0; i < numTest; ++i) {
    math::Vector6d s = math::Vector6d::Random();
    s.tail<3>() = math::Vector3d::Zero();
    math::Isometry3d Exp_s = math::expAngular(s.head<3>());
    math::Matrix4d Exp_s_2 = math::Matrix4d::Identity();

    double theta = s.head<3>().norm();
    math::Matrix3d R = Matrix3d::Zero();
    math::Matrix3d qss = skew(s.head<3>());
    math::Matrix3d qss2 = qss * qss;
    math::Matrix3d P = math::Matrix3d::Zero();

    if (theta < EPSILON_EXPMAP_THETA) {
      R = Matrix3d::Identity() + qss + 0.5 * qss2;
      P = Matrix3d::Identity() + 0.5 * qss + (1 / 6) * qss2;
    } else {
      R = Matrix3d::Identity() + (sin(theta) / theta) * qss
          + ((1 - cos(theta)) / (theta * theta)) * qss2;
      P = Matrix3d::Identity() + ((1 - cos(theta)) / (theta * theta)) * qss
          + ((theta - sin(theta)) / (theta * theta * theta)) * qss2;
    }

    Exp_s_2.topLeftCorner<3, 3>() = R;
    Exp_s_2.topRightCorner<3, 1>() = P * s.tail<3>();

    //
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        EXPECT_NEAR(Exp_s(i, j), Exp_s_2(i, j), LIE_GROUP_OPT_TOL);
  }

  // ExpLinear
  for (int i = 0; i < numTest; ++i) {
    math::Vector6d s = math::Vector6d::Random();
    s.head<3>() = math::Vector3d::Zero();
    math::Isometry3d Exp_s(math::Translation3d(s.tail<3>()));
    math::Matrix4d Exp_s_2 = math::Matrix4d::Identity();

    double theta = s.head<3>().norm();
    math::Matrix3d R = Matrix3d::Zero();
    math::Matrix3d qss = skew(s.head<3>());
    math::Matrix3d qss2 = qss * qss;
    math::Matrix3d P = math::Matrix3d::Zero();

    if (theta < EPSILON_EXPMAP_THETA) {
      R = Matrix3d::Identity() + qss + 0.5 * qss2;
      P = Matrix3d::Identity() + 0.5 * qss + (1 / 6) * qss2;
    } else {
      R = Matrix3d::Identity() + (sin(theta) / theta) * qss
          + ((1 - cos(theta)) / (theta * theta)) * qss2;
      P = Matrix3d::Identity() + ((1 - cos(theta)) / (theta * theta)) * qss
          + ((theta - sin(theta)) / (theta * theta * theta)) * qss2;
    }

    Exp_s_2.topLeftCorner<3, 3>() = R;
    Exp_s_2.topRightCorner<3, 1>() = P * s.tail<3>();

    //
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        EXPECT_NEAR(Exp_s(i, j), Exp_s_2(i, j), LIE_GROUP_OPT_TOL);
  }
  // Exponential mapping test with high values
  int numExpTests = 100;
  double min = -1e+128;
  double max = +1e+128;

  for (int idxTest = 0; idxTest < numExpTests; ++idxTest) {
    math::Vector3d randomS = math::Vector3d::Zero();

    for (int i = 0; i < 3; ++i)
      randomS[i] = Uniform(min, max);

    math::Isometry3d T = math::expAngular(randomS);
    EXPECT_TRUE(math::verifyTransform(T));
  }

  for (int idxTest = 0; idxTest < numExpTests; ++idxTest) {
    math::SE3Tangentd randomS = math::SE3Tangentd::Random();
    math::Isometry3d T = randomS.exp().toIsometry3();
    EXPECT_TRUE(math::verifyTransform(T));
  }
}

/******************************************************************************/
TEST(LIE_GROUP_OPERATORS, ADJOINT_MAPPINGS)
{
  int numTest = 100;

  // AdT(V) == T * V * InvT
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Vector6d V = math::Vector6d::Random();

    math::Vector6d AdTV = AdT(T, V);

    // Ad(T, V) = T * [V] * InvT
    math::Matrix4d T_V_InvT
        = T.matrix() * toMatrixForm(V) * T.inverse().matrix();
    math::Vector6d T_V_InvT_se3 = fromMatrixForm(T_V_InvT);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(AdTV(j), T_V_InvT_se3(j), LIE_GROUP_OPT_TOL);

    // Ad(T, V) = [R 0; [p]R R] * V
    math::Matrix6d AdTMatrix = math::Matrix6d::Zero();
    AdTMatrix.topLeftCorner<3, 3>() = T.linear();
    AdTMatrix.bottomRightCorner<3, 3>() = T.linear();
    AdTMatrix.bottomLeftCorner<3, 3>() = skew(T.translation()) * T.linear();
    math::Vector6d AdTMatrix_V = AdTMatrix * V;
    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(AdTV(j), AdTMatrix_V(j), LIE_GROUP_OPT_TOL);
  }

  // AdR == AdT([R 0; 0 1], V)
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Isometry3d R = math::Isometry3d::Identity();
    R.linear() = T.linear();
    math::Vector6d V = math::Vector6d::Random();

    math::Vector6d AdTV = AdT(R, V);
    math::Vector6d AdRV = AdR(T, V);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(AdTV(j), AdRV(j), LIE_GROUP_OPT_TOL);
  }

  // AdTAngular == AdT(T, se3(w, 0))
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Vector3d w = math::Vector3d::Random();
    math::Vector6d V = math::Vector6d::Zero();
    V.head<3>() = w;

    math::Vector6d AdTV = AdT(T, V);
    math::Vector6d AdTAng = AdTAngular(T, w);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(AdTV(j), AdTAng(j), LIE_GROUP_OPT_TOL);
  }

  // AdTLinear == AdT(T, se3(w, 0))
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Vector3d v = math::Vector3d::Random();
    math::Vector6d V = math::Vector6d::Zero();
    V.tail<3>() = v;

    math::Vector6d AdTV = AdT(T, V);
    math::Vector6d AdTLin = AdTLinear(T, v);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(AdTV(j), AdTLin(j), LIE_GROUP_OPT_TOL);
  }

  // AdTJac
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Vector3d v = math::Vector3d::Random();
    math::Vector6d V = math::Vector6d::Zero();
    V.tail<3>() = v;

    math::Vector6d AdTV = AdT(T, V);
    math::Vector6d AdTLin = AdTLinear(T, v);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(AdTV(j), AdTLin(j), LIE_GROUP_OPT_TOL);
  }

  // AdInvT
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Isometry3d InvT = T.inverse();
    math::Vector6d V = math::Vector6d::Random();

    math::Vector6d Ad_InvT = AdT(InvT, V);
    math::Vector6d AdInv_T = AdInvT(T, V);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(Ad_InvT(j), AdInv_T(j), LIE_GROUP_OPT_TOL);
  }

  // AdInvRLinear
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Vector3d v = math::Vector3d::Random();
    math::Vector6d V = math::Vector6d::Zero();
    V.tail<3>() = v;
    math::Isometry3d R = math::Isometry3d::Identity();
    R.linear() = T.linear();

    math::Vector6d AdT_ = AdT(R.inverse(), V);
    math::Vector6d AdInvRLinear_ = AdInvRLinear(T, v);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(AdT_(j), AdInvRLinear_(j), LIE_GROUP_OPT_TOL);
  }

  // dAdT
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Vector6d F = math::Vector6d::Random();

    math::Vector6d dAdTF = dAdT(T, F);

    // dAd(T, F) = [R 0; [p]R R]^T * F
    math::Matrix6d AdTMatrix = math::Matrix6d::Zero();
    AdTMatrix.topLeftCorner<3, 3>() = T.linear();
    AdTMatrix.bottomRightCorner<3, 3>() = T.linear();
    AdTMatrix.bottomLeftCorner<3, 3>() = skew(T.translation()) * T.linear();
    math::Vector6d AdTTransMatrix_V = AdTMatrix.transpose() * F;
    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(dAdTF(j), AdTTransMatrix_V(j), LIE_GROUP_OPT_TOL);
  }

  // dAdInvT
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Isometry3d InvT = T.inverse();
    math::Vector6d F = math::Vector6d::Random();

    math::Vector6d dAdInvT_F = dAdInvT(T, F);

    //
    math::Vector6d dAd_InvTF = dAdT(InvT, F);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(dAdInvT_F(j), dAd_InvTF(j), LIE_GROUP_OPT_TOL);

    // dAd(T, F) = [R 0; [p]R R]^T * F
    math::Matrix6d AdInvTMatrix = math::Matrix6d::Zero();
    AdInvTMatrix.topLeftCorner<3, 3>() = InvT.linear();
    AdInvTMatrix.bottomRightCorner<3, 3>() = InvT.linear();
    AdInvTMatrix.bottomLeftCorner<3, 3>()
        = skew(InvT.translation()) * InvT.linear();
    math::Vector6d AdInvTTransMatrix_V = AdInvTMatrix.transpose() * F;
    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(dAdInvT_F(j), AdInvTTransMatrix_V(j), LIE_GROUP_OPT_TOL);
  }

  // dAdInvR
  for (int i = 0; i < numTest; ++i) {
    math::SE3Tangentd t = math::SE3Tangentd::Random();
    math::Isometry3d T = t.exp().toIsometry3();
    math::Isometry3d InvT = T.inverse();
    math::Isometry3d InvR = math::Isometry3d::Identity();
    InvR.linear() = InvT.linear();
    math::Vector6d F = math::Vector6d::Random();

    math::Vector6d dAdInvR_F = dAdInvR(T, F);

    //
    math::Vector6d dAd_InvTF = dAdT(InvR, F);

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(dAdInvR_F(j), dAd_InvTF(j), LIE_GROUP_OPT_TOL);
  }

  // ad
  for (int i = 0; i < numTest; ++i) {
    math::Vector6d V = math::Vector6d::Random();
    math::Vector6d W = math::Vector6d::Random();

    math::Vector6d ad_V_W = ad(V, W);

    //
    math::Matrix6d adV_Matrix = math::Matrix6d::Zero();
    adV_Matrix.topLeftCorner<3, 3>() = skew(V.head<3>());
    adV_Matrix.bottomRightCorner<3, 3>() = skew(V.head<3>());
    adV_Matrix.bottomLeftCorner<3, 3>() = skew(V.tail<3>());
    math::Vector6d adV_Matrix_W = adV_Matrix * W;

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(ad_V_W(j), adV_Matrix_W(j), LIE_GROUP_OPT_TOL);
  }

  // dad
  for (int i = 0; i < numTest; ++i) {
    math::Vector6d V = math::Vector6d::Random();
    math::Vector6d F = math::Vector6d::Random();

    math::Vector6d dad_V_F = dad(V, F);

    //
    math::Matrix6d dadV_Matrix = math::Matrix6d::Zero();
    dadV_Matrix.topLeftCorner<3, 3>() = skew(V.head<3>());
    dadV_Matrix.bottomRightCorner<3, 3>() = skew(V.head<3>());
    dadV_Matrix.bottomLeftCorner<3, 3>() = skew(V.tail<3>());
    math::Vector6d dadV_Matrix_F = dadV_Matrix.transpose() * F;

    for (int j = 0; j < 6; ++j)
      EXPECT_NEAR(dad_V_F(j), dadV_Matrix_F(j), LIE_GROUP_OPT_TOL);
  }
}
