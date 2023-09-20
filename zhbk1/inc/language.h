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
    ZHBK_LABEL_MILLIMETERS,
    ZHBK_LABEL_SQUARE_SANTIMETERS,
    ZHBK_LABEL_SHTUCKA,

    ZHBK_LABEL_COUNT
};

static const char zhbk_label[ZHBK_LABEL_COUNT][ZHBK_LANGAUGE_COUNT][512] = {
    // label                                 russian             kazakh
    [ZHBK_LABEL_INPUT]                   = { "Введите данные",        "Деректерді енгізіңіз" }, 
    [ZHBK_LABEL_OUTPUT]                  = { "Результаты расчёта",    "Есептеу нәтижелері" }, 
    [ZHBK_LABEL_LANGUAGE]                = { "Язык",                  "Тіл" }, 
    [ZHBK_LABEL_LANGUAGE_RU]             = { "Русский",               "Орысша" }, 
    [ZHBK_LABEL_LANGUAGE_KZ]             = { "Казахский",             "Қазақша" }, 
    [ZHBK_LABEL_CALCULATE]               = { "Рассчитать",            "Есептеу" }, 

    // input variables
    [ZHBK_LABEL_ZDANIE_L]                = { "Размер здания - L",                                           "Ғимараттың өлшемі - L" }, 
    [ZHBK_LABEL_ZDANIE_B]                = { "Размер здания - B",                                           "Ғимараттың өлшемі - B" }, 
    [ZHBK_LABEL_SETKA_L]                 = { "Шаг колонн в направлении - L",                                "Бағандардың бағытқа қарай қадамы - L" }, 
    [ZHBK_LABEL_SETKA_B]                 = { "Шаг колонн в направлении - B",                                "Бағандардың бағытқа қарай қадамы - B" }, 
    [ZHBK_LABEL_VREM_NAGRUZKA]           = { "Характеристическая временная нагрузка",                       "Сипаттамалық уақыт жүктемесі" },
    [ZHBK_LABEL_TOLSINA_SLOY_1]          = { "Толщина первого слоя пирога пола",                            "Еден пирогының бірінші қабатының қалыңдығы" },
    [ZHBK_LABEL_TOLSINA_SLOY_2]          = { "Толщина второго слоя пирога пола",                            "Еден пирогының екiншi қабатының қалыңдығы" },
    [ZHBK_LABEL_TOLSINA_SLOY_3]          = { "Толщина третьего слоя пирога пола",                           "Еден пирогының үшінші қабатының қалыңдығы" },
    [ZHBK_LABEL_TOLSINA_SLOY_4]          = { "Толщина четвертого слоя пирога пола",                         "Еден пирогының төртінші қабатының қалыңдығы" },
    [ZHBK_LABEL_PLOTNOST_SLOY_1]         = { "Плотность первого слоя пирога пола",                          "Еден пирогының бірінші қабатының тығыздығы" },
    [ZHBK_LABEL_PLOTNOST_SLOY_2]         = { "Плотность второго слоя пирога пола",                          "Еден пирогының екінші қабатының тығыздығы" },
    [ZHBK_LABEL_PLOTNOST_SLOY_3]         = { "Плотность третьего слоя пирога пола",                         "Еден пирогының үшінші қабатының тығыздығы" },
    [ZHBK_LABEL_PLOTNOST_SLOY_4]         = { "Плотность четвертого слоя пирога пола",                       "Еден пирогының төртінші қабатының тығыздығы" },
    [ZHBK_LABEL_KLASS_BETONA]            = { "Класс бетона",                                                "Бетон класы" },

    // output variables
    [ZHBK_LABEL_MAIN_BEAM_LENGTH]        = { "Длина главной балки",                                         "Негізгі сәуленің ұзындығы" },
    [ZHBK_LABEL_MAIN_BEAM_HEIGHT]        = { "Высота главной балки",                                        "Негізгі сәуленің биіктігі" },
    [ZHBK_LABEL_MAIN_BEAM_WIDTH]         = { "Ширина главной балки",                                        "Негізгі сәуленің ені" },
    [ZHBK_LABEL_SECOND_BEAM_LENGTH]      = { "Длина второстепенной балки",                                  "Екінші сәуленің ұзындығы" },
    [ZHBK_LABEL_SECOND_BEAM_HEIGHT]      = { "Высота второстепенной балки",                                 "Екінші сәуленің биіктігі" },
    [ZHBK_LABEL_SECOND_BEAM_WIDTH]       = { "Ширина второстепенной балки",                                 "Екінші сәуленің ені" },
    [ZHBK_LABEL_PLATE_THICKNESS]         = { "Толщина плиты",                                               "Плитаның қалыңдығы" },
    [ZHBK_LABEL_PLATE_WIDTH]             = { "Пролет плиты",                                                "Плитаның ұшуы" },
    [ZHBK_LABEL_PLATE_EFFECTIVE_WIDTH]   = { "Расчетный пролет плиты",                                      "Плитаның есептік аралығы" },
    [ZHBK_LABEL_TEMP_ESTIMATED_LOAD]     = { "Временная рассчетная нагрузка",                               "Уақытша есептік жүктеме" },
    [ZHBK_LABEL_CONST_ESTIMATED_LOAD]    = { "Постоянная расчетная нагрузка",                               "Тұрақты есептік жүктеме" },
    [ZHBK_LABEL_SUM_ESTIMATED_LOAD]      = { "Суммарная рассчетная нагрузка",                               "Жиынтық есептік жүктеме" },
    [ZHBK_LABEL_BEND_MOMENT_1]           = { "Изгибающий момент первого пролета",                           "Бірінші аралықтың иілу моменті" },
    [ZHBK_LABEL_BEND_MOMENT_2]           = { "Изгибающий момент среднего пролета",                          "Екінші аралықтың иілу моменті" },
    [ZHBK_LABEL_COEF_KD_1]               = { "Коэффициент kd для первого пролета",                          "Бірінші ұшу үшін kd коэффициенті" },
    [ZHBK_LABEL_COEF_KD_2]               = { "Коэффициент kd для среднего пролета",                         "Орташа ұшу үшін kd коэффициенті" },
    [ZHBK_LABEL_COEF_KS_1]               = { "Коэффициент ks для первого пролета",                          "Бірінші ұшу үшін ks коэффициенті" },
    [ZHBK_LABEL_COEF_KS_2]               = { "Коэффициент ks для среднего пролета",                         "Орташа ұшу үшін ks коэффициенті" },
    [ZHBK_LABEL_COEF_AS_1]               = { "Требуемое сечение арматуры для первого пролета",              "Бірінші аралыққа арналған арматураның қажетті қимасы" },
    [ZHBK_LABEL_COEF_AS_2]               = { "Требуемое сечение арматуры для среднего пролета",             "Орташа аралыққа арналған арматураның қажетті қимасы" },
    [ZHBK_LABEL_COEF_AS_1_FACT]          = { "Подобранное сечение арматуры для первого пролета",            "Бірінші аралыққа арналған арматураның таңдалған қимасы" },
    [ZHBK_LABEL_COEF_AS_2_FACT]          = { "Подобранное сечение арматуры для среднего пролета",           "Орташа аралыққа арналған арматураның таңдалған қимасы" },
    [ZHBK_LABEL_ARMATURA_STEP1_90]       = { "Шаг поперечной арматуры первого пролета",                     "Бірінші аралықтағы көлденең арматураның қадамы" },
    [ZHBK_LABEL_ARMATURA_STEP2_90]       = { "Шаг поперечной арматуры среднего пролета",                    "Орташа аралықтағы көлденең арматураның қадамы" },
    [ZHBK_LABEL_ARMATURA_STEP1_180]      = { "Шаг продольной арматуры первого пролета",                     "Бірінші аралықтағы бойлық арматураның қадамы" },
    [ZHBK_LABEL_ARMATURA_STEP2_180]      = { "Шаг продольной арматуры среднего пролета",                    "Орташа аралықтағы бойлық арматураның қадамы" },
    [ZHBK_LABEL_ARMATURA_AS1_D]          = { "Диаметр арматуры для первого пролета",                        "Бірінші аралық арматураның диаметрі" },
    [ZHBK_LABEL_ARMATURA_AS1_N]          = { "Количество стержней на погонный метр для первого пролета",    "Бірінші ұшу үшін бір сызықтық метрге арналған шыбықтардың саны" },
    [ZHBK_LABEL_ARMATURA_AS2_D]          = { "Диаметр арматуры для среднего пролета",                       "Орташа аралық арматураның диаметрі" },
    [ZHBK_LABEL_ARMATURA_AS2_N]          = { "Количество стержней на погонный метр для среднего пролета",   "Екінші ұшу үшін бір сызықтық метрге арналған шыбықтардың саны" },

    // measure units
    [ZHBK_LABEL_METERS]                  = { "Метров",          "Метр" },
    [ZHBK_LABEL_KNM2]                    = { "КН/м^2",          "КН/м^2" },
    [ZHBK_LABEL_KGM3]                    = { "Кг/м^3",          "КН/м^3" },
    [ZHBK_LABEL_COD_BETONA]              = { "Класс бетона",    "Бетон класы" },
    [ZHBK_LABEL_MILLIMETERS]             = { "Миллиметров",     "Миллиметр" },
    [ZHBK_LABEL_SQUARE_SANTIMETERS]      = { "См^2",            "См^2" },
    [ZHBK_LABEL_SHTUCKA]                 = { "Шт",              "Дана" },
};

#endif // ZHBK_LANGUAGE_H

