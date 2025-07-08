#include <orea/counterparty/fvabuilder.hpp>
#include <algorithm>

namespace ore {
namespace analytics {

using namespace QuantLib;

FVABuilder::FVABuilder(const ext::shared_ptr<NPVCube>& cube,
                       const std::string& nettingSetId,
                       const std::vector<Date>& dates,
                       const Handle<YieldTermStructure>& discountCurve,
                       Real fundingSpread)
    : cube_(cube), nettingSetId_(nettingSetId), dates_(dates),
      discountCurve_(discountCurve), fundingSpread_(fundingSpread) {}

Real FVABuilder::calculateFVA() const {
    Real fva = 0.0;

    Size nettingSetIdx = cube_->idsAndIndexes().at(nettingSetId_);
    Size numScenarios = cube_->samples();

    for (Size t = 1; t < dates_.size(); ++t) {
        Date d0 = dates_[t - 1];
        Date d1 = dates_[t];

        Time dt = Actual365Fixed().yearFraction(d0, d1);
        Real df = discountCurve_->discount(d1);

        Real expectedEE = 0.0;
        for (Size s = 0; s < numScenarios; ++s) {
            Real exposure = cube_->get(nettingSetIdx, t, s, 0);
            expectedEE += std::max(exposure, 0.0);
        }
        expectedEE /= static_cast<Real>(numScenarios);

        fva += fundingSpread_ * dt * df * expectedEE;
    }

    return fva;
}

} // namespace analytics
} // namespace ore
