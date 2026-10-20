#ifndef FIRE_PROTECTION_UNITS_HPP
#define FIRE_PROTECTION_UNITS_HPP

namespace fire_protection {
namespace units {

constexpr double GPM_TO_LPM = 3.78541;
constexpr double LPM_TO_GPM = 1.0 / GPM_TO_LPM;

constexpr double PSI_TO_BAR = 0.0689476;
constexpr double BAR_TO_PSI = 1.0 / PSI_TO_BAR;
constexpr double PSI_TO_KPA = 6.89476;
constexpr double KPA_TO_PSI = 1.0 / PSI_TO_KPA;

constexpr double INCH_TO_MM = 25.4;
constexpr double MM_TO_INCH = 1.0 / INCH_TO_MM;
constexpr double FEET_TO_METER = 0.3048;
constexpr double METER_TO_FEET = 1.0 / FEET_TO_METER;

inline double gpm_to_lpm(double gpm) { return gpm * GPM_TO_LPM; }
inline double lpm_to_gpm(double lpm) { return lpm * LPM_TO_GPM; }

inline double psi_to_bar(double psi) { return psi * PSI_TO_BAR; }
inline double bar_to_psi(double bar) { return bar * BAR_TO_PSI; }

inline double inch_to_mm(double inches) { return inches * INCH_TO_MM; }
inline double mm_to_inch(double mm) { return mm * MM_TO_INCH; }

inline double feet_to_meter(double feet) { return feet * FEET_TO_METER; }
inline double meter_to_feet(double meter) { return meter * METER_TO_FEET; }

} // namespace units
} // namespace fire_protection

#endif // FIRE_PROTECTION_UNITS_HPP
