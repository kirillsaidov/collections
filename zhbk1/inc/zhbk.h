#ifndef ZHBK_H
#define ZHBK_H

#include <math.h>
#include "vita/vita.h"
#include "tabledata.h"
#include "language.h"

// meters to millimeters
#define M2MM(m) (m * 1000)

// millimeters to meters
#define MM2M(m) (m / 1000)

// millimeters to centimeters
#define MM2CM(m) (m / 10)

// ditto
#define ZHBK_INPUT_LABEL_LENGTH 32

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

        // R3
    enum ZHBKKdClassHardness kd_class;
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
        plate_effective_width,
        temp_estimated_load,
        const_estimated_load,

        // R3
        sum_estimated_load,
        bend_moment1,
        bend_moment2,
        coef_kd1,
        coef_kd2,
        coef_ks1,
        coef_ks2,
        coef_as1,
        coef_as2,
        coef_as1_fact,
        coef_as2_fact,
        armatura_step1_90,
        armatura_step2_90,
        armatura_step1_180,
        armatura_step2_180;

    int32_t
        as1_d_armatura,
        as1_n_armatura,
        as2_d_armatura,
        as2_n_armatura;
};

extern struct ZHBKConfigParams zhbk_parse_config_params(const char *config_file);
extern struct ZHBKConfigParams zhbk_parse_params(const char zhbk_input_text[ZHBK_LABEL_COUNT][ZHBK_INPUT_LABEL_LENGTH]);
extern struct ZHBKCalcParams zhbk_calc_params(const struct ZHBKConfigParams params);

extern float zhbk_calc_wall_thickness_from_load(const float thickness);
extern float zhbk_round_50(const float value);
extern float zhbk_get_kd_class_value(const enum ZHBKKdClassHardness kd_class, const float coef_kd);
extern float zhbk_get_asx_fact_value(const float coef_as, int32_t *d_armatura, int32_t *n_armatura);
extern enum ZHBKKdClassHardness zhbk_conv_str_to_kd_class_hardness(const char *const text);

#endif // ZHBK_H