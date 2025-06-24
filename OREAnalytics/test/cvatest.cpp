#include <orea/counterparty/cvabuilder.hpp>
#include <orea/cube/inmemorycube.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/credit/flathazardrate.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <ql/settings.hpp>
#include <iostream>
#include <set>

using namespace QuantLib;
using namespace ore::analytics;
using ore::analytics::DoublePrecisionInMemoryCube;

int main() {
    // Set evaluation date
    Date today(24, June, 2025);
    Settings::instance().evaluationDate() = today;

    // Define time grid
    std::vector<Date> dates = {today, today + 30, today + 60, today + 90};
    std::set<std::string> nettingSetIds = {"NET1"};

    // Create cube: 1 netting set, 4 dates, 2 scenarios, 1 depth level
    auto cube = QuantLib::ext::make_shared<DoublePrecisionInMemoryCube>(
        today, nettingSetIds, dates, 2, 1, 0.0);

    // Set positive exposures for each scenario at t1, t2, t3
    for (Size s = 0; s < 2; ++s) {
        cube->set(100.0, 0, 1, s, 0);  // t1
        cube->set(80.0, 0, 2, s, 0);   // t2
        cube->set(50.0, 0, 3, s, 0);   // t3
    }

    // Flat 1% hazard rate (default curve)
    Handle<DefaultProbabilityTermStructure> defaultCurve(
        QuantLib::ext::make_shared<FlatHazardRate>(today, 0.01, Actual365Fixed()));

    // Flat 2% interest rate (discount curve)
    Handle<YieldTermStructure> discountCurve(
        QuantLib::ext::make_shared<FlatForward>(today, 0.02, Actual365Fixed()));

    Real recoveryRate = 0.4;

    // Run CVA calculation
    CVABuilder builder(cube, "NET1", dates, defaultCurve, recoveryRate, discountCurve);
    Real cva = builder.calculateCVA();

    std::cout << "CVA = " << cva << std::endl;
    return 0;
}
