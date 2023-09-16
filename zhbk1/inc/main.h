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

// window data
#define WINDOW_TITLE "ZHBK CALC"
#define WINDOW_WIDTH 1080
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

// input
static char zhbk_input_text[ZHBK_LABEL_COUNT][ZHBK_INPUT_LABEL_LENGTH] = {
    [ZHBK_LABEL_ZDANIE_L]        = "22.8", 
    [ZHBK_LABEL_ZDANIE_B]        = "60", 
    [ZHBK_LABEL_SETKA_L]         = "5.7", 
    [ZHBK_LABEL_SETKA_B]         = "6", 
    [ZHBK_LABEL_VREM_NAGRUZKA]   = "4",
    [ZHBK_LABEL_TOLSINA_SLOY_1]  = "0.01",
    [ZHBK_LABEL_TOLSINA_SLOY_2]  = "0.03",
    [ZHBK_LABEL_TOLSINA_SLOY_3]  = "0.025",
    [ZHBK_LABEL_TOLSINA_SLOY_4]  = "0.1",
    [ZHBK_LABEL_PLOTNOST_SLOY_1] = "1800",
    [ZHBK_LABEL_PLOTNOST_SLOY_2] = "1600",
    [ZHBK_LABEL_PLOTNOST_SLOY_3] = "150",
    [ZHBK_LABEL_PLOTNOST_SLOY_4] = "2500",
    [ZHBK_LABEL_KLASS_BETONA]    = "C12/15",
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

// allocator
static vt_mallocator_t *alloctr = NULL;

// setup
extern void zhbk_app_run(void);
extern void zhbk_app_set_gui_style(struct nk_context *ctx, enum ZHBKTheme ZHBKTheme);

// calculations
extern struct ZHBKInputParams zhbk_parse_params(const char zhbk_input_text[ZHBK_LABEL_COUNT][ZHBK_INPUT_LABEL_LENGTH]);
extern struct ZHBKCalcParams zhbk_calc_params(const struct ZHBKInputParams params);

// auxiliary
extern float zhbk_calc_wall_thickness_from_load(const float thickness);
extern float zhbk_round_50(const float value);
extern float zhbk_get_kd_class_value(const enum ZHBKKdClassHardness kd_class, const float coef_kd);
extern float zhbk_get_asx_fact_value(const float coef_as, int32_t *d_armatura, int32_t *n_armatura);

#endif // ZHBK_MAIN_H