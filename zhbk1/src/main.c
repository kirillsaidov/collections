#include "main.h"

int32_t main(void) {    
    // run app
    zhbk_app_run();
    
    return 0;
}

void zhbk_app_run(void) {
    // platform
    static GLFWwindow *window_handle = NULL;
    int32_t window_width = 0, window_height = 0;
    struct nk_glfw glfw_ctx = {0};
    struct nk_context *nk_ctx = NULL;
    struct nk_colorf window_bg = { 0.1f, 0.18f, 0.24f, 1.0f };

    // setup GLFW
    if (!glfwInit()) {
        VT_LOG_ERROR("[GFLW] failed to init!\n");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    window_handle = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    glfwMakeContextCurrent(window_handle);
    glfwGetWindowSize(window_handle, &window_width, &window_height);

    // setup OpenGL
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        VT_LOG_ERROR("Failed to setup GLEW\n");
    }

    // initialize Nuklear GLFW context
    nk_ctx = nk_glfw3_init(&glfw_ctx, window_handle, NK_GLFW3_INSTALL_CALLBACKS);
    {
        // initialize fonts: default font
        struct nk_font_atlas *atlas = NULL;
        struct nk_font_config font_cfg = nk_font_config(16);
        nk_glfw3_font_stash_begin(&glfw_ctx, &atlas);
        font_cfg.range = nk_font_cyrillic_glyph_ranges();
        struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "/Users/krillos/MyFiles/dev/repos/git.kirillsaidov/collections/zhbk1/assets/roboto.ttf", 16, &font_cfg);
        nk_glfw3_font_stash_end(&glfw_ctx);
        nk_style_set_font(nk_ctx, &roboto->handle);
    }

    // set style
    zhbk_app_set_gui_style(nk_ctx, ZHBK_THEME_RED);
    // zhbk_app_set_gui_style(nk_ctx, ZHBK_THEME_DARK);

    // init variables
    bool calculate_button_pressed = false;
    enum ZHBKLanguage language_id = ZHBK_LANGUAGE_RUSSIAN;
    enum ZHBKKdClassHardness kd_class = ZHBK_KD_CLASS_C1215;

    // loop
    while(!glfwWindowShouldClose(window_handle)) {
        // process events
        glfwPollEvents();
        nk_glfw3_new_frame(&glfw_ctx);

        // describe GUI: input window
        if (nk_begin_titled(nk_ctx, WINDOW_TITLE "1", zhbk_label[ZHBK_LABEL_INPUT][language_id], nk_rect(5, 5, WINDOW_WIDTH/2 - 5, WINDOW_HEIGHT*5/6), WINDOW_FLAGS)) {
            // language choice
            nk_layout_row_dynamic(nk_ctx, 25, 3);
            {   
                nk_label(nk_ctx, zhbk_label[ZHBK_LABEL_LANGUAGE][language_id], NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                if (nk_option_label(nk_ctx, zhbk_label[ZHBK_LABEL_LANGUAGE_RU][language_id], language_id == ZHBK_LANGUAGE_RUSSIAN)) language_id = ZHBK_LANGUAGE_RUSSIAN;
                if (nk_option_label(nk_ctx, zhbk_label[ZHBK_LABEL_LANGUAGE_KZ][language_id], language_id == ZHBK_LANGUAGE_KAZAKH)) language_id = ZHBK_LANGUAGE_KAZAKH;
            }
            
            // text: variable | input | text: measure unit
            nk_layout_row_static(nk_ctx, 28, 120, 3);
            {
                // generate input rows
                VT_FOREACH(i, ZHBK_LABEL_ZDANIE_L, ZHBK_LABEL_KLASS_BETONA) {
                    nk_label(nk_ctx, zhbk_label[i][language_id], NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                    nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_BOX, zhbk_data_text[i], sizeof(zhbk_data_text[i]), nk_filter_float);

                    // measure unit
                    const enum ZHBKLabel mu = (i == ZHBK_LABEL_VREM_NAGRUZKA) 
                        ? ZHBK_LABEL_KNM2 
                        : (i > ZHBK_LABEL_TOLSINA_SLOY_4 ? ZHBK_LABEL_KGM3 : ZHBK_LABEL_METERS);
                    nk_label(nk_ctx, zhbk_label[mu][language_id], NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                }

                // select item from box
                nk_label(nk_ctx, zhbk_label[ZHBK_LABEL_KLASS_BETONA][language_id], NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                kd_class = nk_combo(nk_ctx, zhbk_kd_class_name, ZHBK_KD_CLASS_COUNT, kd_class, 28, nk_vec2(120, 160));
                nk_label(nk_ctx, zhbk_label[ZHBK_LABEL_COD_BETONA][language_id], NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
            }

            // calculate
            nk_layout_row_static(nk_ctx, 30, window_width/2 - 27, 1);
            {   
                nk_label(nk_ctx, "", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                if (nk_button_label(nk_ctx, zhbk_label[ZHBK_LABEL_CALCULATE][language_id])) {                    
                    // parse input
                    struct ZHBKInputParams params = zhbk_params_parse(zhbk_data_text);
                    params.kd_class = kd_class;

                    // calculate and output results
                    struct ZHBKCalcParams calc_params = zhbk_params_calc(params);
                    zhbk_params_output_results(calc_params, zhbk_data_text);

                    // show calculate window
                    calculate_button_pressed = true;
                }
            }
        }
        nk_end(nk_ctx);

        // describe GUI: output window (calculations)
        if(calculate_button_pressed) {
            if(nk_begin_titled(nk_ctx, WINDOW_TITLE "2", zhbk_label[ZHBK_LABEL_OUTPUT][language_id], nk_rect(WINDOW_WIDTH/2 + 5, 5, WINDOW_WIDTH/2 - 10, WINDOW_HEIGHT*5/6), WINDOW_FLAGS)) {
                // text: variable | input | text: measure unit
                nk_layout_row_static(nk_ctx, 28, 120, 3);
                {
                    // generate input rows
                    VT_FOREACH(i, ZHBK_LABEL_MAIN_BEAM_LENGTH, ZHBK_LABEL_ARMATURA_AS2_N+1) {
                        nk_label(nk_ctx, zhbk_label[i][language_id], NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                        nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_READ_ONLY, zhbk_data_text[i], sizeof(zhbk_data_text[i]), nk_filter_float);

                        // measure unit
                        const enum ZHBKLabel mu = ZHBK_LABEL_METERS;
                        nk_label(nk_ctx, zhbk_label[mu][language_id], NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                    }
                }
            }
            nk_end(nk_ctx);
        }

        // render GUI
        glfwGetWindowSize(window_handle, &window_width, &window_height);
        glViewport(0, 0, window_width, window_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(window_bg.r, window_bg.g, window_bg.b, window_bg.a);
        nk_glfw3_render(&glfw_ctx, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(window_handle);
    }

    // cleanup
    nk_glfw3_shutdown(&glfw_ctx);
    glfwTerminate();
}

void zhbk_app_set_gui_style(struct nk_context *ctx, enum ZHBKTheme ZHBKTheme) {
    struct nk_color table[NK_COLOR_COUNT];
    if (ZHBKTheme == ZHBK_THEME_WHITE) {
        table[NK_COLOR_TEXT] = nk_rgba(70, 70, 70, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_HEADER] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_BORDER] = nk_rgba(0, 0, 0, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(185, 185, 185, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(170, 170, 170, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(120, 120, 120, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_SELECT] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(80, 80, 80, 255);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(70, 70, 70, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(60, 60, 60, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_EDIT] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(0, 0, 0, 255);
        table[NK_COLOR_COMBO] = nk_rgba(175, 175, 175, 255);
        table[NK_COLOR_CHART] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(45, 45, 45, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(180, 180, 180, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(140, 140, 140, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(150, 150, 150, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(160, 160, 160, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(180, 180, 180, 255);
        nk_style_from_table(ctx, table);
    } else if (ZHBKTheme == ZHBK_THEME_RED) {
        table[NK_COLOR_TEXT] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(30, 33, 40, 215);
        table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
        table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
        nk_style_from_table(ctx, table);
    } else if (ZHBKTheme == ZHBK_THEME_BLUE) {
        table[NK_COLOR_TEXT] = nk_rgba(20, 20, 20, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(202, 212, 214, 215);
        table[NK_COLOR_HEADER] = nk_rgba(137, 182, 224, 220);
        table[NK_COLOR_BORDER] = nk_rgba(140, 159, 173, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(142, 187, 229, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(147, 192, 234, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(182, 215, 215, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(177, 210, 210, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_EDIT] = nk_rgba(210, 210, 210, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
        table[NK_COLOR_COMBO] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_CHART] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(190, 200, 200, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
        nk_style_from_table(ctx, table);
    } else if (ZHBKTheme == ZHBK_THEME_DARK) {
        table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(57, 67, 71, 215);
        table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 220);
        table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(63, 98, 126, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
        table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
        nk_style_from_table(ctx, table);
    } else {
        nk_style_default(ctx);
    }
}

struct ZHBKInputParams zhbk_params_parse(const char input[ZHBK_LABEL_COUNT][ZHBK_INPUT_LABEL_LENGTH]) {
    struct ZHBKInputParams params = {
        .zdanie_L = M2MM(vt_conv_str_to_f(input[ZHBK_LABEL_ZDANIE_L])), 
        .zdanie_B = M2MM(vt_conv_str_to_f(input[ZHBK_LABEL_ZDANIE_B])), 
        .setka_L = M2MM(vt_conv_str_to_f(input[ZHBK_LABEL_SETKA_L])), 
        .setka_B = M2MM(vt_conv_str_to_f(input[ZHBK_LABEL_SETKA_B])), 
        .vrem_nagruzka = vt_conv_str_to_f(input[ZHBK_LABEL_VREM_NAGRUZKA]),
        .tolsina_sloy_1 = M2MM(vt_conv_str_to_f(input[ZHBK_LABEL_TOLSINA_SLOY_1])),
        .tolsina_sloy_2 = M2MM(vt_conv_str_to_f(input[ZHBK_LABEL_TOLSINA_SLOY_2])),
        .tolsina_sloy_3 = M2MM(vt_conv_str_to_f(input[ZHBK_LABEL_TOLSINA_SLOY_3])),
        .tolsina_sloy_4 = M2MM(vt_conv_str_to_f(input[ZHBK_LABEL_TOLSINA_SLOY_4])),
        .plotnost_sloy_1 = vt_conv_str_to_f(input[ZHBK_LABEL_PLOTNOST_SLOY_1]),
        .plotnost_sloy_2 = vt_conv_str_to_f(input[ZHBK_LABEL_PLOTNOST_SLOY_2]),
        .plotnost_sloy_3 = vt_conv_str_to_f(input[ZHBK_LABEL_PLOTNOST_SLOY_3]),
        .plotnost_sloy_4 = vt_conv_str_to_f(input[ZHBK_LABEL_PLOTNOST_SLOY_4]),
    };

    return params;
}

struct ZHBKCalcParams zhbk_params_calc(const struct ZHBKInputParams params) {
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

void zhbk_params_output_results(const struct ZHBKCalcParams params, const char output[ZHBK_LABEL_COUNT][ZHBK_INPUT_LABEL_LENGTH]) {
    snprintf((char*)output[ZHBK_LABEL_MAIN_BEAM_LENGTH], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.main_beam_length);
    snprintf((char*)output[ZHBK_LABEL_MAIN_BEAM_HEIGHT], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.main_beam_height);
    snprintf((char*)output[ZHBK_LABEL_MAIN_BEAM_WIDTH], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.main_beam_width);
    snprintf((char*)output[ZHBK_LABEL_SECOND_BEAM_LENGTH], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.second_beam_length);
    snprintf((char*)output[ZHBK_LABEL_SECOND_BEAM_HEIGHT], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.second_beam_height);
    snprintf((char*)output[ZHBK_LABEL_SECOND_BEAM_WIDTH], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.second_beam_width);
    snprintf((char*)output[ZHBK_LABEL_PLATE_THICKNESS], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.plate_thickness);
    snprintf((char*)output[ZHBK_LABEL_PLATE_WIDTH], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.plate_width);
    snprintf((char*)output[ZHBK_LABEL_PLATE_EFFECTIVE_WIDTH], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.plate_effective_width);
    snprintf((char*)output[ZHBK_LABEL_TEMP_ESTIMATED_LOAD], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.temp_estimated_load);
    snprintf((char*)output[ZHBK_LABEL_CONST_ESTIMATED_LOAD], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.const_estimated_load);
    snprintf((char*)output[ZHBK_LABEL_SUM_ESTIMATED_LOAD], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.sum_estimated_load);
    snprintf((char*)output[ZHBK_LABEL_BEND_MOMENT_1], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.bend_moment1);
    snprintf((char*)output[ZHBK_LABEL_BEND_MOMENT_2], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.bend_moment2);
    snprintf((char*)output[ZHBK_LABEL_COEF_KD_1], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.coef_kd1);
    snprintf((char*)output[ZHBK_LABEL_COEF_KD_2], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.coef_kd2);
    snprintf((char*)output[ZHBK_LABEL_COEF_KS_1], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.coef_ks1);
    snprintf((char*)output[ZHBK_LABEL_COEF_KS_2], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.coef_ks2);
    snprintf((char*)output[ZHBK_LABEL_COEF_AS_1], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.coef_as1);
    snprintf((char*)output[ZHBK_LABEL_COEF_AS_2], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.coef_as2);
    snprintf((char*)output[ZHBK_LABEL_COEF_AS_1_FACT], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.coef_as1_fact);
    snprintf((char*)output[ZHBK_LABEL_COEF_AS_2_FACT], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.coef_as2_fact);
    snprintf((char*)output[ZHBK_LABEL_ARMATURA_STEP1_90], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.armatura_step1_90);
    snprintf((char*)output[ZHBK_LABEL_ARMATURA_STEP2_90], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.armatura_step2_90);
    snprintf((char*)output[ZHBK_LABEL_ARMATURA_STEP1_180], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.armatura_step1_180);
    snprintf((char*)output[ZHBK_LABEL_ARMATURA_STEP2_180], ZHBK_INPUT_LABEL_LENGTH, "%.2f", params.armatura_step2_180);
    snprintf((char*)output[ZHBK_LABEL_ARMATURA_AS1_D], ZHBK_INPUT_LABEL_LENGTH, "%d", params.as1_d_armatura);
    snprintf((char*)output[ZHBK_LABEL_ARMATURA_AS1_N], ZHBK_INPUT_LABEL_LENGTH, "%d", params.as1_n_armatura);
    snprintf((char*)output[ZHBK_LABEL_ARMATURA_AS2_D], ZHBK_INPUT_LABEL_LENGTH, "%d", params.as2_d_armatura);
    snprintf((char*)output[ZHBK_LABEL_ARMATURA_AS2_N], ZHBK_INPUT_LABEL_LENGTH, "%d", params.as2_n_armatura);
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

