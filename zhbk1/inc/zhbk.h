#include "vita/vita.h"

// meters to millimeters
#define M2MM(m) (m * 1000)

// millimeters to meters
#define MM2M(m) (m / 1000)

struct ZHBKConfigParams {
    float 
        // R1
        zdanie_L, 
        zdanie_B, 
        setka_L, 
        setka_B, 
        vrem_nagruzka,
        
        // R2
        tolsina_sloy_1,
        tolsina_sloy_2,
        tolsina_sloy_3,
        tolsina_sloy_4,
        plotnost_sloy_1,
        plotnost_sloy_2,
        plotnost_sloy_3,
        plotnost_sloy_4;
};

struct ZHBKCalcParams {
    float 
        // R1
        main_beam_length,
        main_beam_height,
        main_beam_width,
        second_beam_length,
        second_beam_height,
        second_beam_width,
        plate_thickness,
        plate_width,

        // R2
        plate_effective_span,
        temp_estimated_load,
        const_estimated_load;
};

struct ZHBKConfigParams zhbk_parse_config_params(const char *config_file);
struct ZHBKCalcParams zhbk_calc_params(const struct ZHBKConfigParams params);
float zhbk_calc_wall_thickness_from_load(const float thickness);
float zhbk_round_50(const float value);

