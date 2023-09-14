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
    printf("%34s: %d\n\n", VT_STRING_OF(params.kd_class), params.kd_class);

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
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.plate_effective_width), calc_params.plate_effective_width);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.temp_estimated_load), calc_params.temp_estimated_load);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.const_estimated_load), calc_params.const_estimated_load);
    printf("%34s\n", "--- R3 ---");
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.sum_estimated_load), calc_params.sum_estimated_load);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.bend_moment1), calc_params.bend_moment1);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.bend_moment2), calc_params.bend_moment2);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.coef_kd1), calc_params.coef_kd1);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.coef_kd2), calc_params.coef_kd2);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.coef_ks1), calc_params.coef_ks1);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.coef_ks2), calc_params.coef_ks2);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.coef_as1), calc_params.coef_as1);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.coef_as2), calc_params.coef_as2);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.coef_as1_fact), calc_params.coef_as1_fact);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.coef_as2_fact), calc_params.coef_as2_fact);
    printf("%34s: %d\n", VT_STRING_OF(calc_params.as1_d_armatura), calc_params.as1_d_armatura);
    printf("%34s: %d\n", VT_STRING_OF(calc_params.as1_n_armatura), calc_params.as1_n_armatura);
    printf("%34s: %d\n", VT_STRING_OF(calc_params.as2_d_armatura), calc_params.as2_d_armatura);
    printf("%34s: %d\n", VT_STRING_OF(calc_params.as2_n_armatura), calc_params.as2_n_armatura);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.armatura_step1_90), calc_params.armatura_step1_90);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.armatura_step2_90), calc_params.armatura_step2_90);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.armatura_step1_180), calc_params.armatura_step1_180);
    printf("%34s: %.2f\n", VT_STRING_OF(calc_params.armatura_step2_180), calc_params.armatura_step2_180);

    zhbk_gui_run();

    return 0;
}

void zhbk_gui_run(void) {
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
    window_handle = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ZHBK CALC", NULL, NULL);
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
        nk_glfw3_font_stash_begin(&glfw_ctx, &atlas);
        // struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);
        nk_glfw3_font_stash_end(&glfw_ctx);
    }

    // set style
    set_style(nk_ctx, THEME_RED);
    // set_style(nk_ctx, THEME_DARK);

    // loop
    char text_buffer[1024] = "hello, world!";
    while(!glfwWindowShouldClose(window_handle)) {
        // process events
        glfwPollEvents();
        nk_glfw3_new_frame(&glfw_ctx);

        // describe GUI
        if (nk_begin(nk_ctx, "INPUT", nk_rect(5, 5, WINDOW_WIDTH/2, WINDOW_HEIGHT/2), WINDOW_FLAGS)) {
            // text: variable | input | text: measure unit
            nk_layout_row_static(nk_ctx, 25, 120, 3);
            {
                // R1: row 1
                nk_label(nk_ctx, "Zdanie_B", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_BOX, text_buffer, sizeof(text_buffer), nk_filter_default);
                nk_label(nk_ctx, "meters", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);

                // R1: row 2
                nk_label(nk_ctx, "Zdanie_L", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_BOX, text_buffer, sizeof(text_buffer), nk_filter_default);
                nk_label(nk_ctx, "meters", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);

                // R1: row 3
                nk_label(nk_ctx, "Setka_B", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_BOX, text_buffer, sizeof(text_buffer), nk_filter_default);
                nk_label(nk_ctx, "meters", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                
                // R1: row 4
                nk_label(nk_ctx, "Setka_L", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_BOX, text_buffer, sizeof(text_buffer), nk_filter_default);
                nk_label(nk_ctx, "meters", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);

                // R1: row 4
                nk_label(nk_ctx, "Vrem_nagruzka", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
                nk_edit_string_zero_terminated(nk_ctx, NK_EDIT_BOX, text_buffer, sizeof(text_buffer), nk_filter_default);
                nk_label(nk_ctx, "KN/m^2", NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_MIDDLE);
            }
        }
        nk_end(nk_ctx);

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

