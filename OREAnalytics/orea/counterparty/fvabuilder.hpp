#pragma once

#include <orea/cube/npvcube.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/termstructures/credit/defaultdensitystructure.hpp>
#include <ql/time/date.hpp>

namespace ore {
namespace analytics {

class FVABuilder {
public:
    FVABuilder(const QuantLib::ext::shared_ptr<NPVCube>& cube,
               const std::string& nettingSetId,
               const std::vector<QuantLib::Date>& dates,
               const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
               QuantLib::Real fundingSpread);

    QuantLib::Real calculateFVA() const;

private:
    QuantLib::ext::shared_ptr<NPVCube> cube_;
    std::string nettingSetId_;
    std::vector<QuantLib::Date> dates_;
    QuantLib::Handle<QuantLib::YieldTermStructure> discountCurve_;
    QuantLib::Real fundingSpread_;
};

} // namespace analytics
} // namespace ore
