#include "zhbk.h"

#define PARAM_NAME_LENGTH 256

struct ZHBKConfigParams zhbk_parse_config_params(const char *config_file) {
    struct ZHBKConfigParams params = {};

    // read file contents
    vt_str_t *config_contents = vt_file_read(config_file, NULL);
    
    // split lines
    vt_plist_t *lines = vt_str_split(NULL, config_contents, "\n");
    VT_FOREACH(i, 0, vt_plist_len(lines)) {
        vt_str_t *line = (vt_str_t*)vt_plist_get(lines, i);
        VT_ENFORCE(vt_str_len(line) < PARAM_NAME_LENGTH, "Param name is longer than 256 characters!");

        // skip comments
        if (vt_str_z(line)[0] == '#' || !isalpha(vt_str_z(line)[0])) {
            continue;
        }
        
        // get data
        char name[PARAM_NAME_LENGTH] = {};
        float value = 0;

        // save values (strings)
        if(vt_str_starts_with(vt_str_z(line), "Klass_betona")) {
            sscanf(vt_str_z(line), "%s : %d", name, &params.kd_class);
            continue;
        }

        // save values (floats)
        sscanf(vt_str_z(line), "%s : %f", name, &value);
        if (vt_str_equals(name, "Zdanie_L")) {
            params.zdanie_L = M2MM(value);
        } else if (vt_str_equals(name, "Zdanie_B")) {
            params.zdanie_B = M2MM(value);
        } else if (vt_str_equals(name, "Setka_L")) {
            params.setka_L = M2MM(value);
        } else if (vt_str_equals(name, "Setka_B")) {
            params.setka_B = M2MM(value);
        } else if (vt_str_equals(name, "Vrem_nagruzka")) {
            params.vrem_nagruzka = value;
        } else if (vt_str_equals(name, "Tolsina_sloy_1")) {
            params.tolsina_sloy_1 = M2MM(value);
        } else if (vt_str_equals(name, "Tolsina_sloy_2")) {
            params.tolsina_sloy_2 = M2MM(value);
        } else if (vt_str_equals(name, "Tolsina_sloy_3")) {
            params.tolsina_sloy_3 = M2MM(value);
        } else if (vt_str_equals(name, "Tolsina_sloy_4")) {
            params.tolsina_sloy_4 = M2MM(value);
        } else if (vt_str_equals(name, "Plotnost_sloy_1")) {
            params.plotnost_sloy_1 = value;
        } else if (vt_str_equals(name, "Plotnost_sloy_2")) {
            params.plotnost_sloy_2 = value;
        } else if (vt_str_equals(name, "Plotnost_sloy_3")) {
            params.plotnost_sloy_3 = value;
        } else if (vt_str_equals(name, "Plotnost_sloy_4")) {
            params.plotnost_sloy_4 = value;
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

    /**************** R1 ****************/

    // главная балка
    calc_params.main_beam_length = vt_cmp_minf(params.setka_L, params.setka_B);
    const float main_min_height = calc_params.main_beam_length * 1/15.0;
    const float main_max_height = calc_params.main_beam_length * 1/8.0;
    calc_params.main_beam_height = zhbk_round_50((main_min_height + main_max_height) / 2);
    calc_params.main_beam_width = zhbk_round_50(calc_params.main_beam_height * 0.4);

    // второстепенная балка
    calc_params.second_beam_length = vt_cmp_maxf(params.setka_L, params.setka_B);
    const float second_min_height = calc_params.second_beam_length * 1/20.0;
    const float second_max_height = calc_params.second_beam_length * 1/12.0;
    calc_params.second_beam_height = zhbk_round_50((second_min_height + second_max_height) / 2);
    calc_params.second_beam_width = zhbk_round_50(calc_params.second_beam_height * 0.4);

    // плита
    calc_params.plate_thickness = zhbk_calc_wall_thickness_from_load(params.vrem_nagruzka);
    calc_params.plate_width = zhbk_round_50(calc_params.main_beam_length / 3);

    /**************** R2 ****************/

    // Определение расчетного пролета плиты перекрытия
    const int32_t a1 = 100, a2 = 100;
    const int32_t plate_length = calc_params.plate_width - (a1 + a2);
    calc_params.plate_effective_width = plate_length + a1/2 + a2/2;

    // Временная расчетная нагрузка
    const int32_t running_meter = 1;
    const float temp_load_safety_coef = 1.5;
    calc_params.temp_estimated_load = params.vrem_nagruzka * temp_load_safety_coef * running_meter;

    // Постоянная расчетная нагрузка
    const float G = 9.8;
    const float const_load_safety_coef = 1.35;
    const float g = (params.tolsina_sloy_1 * params.plotnost_sloy_1 * G 
        + params.tolsina_sloy_2 * params.plotnost_sloy_2 * G
        + params.tolsina_sloy_3 * params.plotnost_sloy_3 * G
        + params.tolsina_sloy_4 * params.plotnost_sloy_4 * G)/1000000;
    calc_params.const_estimated_load = g * const_load_safety_coef * running_meter;

    /**************** R3 ****************/

    // Защитный слой бетона
    const float concrete_protect_layer_width_cm = 1.5; // cm

    // Находим суммарную расчетную нагрузку
    calc_params.sum_estimated_load = calc_params.temp_estimated_load + calc_params.const_estimated_load;

    // Находим изгибающий момент в первом/среднем пролете и на первой/средней опоре
    calc_params.bend_moment1 = calc_params.sum_estimated_load * powf(MM2M(calc_params.plate_effective_width), 2) / 11.0;
    calc_params.bend_moment2 = calc_params.sum_estimated_load * powf(MM2M(calc_params.plate_effective_width), 2) / 16.0;

    // Определяем значение коэф. kd1 (первый пролет), kd2 (средний пролет)
    calc_params.coef_kd1 = (MM2CM(calc_params.plate_thickness) - concrete_protect_layer_width_cm)/sqrtf(calc_params.bend_moment1);
    calc_params.coef_kd2 = (MM2CM(calc_params.plate_thickness) - concrete_protect_layer_width_cm)/sqrtf(calc_params.bend_moment2);

    // Находим Ks1 и Ks2
    calc_params.coef_ks1 = zhbk_get_kd_class_value(params.kd_class, calc_params.coef_kd1);
    calc_params.coef_ks2 = zhbk_get_kd_class_value(params.kd_class, calc_params.coef_kd2);

    // Определяем требуемую площадь поперечной арматуры для первого и среднего пролетов
    calc_params.coef_as1 = calc_params.coef_ks1 * calc_params.bend_moment1 / (MM2CM(calc_params.plate_thickness) - concrete_protect_layer_width_cm);
    calc_params.coef_as2 = calc_params.coef_ks2 * calc_params.bend_moment2 / (MM2CM(calc_params.plate_thickness) - concrete_protect_layer_width_cm);

    // Подбор площади сечения арматуры плиты
    calc_params.coef_as1_fact = zhbk_get_asx_fact_value(calc_params.coef_as1, &calc_params.as1_d_armatura, &calc_params.as1_n_armatura);
    calc_params.coef_as2_fact = zhbk_get_asx_fact_value(calc_params.coef_as2, &calc_params.as2_d_armatura, &calc_params.as2_n_armatura);

    // Шаг стержней
    calc_params.armatura_step1_90 = roundf(1000.0 / calc_params.as1_n_armatura / 10) * 10;
    calc_params.armatura_step2_90 = roundf(1000.0 / calc_params.as2_n_armatura / 10) * 10;
    calc_params.armatura_step1_180 = roundf(calc_params.plate_effective_width / 5 / 10) * 10;
    calc_params.armatura_step2_180 = roundf(calc_params.plate_effective_width / 5 / 10) * 10;

    return calc_params;
}

float zhbk_calc_wall_thickness_from_load(const float thickness) {
    if (thickness >= 15) {
        return 100;
    } else if (thickness >= 12 && thickness <= 14) {
        return 90;
    } else if (thickness >= 9 && thickness <= 11) {
        return 80;
    } else if (thickness >= 6 && thickness <= 8) {
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
    while (rval % 50 != 0) {
        rval += 1;
    }

    return (float)rval;
}

float zhbk_get_kd_class_value(const enum ZHBKKdClassHardness kd_class, const float coef_kd) {
    float coef_ks = 0;
    size_t coef_ks_row = 0;
    const size_t rows = sizeof(zhbk_kd_class_table) / sizeof(float) / ZHBK_KD_CLASS_COUNT;
    VT_FOREACH(i, 0, rows) {
        const float coef = zhbk_kd_class_table[i][kd_class];
        const float coef_diff = fabs(coef_kd - coef);
        const float coef_curr_diff = fabs(coef_ks - coef);
        if (coef_diff < coef_curr_diff) {
            coef_ks = coef;
            coef_ks_row = i;
        }
    }

    return zhbk_ks_class_table[coef_ks_row];
}

float zhbk_get_asx_fact_value(const float coef_as, int32_t *d_armatura, int32_t *n_armatura) {
    float coef_as_fact = coef_as;
    const size_t rows = sizeof(zhbk_armatura_table) / sizeof(zhbk_armatura_table[0]);
    VT_FOREACH(i, 3, rows) {
        VT_FOREACH(j, 5, 11) {
            const float coef = zhbk_armatura_table[i][j];
            if(coef_as < coef) {
                coef_as_fact = coef;
                *d_armatura = zhbk_armatura_table[i][0];
                *n_armatura = j;

                return coef_as_fact;
            }
        }
    }

    return coef_as_fact;
}

