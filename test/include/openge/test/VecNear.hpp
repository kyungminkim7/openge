#pragma once

#include <glm/gtc/epsilon.hpp>
#include <glm/vector_relational.hpp>
#include <openge/test/Vector.hpp>
#include <ostream>

namespace ge {
namespace test {

/**
 * GTest matcher for testing whether glm::vec types are
 * approximately equal.
 */
template <typename Vector>
class VecNear {
 public:
  using is_gtest_matcher = void;
  using ValueType = typename Vector::value_type;

  explicit VecNear(const Vector& rhs, ValueType maxAbsError)
      : rhs(rhs), maxAbsError(maxAbsError) {}

  bool MatchAndExplain(const Vector& lhs, std::ostream*) const {
    return glm::all(glm::epsilonEqual(lhs, rhs, maxAbsError));
  }

  void DescribeTo(std::ostream* os) const {
    *os << "is approximately " << rhs << " (absolute error <= " << maxAbsError
        << ")";
  }

  void DescribeNegationTo(std::ostream* os) const {
    *os << "isn't approximately " << rhs << " (absolute error > " << maxAbsError
        << ")";
  }

 private:
  Vector rhs;
  ValueType maxAbsError;
};

}  //  namespace test
}  //  namespace ge
