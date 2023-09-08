#include "main.h"

int32_t main(void) {
    struct ZHBKConfigParams params = zhbk_parse_config_params("assets/zhbk1.conf");
    printf("%s\t: %f\n", VT_STRING_OF(params.zdanie_L), params.zdanie_L);
    printf("%s\t: %f\n", VT_STRING_OF(params.zdanie_B), params.zdanie_B);
    printf("%s\t: %f\n", VT_STRING_OF(params.setka_L), params.setka_L);
    printf("%s\t: %f\n", VT_STRING_OF(params.setka_B), params.setka_B);
    printf("%s\t: %f\n\n", VT_STRING_OF(params.vrem_nagruzka), params.vrem_nagruzka);

    struct ZHBKCalcParams calc_params = zhbk_calc_params(params);
    printf("%s\t: %f\n", VT_STRING_OF(calc_params.main_beam_length), calc_params.main_beam_length);
    printf("%s\t: %f\n", VT_STRING_OF(calc_params.main_beam_height), calc_params.main_beam_height);
    printf("%s\t: %f\n", VT_STRING_OF(calc_params.main_beam_width), calc_params.main_beam_width);
    printf("%s\t: %f\n", VT_STRING_OF(calc_params.second_beam_length), calc_params.second_beam_length);
    printf("%s\t: %f\n", VT_STRING_OF(calc_params.second_beam_height), calc_params.second_beam_height);
    printf("%s\t: %f\n", VT_STRING_OF(calc_params.second_beam_width), calc_params.second_beam_width);
    printf("%s\t: %f\n", VT_STRING_OF(calc_params.plate_thickness), calc_params.plate_thickness);
    printf("%s\t: %f\n", VT_STRING_OF(calc_params.plate_width), calc_params.plate_width);

    return 0;
}

struct ZHBKConfigParams zhbk_parse_config_params(const char *config_file) {
    struct ZHBKConfigParams params = {};

    // read file contents
    vt_str_t *config_contents = vt_file_read(config_file, NULL);
    
    // split lines
    vt_plist_t *lines = vt_str_split(NULL, config_contents, "\n");
    VT_FOREACH(i, 0, vt_plist_len(lines)) {
        vt_str_t *line = (vt_str_t*)vt_plist_get(lines, i);
        VT_ENFORCE(vt_str_len(line) < 256, "Param name is longer than 256 characters!");

        // skip comments
        if(vt_str_z(line)[0] == '#' || !isalpha(vt_str_z(line)[0])) {
            continue;
        }
        
        // get data
        char name[256] = {};
        float value = 0;
        sscanf(vt_str_z(line), "%s : %f", name, &value);

        // save values
        value = M2MM(value);
        if(vt_str_equals(name, "Zdanie_L")) {
            params.zdanie_L = value;
        } else if(vt_str_equals(name, "Zdanie_B")) {
            params.zdanie_B = value;
        } else if(vt_str_equals(name, "Setka_L")) {
            params.setka_L = value;
        } else if(vt_str_equals(name, "Setka_B")) {
            params.setka_B = value;
        } else if(vt_str_equals(name, "Vrem_nagruzka")) {
            params.vrem_nagruzka = value / 1000;
        }
    }

    // free resources
    vt_str_destroy(config_contents);
    VT_FOREACH(i, 0, vt_plist_len(lines)) {
        vt_str_destroy((vt_str_t*)vt_plist_get(lines, i));
    }

    return params;
}

struct ZHBKCalcParams zhbk_calc_params(const struct ZHBKConfigParams params) {
    struct ZHBKCalcParams calc_params = {}; 
    
    // ---   MAIN BEAM    ---
    calc_params.main_beam_length = vt_cmp_minf(params.setka_L, params.setka_B);
    const float main_min_height = calc_params.main_beam_length * 1/15.0;
    const float main_max_height = calc_params.main_beam_length * 1/8.0;
    calc_params.main_beam_height = zhbk_round_50((main_min_height + main_max_height) / 2);
    calc_params.main_beam_width = zhbk_round_50(calc_params.main_beam_height * 0.4);

    // --- SECONDARY BEAM ---
    calc_params.second_beam_length = vt_cmp_maxf(params.setka_L, params.setka_B);
    const float second_min_height = calc_params.second_beam_length * 1/20.0;
    const float second_max_height = calc_params.second_beam_length * 1/12.0;
    calc_params.second_beam_height = zhbk_round_50((second_min_height + second_max_height) / 2);
    calc_params.second_beam_width = zhbk_round_50(calc_params.second_beam_height * 0.4);

    // ---      PLATE     ---
    calc_params.plate_thickness = zhbk_calc_wall_thickness_from_load(params.vrem_nagruzka);
    calc_params.plate_width = zhbk_round_50(calc_params.main_beam_length / 3);

    return calc_params;
}

float zhbk_calc_wall_thickness_from_load(const float thickness) {
    if(thickness >= 15) {
        return 100;
    } else if(thickness >= 12 && thickness <= 14) {
        return 90;
    } else if(thickness >= 9 && thickness <= 11) {
        return 80;
    } else if(thickness >= 6 && thickness <= 8) {
        return 70;
    } else {
        return 60;
    }
}

float zhbk_round_50(const float value) {
    // smaller multiple
    const int32_t a = (value / 10) * 10;
      
    // larger multiple
    const int32_t b = a + 10;
  
    // get the closest of two
    int32_t rval = (value - a > b - value)? b : a;
    
    // calculate multiple of 50
    while(rval % 50 != 0) {
        rval += 1;
    }

    return (float)rval;
}

