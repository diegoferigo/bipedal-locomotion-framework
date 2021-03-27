/**
 * @file LinearizedFrictionConeTest.cpp
 * @authors Giulio Romualdi
 * @copyright 2021 Istituto Italiano di Tecnologia (IIT). This software may be modified and
 * distributed under the terms of the GNU Lesser General Public License v2.1 or any later version.
 */

// Catch2
#include <catch2/catch.hpp>

#include <BipedalLocomotion/Math/LinearizedFrictionCone.h>
#include <BipedalLocomotion/ParametersHandler/StdImplementation.h>

using namespace BipedalLocomotion::Math;
using namespace BipedalLocomotion::ParametersHandler;

TEST_CASE("Linearized Friction Cone")
{
    auto params = std::make_shared<StdImplementation>();
    params->setParameter("number_of_slices", 2);
    params->setParameter("static_friction_coefficient", 0.3);

    LinearizedFrictionCone cone;
    REQUIRE(cone.initialize(params));

    // test the solution
    REQUIRE(cone.getB().isApprox(Eigen::VectorXd::Zero(8)));
    Eigen::MatrixXd matlabSolution(8, 3);
    matlabSolution << 2.4142,  1.0000, -0.7243,
                      0.4142,  1.0000, -0.3000,
                     -0.4142,  1.0000, -0.3000,
                     -2.4142,  1.0000, -0.7243,
                     -2.4142, -1.0000, -0.7243,
                     -0.4142, -1.0000, -0.3000,
                      0.4142, -1.0000, -0.3000,
                      2.4142, -1.0000, -0.7243;

    constexpr double tolerance = 1e-4;
    REQUIRE(matlabSolution.isApprox(cone.getA(), tolerance));
}