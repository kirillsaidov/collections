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
    ZHBK_LABEL_LANGUAGE,
    ZHBK_LABEL_LANGUAGE_RU,
    ZHBK_LABEL_LANGUAGE_KZ,
    ZHBK_LABEL_CALCULATE,

    // variables
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

    // measure units
    ZHBK_LABEL_METERS,
    ZHBK_LABEL_KNM2,
    ZHBK_LABEL_KGM3,
    ZHBK_LABEL_COD_BETONA,

    ZHBK_LABEL_COUNT
};

static const char zhbk_label[ZHBK_LABEL_COUNT][ZHBK_LANGAUGE_COUNT][512] = {
    // label
    [ZHBK_LABEL_INPUT]            = { "Введите данные",   "hello" }, 
    [ZHBK_LABEL_LANGUAGE]         = { "Язык",             "hello" }, 
    [ZHBK_LABEL_LANGUAGE_RU]      = { "Русский",          "hello" }, 
    [ZHBK_LABEL_LANGUAGE_KZ]      = { "Казахский",        "hello" }, 
    [ZHBK_LABEL_CALCULATE]        = { "Рассчитать",       "hello" }, 

    // variables
    [ZHBK_LABEL_ZDANIE_L]         = { "Zdanie_L",         "hello" }, 
    [ZHBK_LABEL_ZDANIE_B]         = { "Zdanie_B",         "hello" }, 
    [ZHBK_LABEL_SETKA_L]          = { "Setka_L",          "hello" }, 
    [ZHBK_LABEL_SETKA_B]          = { "Setka_B",          "hello" }, 
    [ZHBK_LABEL_VREM_NAGRUZKA]    = { "Vrem_nagruzka",    "hello" },
    [ZHBK_LABEL_TOLSINA_SLOY_1]   = { "Tolsina_sloy_1",   "hello" },
    [ZHBK_LABEL_TOLSINA_SLOY_2]   = { "Tolsina_sloy_2",   "hello" },
    [ZHBK_LABEL_TOLSINA_SLOY_3]   = { "Tolsina_sloy_3",   "hello" },
    [ZHBK_LABEL_TOLSINA_SLOY_4]   = { "Tolsina_sloy_4",   "hello" },
    [ZHBK_LABEL_PLOTNOST_SLOY_1]  = { "Plotnost_sloy_1",  "hello" },
    [ZHBK_LABEL_PLOTNOST_SLOY_2]  = { "Plotnost_sloy_2",  "hello" },
    [ZHBK_LABEL_PLOTNOST_SLOY_3]  = { "Plotnost_sloy_3",  "hello" },
    [ZHBK_LABEL_PLOTNOST_SLOY_4]  = { "Plotnost_sloy_4",  "hello" },
    [ZHBK_LABEL_KLASS_BETONA]     = { "Klass_betona",     "hello" },

    // measure units
    [ZHBK_LABEL_METERS]           = { "метров",           "hello" },
    [ZHBK_LABEL_KNM2]             = { "КН/м^2",           "hello" },
    [ZHBK_LABEL_KGM3]             = { "КГ/м^3",           "hello" },
    [ZHBK_LABEL_COD_BETONA]       = { "код бетона",       "hello" },
};

#endif // ZHBK_LANGUAGE_H