#ifndef ZHBK_LANGUAGE_H
#define ZHBK_LANGUAGE_H

enum ZHBKLanguage {
    ZHBK_LANGUAGE_RUSSIAN,
    ZHBK_LANGUAGE_KAZAKH,
    ZHBK_LANGAUGE_COUNT
};

enum ZHBKLabel {
    // labels
    ZHBK_LABEL_INPUT,
    ZHBK_LABEL_OUTPUT,
    ZHBK_LABEL_LANGUAGE,
    ZHBK_LABEL_LANGUAGE_RU,
    ZHBK_LABEL_LANGUAGE_KZ,
    ZHBK_LABEL_CALCULATE,

    // input variables
    ZHBK_LABEL_ZDANIE_L,
    ZHBK_LABEL_ZDANIE_B,
    ZHBK_LABEL_SETKA_L,
    ZHBK_LABEL_SETKA_B,
    ZHBK_LABEL_VREM_NAGRUZKA,
    ZHBK_LABEL_TOLSINA_SLOY_1,
    ZHBK_LABEL_TOLSINA_SLOY_2,
    ZHBK_LABEL_TOLSINA_SLOY_3,
    ZHBK_LABEL_TOLSINA_SLOY_4,
    ZHBK_LABEL_PLOTNOST_SLOY_1,
    ZHBK_LABEL_PLOTNOST_SLOY_2,
    ZHBK_LABEL_PLOTNOST_SLOY_3,
    ZHBK_LABEL_PLOTNOST_SLOY_4,
    ZHBK_LABEL_KLASS_BETONA,

    // output variables
    ZHBK_LABEL_MAIN_BEAM_LENGTH,
    ZHBK_LABEL_MAIN_BEAM_HEIGHT,
    ZHBK_LABEL_MAIN_BEAM_WIDTH,
    ZHBK_LABEL_SECOND_BEAM_LENGTH,
    ZHBK_LABEL_SECOND_BEAM_HEIGHT,
    ZHBK_LABEL_SECOND_BEAM_WIDTH,
    ZHBK_LABEL_PLATE_THICKNESS,
    ZHBK_LABEL_PLATE_WIDTH,
    ZHBK_LABEL_PLATE_EFFECTIVE_WIDTH,
    ZHBK_LABEL_TEMP_ESTIMATED_LOAD,
    ZHBK_LABEL_CONST_ESTIMATED_LOAD,
    ZHBK_LABEL_SUM_ESTIMATED_LOAD,
    ZHBK_LABEL_BEND_MOMENT_1,
    ZHBK_LABEL_BEND_MOMENT_2,
    ZHBK_LABEL_COEF_KD_1,
    ZHBK_LABEL_COEF_KD_2,
    ZHBK_LABEL_COEF_KS_1,
    ZHBK_LABEL_COEF_KS_2,
    ZHBK_LABEL_COEF_AS_1,
    ZHBK_LABEL_COEF_AS_2,
    ZHBK_LABEL_COEF_AS_1_FACT,
    ZHBK_LABEL_COEF_AS_2_FACT,
    ZHBK_LABEL_ARMATURA_STEP1_90,
    ZHBK_LABEL_ARMATURA_STEP2_90,
    ZHBK_LABEL_ARMATURA_STEP1_180,
    ZHBK_LABEL_ARMATURA_STEP2_180,
    ZHBK_LABEL_ARMATURA_AS1_D,
    ZHBK_LABEL_ARMATURA_AS1_N,
    ZHBK_LABEL_ARMATURA_AS2_D,
    ZHBK_LABEL_ARMATURA_AS2_N,

    // measure units
    ZHBK_LABEL_METERS,
    ZHBK_LABEL_KNM2,
    ZHBK_LABEL_KGM3,
    ZHBK_LABEL_COD_BETONA,

    ZHBK_LABEL_COUNT
};

static const char zhbk_label[ZHBK_LABEL_COUNT][ZHBK_LANGAUGE_COUNT][512] = {
    // label                                 russian             kazakh
    [ZHBK_LABEL_INPUT]                   = { "Введите данные",          "hello" }, 
    [ZHBK_LABEL_OUTPUT]                  = { "Рассчёт",                 "hello" }, 
    [ZHBK_LABEL_LANGUAGE]                = { "Язык",                    "hello" }, 
    [ZHBK_LABEL_LANGUAGE_RU]             = { "Русский",                 "hello" }, 
    [ZHBK_LABEL_LANGUAGE_KZ]             = { "Казахский",               "hello" }, 
    [ZHBK_LABEL_CALCULATE]               = { "Рассчитать",              "hello" }, 

    // input variables
    [ZHBK_LABEL_ZDANIE_L]                = { "Zdanie_L",                "hello" }, 
    [ZHBK_LABEL_ZDANIE_B]                = { "Zdanie_B",                "hello" }, 
    [ZHBK_LABEL_SETKA_L]                 = { "Setka_L",                 "hello" }, 
    [ZHBK_LABEL_SETKA_B]                 = { "Setka_B",                 "hello" }, 
    [ZHBK_LABEL_VREM_NAGRUZKA]           = { "Vrem_nagruzka",           "hello" },
    [ZHBK_LABEL_TOLSINA_SLOY_1]          = { "Tolsina_sloy_1",          "hello" },
    [ZHBK_LABEL_TOLSINA_SLOY_2]          = { "Tolsina_sloy_2",          "hello" },
    [ZHBK_LABEL_TOLSINA_SLOY_3]          = { "Tolsina_sloy_3",          "hello" },
    [ZHBK_LABEL_TOLSINA_SLOY_4]          = { "Tolsina_sloy_4",          "hello" },
    [ZHBK_LABEL_PLOTNOST_SLOY_1]         = { "Plotnost_sloy_1",         "hello" },
    [ZHBK_LABEL_PLOTNOST_SLOY_2]         = { "Plotnost_sloy_2",         "hello" },
    [ZHBK_LABEL_PLOTNOST_SLOY_3]         = { "Plotnost_sloy_3",         "hello" },
    [ZHBK_LABEL_PLOTNOST_SLOY_4]         = { "Plotnost_sloy_4",         "hello" },
    [ZHBK_LABEL_KLASS_BETONA]            = { "Klass_betona",            "hello" },

    // output variables
    [ZHBK_LABEL_MAIN_BEAM_LENGTH]        = { "main_beam_length",        "hello" },
    [ZHBK_LABEL_MAIN_BEAM_HEIGHT]        = { "main_beam_height",        "hello" },
    [ZHBK_LABEL_MAIN_BEAM_WIDTH]         = { "main_beam_width",         "hello" },
    [ZHBK_LABEL_SECOND_BEAM_LENGTH]      = { "second_beam_length",      "hello" },
    [ZHBK_LABEL_SECOND_BEAM_HEIGHT]      = { "second_beam_height",      "hello" },
    [ZHBK_LABEL_SECOND_BEAM_WIDTH]       = { "second_beam_width",       "hello" },
    [ZHBK_LABEL_PLATE_THICKNESS]         = { "plate_thickness",         "hello" },
    [ZHBK_LABEL_PLATE_WIDTH]             = { "plate_width",             "hello" },
    [ZHBK_LABEL_PLATE_EFFECTIVE_WIDTH]   = { "plate_effective_width",   "hello" },
    [ZHBK_LABEL_TEMP_ESTIMATED_LOAD]     = { "temp_estimated_load",     "hello" },
    [ZHBK_LABEL_CONST_ESTIMATED_LOAD]    = { "const_estimated_load",    "hello" },
    [ZHBK_LABEL_SUM_ESTIMATED_LOAD]      = { "sum_estimated_load",      "hello" },
    [ZHBK_LABEL_BEND_MOMENT_1]           = { "bend_moment1",            "hello" },
    [ZHBK_LABEL_BEND_MOMENT_2]           = { "bend_moment2",            "hello" },
    [ZHBK_LABEL_COEF_KD_1]               = { "coef_kd1",                "hello" },
    [ZHBK_LABEL_COEF_KD_2]               = { "coef_kd2",                "hello" },
    [ZHBK_LABEL_COEF_KS_1]               = { "coef_ks1",                "hello" },
    [ZHBK_LABEL_COEF_KS_2]               = { "coef_ks2",                "hello" },
    [ZHBK_LABEL_COEF_AS_1]               = { "coef_as1",                "hello" },
    [ZHBK_LABEL_COEF_AS_2]               = { "coef_as2",                "hello" },
    [ZHBK_LABEL_COEF_AS_1_FACT]          = { "coef_as1_fact",           "hello" },
    [ZHBK_LABEL_COEF_AS_2_FACT]          = { "coef_as2_fact",           "hello" },
    [ZHBK_LABEL_ARMATURA_STEP1_90]       = { "armatura_step1_90",       "hello" },
    [ZHBK_LABEL_ARMATURA_STEP2_90]       = { "armatura_step2_90",       "hello" },
    [ZHBK_LABEL_ARMATURA_STEP1_180]      = { "armatura_step1_180",      "hello" },
    [ZHBK_LABEL_ARMATURA_STEP2_180]      = { "armatura_step2_180",      "hello" },
    [ZHBK_LABEL_ARMATURA_AS1_D] = { "as1_d_armatura",          "hello" },
    [ZHBK_LABEL_ARMATURA_AS1_N] = { "as1_n_armatura",          "hello" },
    [ZHBK_LABEL_ARMATURA_AS2_D] = { "as2_d_armatura",          "hello" },
    [ZHBK_LABEL_ARMATURA_AS2_N] = { "as2_n_armatura",          "hello" },

    // measure units
    [ZHBK_LABEL_METERS]                  = { "метров",                  "hello" },
    [ZHBK_LABEL_KNM2]                    = { "КН/м^2",                  "hello" },
    [ZHBK_LABEL_KGM3]                    = { "КГ/м^3",                  "hello" },
    [ZHBK_LABEL_COD_BETONA]              = { "код бетона",              "hello" },
};

#endif // ZHBK_LANGUAGE_H