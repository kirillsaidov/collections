#include "main.h"

int32_t main(void) {
    struct ZHBKConfigParams params = zhbk_parse_config_params("assets/zhbk1.conf");
    printf("%34s\n", "PARAMS");
    printf("%34s\n", "--- R1 ---");
    printf("%34s: %.2f\n", VT_STRING_OF(params.zdanie_L), params.zdanie_L);
    printf("%34s: %.2f\n", VT_STRING_OF(params.zdanie_B), params.zdanie_B);
    printf("%34s: %.2f\n", VT_STRING_OF(params.setka_L), params.setka_L);
    printf("%34s: %.2f\n", VT_STRING_OF(params.setka_B), params.setka_B);
    printf("%34s\n", "--- R2 ---");
    printf("%34s: %.2f\n", VT_STRING_OF(params.tolsina_sloy_1), params.tolsina_sloy_1);
    printf("%34s: %.2f\n", VT_STRING_OF(params.tolsina_sloy_2), params.tolsina_sloy_2);
    printf("%34s: %.2f\n", VT_STRING_OF(params.tolsina_sloy_3), params.tolsina_sloy_3);
    printf("%34s: %.2f\n", VT_STRING_OF(params.tolsina_sloy_4), params.tolsina_sloy_4);
    printf("%34s: %.2f\n", VT_STRING_OF(params.plotnost_sloy_1), params.plotnost_sloy_1);
    printf("%34s: %.2f\n", VT_STRING_OF(params.plotnost_sloy_2), params.plotnost_sloy_2);
    printf("%34s: %.2f\n", VT_STRING_OF(params.plotnost_sloy_3), params.plotnost_sloy_3);
    printf("%34s: %.2f\n", VT_STRING_OF(params.plotnost_sloy_4), params.plotnost_sloy_4);
    printf("%34s\n", "--- R3 ---");
    printf("%34s: %s\n\n", VT_STRING_OF(params.concrete_class), params.concrete_class);

    struct ZHBKCalcParams calc_params = zhbk_calc_params(params);
    printf("%34s\n", "CALCULATIONS");
    printf("%34s\n", "--- R1 ---");
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.main_beam_length), calc_params.main_beam_length);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.main_beam_height), calc_params.main_beam_height);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.main_beam_width), calc_params.main_beam_width);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.second_beam_length), calc_params.second_beam_length);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.second_beam_height), calc_params.second_beam_height);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.second_beam_width), calc_params.second_beam_width);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.plate_thickness), calc_params.plate_thickness);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.plate_width), calc_params.plate_width);
    printf("%34s\n", "--- R2 ---");
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.plate_effective_span), calc_params.plate_effective_span);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.temp_estimated_load), calc_params.temp_estimated_load);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.const_estimated_load), calc_params.const_estimated_load);
    printf("%34s\n", "--- R3 ---");

    return 0;
}

