#include "vita/vita.h"

// meters to millimeters
#define M2MM(m) (m * 1000)

struct ZHBKConfigParams {
    float 
        zdanie_L, 
        zdanie_B, 
        setka_L, 
        setka_B, 
        vrem_nagruzka;
};

struct ZHBKCalcParams {
    float 
        main_beam_length,
        main_beam_height,
        main_beam_width,
        second_beam_length,
        second_beam_height,
        second_beam_width,
        plate_thickness,
        plate_width;
};

struct ZHBKConfigParams zhbk_parse_config_params(const char *config_file);
struct ZHBKCalcParams zhbk_calc_params(const struct ZHBKConfigParams params);
float zhbk_calc_wall_thickness_from_load(const float thickness);
float zhbk_round_50(const float value);
