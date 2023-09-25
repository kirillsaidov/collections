#ifndef ZHBK_MAIN_H
#define ZHBK_MAIN_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear/nuklear.h"
#include "nuklear/nuklear_glfw_gl3.h"

#include <math.h>
#include "vita/vita.h"
#include "tabledata.h"
#include "language.h"

// #if defined(_WIN32)
    #include "mysql/mysql.h"
// #else
//     #include <mysql/mysql.h>
// #endif

// window data
#define WINDOW_TITLE "ZHBK CALC"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_FLAGS (NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)

// render data
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

// meters to millimeters
#define M2MM(m) (m * 1000)

// millimeters to meters
#define MM2M(m) (m / 1000)

// millimeters to centimeters
#define MM2CM(m) (m / 10)

// ditto
#define ZHBK_TMP_BUFLEN 512
#define ZHBK_INPUT_LABEL_LENGTH 32

// theme style
enum ZHBKTheme {
    ZHBK_THEME_BLACK, 
    ZHBK_THEME_WHITE, 
    ZHBK_THEME_RED, 
    ZHBK_THEME_BLUE, 
    ZHBK_THEME_DARK,
    ZHBK_THEME_COUNT
};

// zhbk data
static char zhbk_data_text[ZHBK_LABEL_COUNT][ZHBK_INPUT_LABEL_LENGTH] = {
    // input variables
    [ZHBK_LABEL_ZDANIE_L]               = "22.8", 
    [ZHBK_LABEL_ZDANIE_B]               = "60", 
    [ZHBK_LABEL_SETKA_L]                = "5.7", 
    [ZHBK_LABEL_SETKA_B]                = "6", 
    [ZHBK_LABEL_VREM_NAGRUZKA]          = "4",
    [ZHBK_LABEL_TOLSINA_SLOY_1]         = "0.01",
    [ZHBK_LABEL_TOLSINA_SLOY_2]         = "0.03",
    [ZHBK_LABEL_TOLSINA_SLOY_3]         = "0.025",
    [ZHBK_LABEL_TOLSINA_SLOY_4]         = "0.1",
    [ZHBK_LABEL_PLOTNOST_SLOY_1]        = "1800",
    [ZHBK_LABEL_PLOTNOST_SLOY_2]        = "1600",
    [ZHBK_LABEL_PLOTNOST_SLOY_3]        = "150",
    [ZHBK_LABEL_PLOTNOST_SLOY_4]        = "2500",
    [ZHBK_LABEL_KLASS_BETONA]           = "C12/15",

    // output variables
    [ZHBK_LABEL_MAIN_BEAM_LENGTH]        = "",
    [ZHBK_LABEL_MAIN_BEAM_HEIGHT]        = "",
    [ZHBK_LABEL_MAIN_BEAM_WIDTH]         = "",
    [ZHBK_LABEL_SECOND_BEAM_LENGTH]      = "",
    [ZHBK_LABEL_SECOND_BEAM_HEIGHT]      = "",
    [ZHBK_LABEL_SECOND_BEAM_WIDTH]       = "",
    [ZHBK_LABEL_PLATE_THICKNESS]         = "",
    [ZHBK_LABEL_PLATE_WIDTH]             = "",
    [ZHBK_LABEL_PLATE_EFFECTIVE_WIDTH]   = "",
    [ZHBK_LABEL_TEMP_ESTIMATED_LOAD]     = "",
    [ZHBK_LABEL_CONST_ESTIMATED_LOAD]    = "",
    [ZHBK_LABEL_SUM_ESTIMATED_LOAD]      = "",
    [ZHBK_LABEL_BEND_MOMENT_1]           = "",
    [ZHBK_LABEL_BEND_MOMENT_2]           = "",
    [ZHBK_LABEL_COEF_KD_1]               = "",
    [ZHBK_LABEL_COEF_KD_2]               = "",
    [ZHBK_LABEL_COEF_KS_1]               = "",
    [ZHBK_LABEL_COEF_KS_2]               = "",
    [ZHBK_LABEL_COEF_AS_1]               = "",
    [ZHBK_LABEL_COEF_AS_2]               = "",
    [ZHBK_LABEL_COEF_AS_1_FACT]          = "",
    [ZHBK_LABEL_COEF_AS_2_FACT]          = "",
    [ZHBK_LABEL_ARMATURA_STEP1_90]       = "",
    [ZHBK_LABEL_ARMATURA_STEP2_90]       = "",
    [ZHBK_LABEL_ARMATURA_STEP1_180]      = "",
    [ZHBK_LABEL_ARMATURA_STEP2_180]      = "",
    [ZHBK_LABEL_ARMATURA_AS1_D] = "",
    [ZHBK_LABEL_ARMATURA_AS1_N] = "",
    [ZHBK_LABEL_ARMATURA_AS2_D] = "",
    [ZHBK_LABEL_ARMATURA_AS2_N] = "",
};

// Input parameters
struct ZHBKInputParams {
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

// Calculated parameters
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

// setup
extern void zhbk_app_run(void);
extern void zhbk_app_set_gui_style(struct nk_context *ctx, enum ZHBKTheme ZHBKTheme);

// calculations
extern struct ZHBKInputParams zhbk_params_parse(const char input[ZHBK_LABEL_COUNT][ZHBK_INPUT_LABEL_LENGTH]);
extern struct ZHBKCalcParams zhbk_params_calc(const struct ZHBKInputParams params);
extern void zhbk_params_output_results(const struct ZHBKCalcParams params, const char output[ZHBK_LABEL_COUNT][ZHBK_INPUT_LABEL_LENGTH]);

// auxiliary
extern float zhbk_calc_wall_thickness_from_load(const float thickness);
extern float zhbk_round_50(const float value);
extern float zhbk_get_kd_class_value(const enum ZHBKKdClassHardness kd_class, const float coef_kd);
extern float zhbk_get_asx_fact_value(const float coef_as, int32_t *d_armatura, int32_t *n_armatura);

#define ZHBK_INSTALL_FOLDER "C:\\Users\\Public\\AppData\\ZHBK"
#define ZHBK_LICENSE_FILE "C:\\Users\\Public\\AppData\\ZHBK\\zhbk.license"

enum ZHBKStatus {
    ZHBK_STATUS_ERROR_UNKNOWN,
    ZHBK_STATUS_ERROR_NETWORK,
    ZHBK_STATUS_ERROR_NOT_INSTALLED,
    ZHBK_STATUS_LICENSE_INVALID,
    ZHBK_STATUS_LICENSE_NOT_FOUND,
    ZHBK_STATUS_SUCCESS,
    ZHBK_STATUS_COUNT
};

// mysql
extern enum ZHBKStatus zhbk_license_check(const char *const key);
extern enum ZHBKStatus zhbk_license_check_key(MYSQL* mysql, const char *const key);
extern enum ZHBKStatus zhbk_license_update_key(MYSQL* mysql, const char *const key);

#endif // ZHBK_MAIN_H

