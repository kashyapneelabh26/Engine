// File: OREAnalytics/orea/counterparty/cvabuilder.cpp

#include <orea/counterparty/cvabuilder.hpp>
#include <ql/math/comparison.hpp>
#include <ql/utilities/null.hpp>
#include <algorithm>

namespace ore {
namespace analytics {

using namespace QuantLib;

CVABuilder::CVABuilder(const ext::shared_ptr<NPVCube>& cube,
                       const std::string& nettingSetId,
                       const std::vector<Date>& dates,
                       const Handle<DefaultProbabilityTermStructure>& defaultCurve,
                       Real recoveryRate,
                       const Handle<YieldTermStructure>& discountCurve)
    : cube_(cube), nettingSetId_(nettingSetId), dates_(dates),
      defaultCurve_(defaultCurve), recoveryRate_(recoveryRate),
      discountCurve_(discountCurve) {}

Real CVABuilder::calculateCVA() const {
    Real cva = 0.0;

    // Use ORE-standard methods
    Size nettingSetIdx = cube_->idsAndIndexes().at(nettingSetId_);
    Size numScenarios = cube_->samples();

    for (Size t = 1; t < dates_.size(); ++t) {
        Date d0 = dates_[t - 1];
        Date d1 = dates_[t];

        Real pd = defaultCurve_->defaultProbability(d0, d1);
        Real df = discountCurve_->discount(d1);

        // Expected positive exposure (EPE)
        Real expectedEE = 0.0;
        for (Size s = 0; s < numScenarios; ++s) {
            Real exposure = cube_->get(nettingSetIdx, t, s, 0);  // use depth 0
            expectedEE += std::max(exposure, 0.0);
        }
        expectedEE /= static_cast<Real>(numScenarios);

        cva += (1.0 - recoveryRate_) * df * expectedEE * pd;
    }

    return cva;
}

} // namespace analytics
} // namespace ore
