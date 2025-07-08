#include <orea/counterparty/dvabuilder.hpp>
#include <algorithm>
#include <ql/termstructures/credit/defaultdensitystructure.hpp>

namespace ore {
namespace analytics {

using namespace QuantLib;

DVABuilder::DVABuilder(const ext::shared_ptr<NPVCube>& cube,
                       const std::string& nettingSetId,
                       const std::vector<Date>& dates,
                       const Handle<DefaultProbabilityTermStructure>& defaultCurve,
                       Real recoveryRate,
                       const Handle<YieldTermStructure>& discountCurve)
    : cube_(cube), nettingSetId_(nettingSetId), dates_(dates),
      defaultCurve_(defaultCurve), recoveryRate_(recoveryRate),
      discountCurve_(discountCurve) {}

Real DVABuilder::calculateDVA() const {
    Real dva = 0.0;

    Size nettingSetIdx = cube_->idsAndIndexes().at(nettingSetId_);
    Size numScenarios = cube_->samples();

    for (Size t = 1; t < dates_.size(); ++t) {
        Date d0 = dates_[t - 1];
        Date d1 = dates_[t];

        Real pd = defaultCurve_->defaultProbability(d0, d1);
        Real df = discountCurve_->discount(d1);

        Real expectedNE = 0.0;
        for (Size s = 0; s < numScenarios; ++s) {
            Real exposure = cube_->get(nettingSetIdx, t, s, 0);
            expectedNE += std::min(exposure, 0.0);  // note: take negative part
        }
        expectedNE /= static_cast<Real>(numScenarios);

        dva += (1.0 - recoveryRate_) * df * (-expectedNE) * pd;
    }

    return dva;
}

} // namespace analytics
} // namespace ore
