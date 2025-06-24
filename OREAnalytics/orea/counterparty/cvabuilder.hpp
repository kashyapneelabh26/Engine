#pragma once

#include <orea/cube/npvcube.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/termstructures/defaulttermstructure.hpp>
#include <ql/time/date.hpp>
#include <ql/types.hpp>
#include <vector>

namespace ore {
namespace analytics {

class CVABuilder {
public:
    CVABuilder(const QuantLib::ext::shared_ptr<NPVCube>& cube,
               const std::string& nettingSetId,
               const std::vector<QuantLib::Date>& dates,
               const QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure>& defaultCurve,
               QuantLib::Real recoveryRate,
               const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve);

    QuantLib::Real calculateCVA() const;

private:
    QuantLib::ext::shared_ptr<NPVCube> cube_;
    std::string nettingSetId_;
    std::vector<QuantLib::Date> dates_;
    QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> defaultCurve_;
    QuantLib::Real recoveryRate_;
    QuantLib::Handle<QuantLib::YieldTermStructure> discountCurve_;
};

} // namespace analytics
} // namespace ore
