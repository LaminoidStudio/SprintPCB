//
// Created by Benedikt on 26.04.2022.
// Copyright 2022, Laminoid.com (Muessig & Muessig GbR).
// Licensed under the terms and conditions of the GPLv3.
//

#include <stdio.h>

#include "libsprintpcb/list.h"
#include "libsprintpcb/primitives.h"
#include "libsprintpcb/elements.h"
#include "libsprintpcb/stringbuilder.h"

int gui_main(void);

int main() {
    sprint_element circle = sprint_circle_create(
            SPRINT_LAYER_MECHANICAL,
            10,
            sprint_tuple_of(sprint_dist_um(1), sprint_dist_um(20)),
            10);

    sprint_prim_format format_dist = SPRINT_PRIM_FORMAT_DIST_UM;
    sprint_prim_format format_angle = format_dist == SPRINT_PRIM_FORMAT_RAW ? format_dist : SPRINT_PRIM_FORMAT_COOKED;
    sprint_prim_format format_layer = format_angle;


    sprint_stringbuilder* builder = sprint_stringbuilder_of("Circle and builder test:\n");
    sprint_stringbuilder_put_str(builder, "layer: ");
    sprint_layer_string(circle.circle.layer, builder, format_layer);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "width: ");
    sprint_dist_string(circle.circle.width, builder, format_dist);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "center: ");
    sprint_tuple_string(&circle.circle.center, builder, format_dist);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "radius: ");
    sprint_dist_string(circle.circle.radius, builder, format_dist);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "clear: ");
    sprint_dist_string(circle.circle.clear, builder, format_dist);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(cutout): ");
    sprint_bool_string(circle.circle.cutout, builder);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(soldermask): ");
    sprint_bool_string(circle.circle.soldermask, builder);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(start): ");
    sprint_angle_string(circle.circle.start, builder, format_angle);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(stop): ");
    sprint_angle_string(circle.circle.stop, builder, format_angle);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(fill): ");
    sprint_bool_string(circle.circle.fill, builder);
    sprint_stringbuilder_put_chr(builder, '\n');
    sprint_element_destroy(&circle);

    sprint_stringbuilder_put_str(builder, "String test: ");
    sprint_str_string("my string raw", builder, SPRINT_PRIM_FORMAT_RAW);
    sprint_stringbuilder_put_chr(builder, ' ');
    sprint_str_string("my string cooked", builder, SPRINT_PRIM_FORMAT_COOKED);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_flush(builder, stdout);

    sprint_tuple tuple1 = sprint_tuple_of(1, 2), tuple2 = sprint_tuple_of(3, 4);

    printf("track %d\n", (int) sizeof(sprint_track));
    printf("pad_tht %d\n", (int) sizeof(sprint_pad_tht));
    printf("pad_smt %d\n", (int) sizeof(sprint_pad_smt));
    printf("zone %d\n", (int) sizeof(sprint_zone));
    printf("text %d\n", (int) sizeof(sprint_text));
    printf("circle %d\n", (int) sizeof(sprint_circle));
    printf("component %d\n", (int) sizeof(sprint_component));
    printf("group %d\n\n", (int) sizeof(sprint_group));
    printf("element %d\n", (int) sizeof(sprint_element));

    sprint_list* list = sprint_list_create(sizeof(sprint_tuple), 0);
    sprint_list_add(list, &tuple1);
    sprint_list_add(list, &tuple2);
    sprint_list_add(list, &tuple2);

    for (int i = 0; i < list->count; i++) {
        sprint_tuple* tuple = (sprint_tuple*)sprint_list_get(list, i);
        sprint_tuple_print(tuple, stdout, SPRINT_PRIM_FORMAT_COOKED);
        putchar('\n');
    }

    sprint_list_destroy(list);

    return gui_main();
}


#ifdef WIN32

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 320

#include "nuklear.h"
#include "nuklear_gdi.h"

static LRESULT CALLBACK
WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    if (nk_gdi_handle_event(wnd, msg, wparam, lparam))
        return 0;

    return DefWindowProcW(wnd, msg, wparam, lparam);
}

char buf[256] = {0};
nk_size mprog = 60;
int mslider = 10;
int mcheck = nk_true;

/*
void element_test(sprint_element* element)
{
    sprint_prim_format format;
    sprint_stringbuilder* builder = sprint_stringbuilder_create(16);
    sprint_layer_string(element->circle.layer, builder, format_layer);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "width: ");
    sprint_dist_string(circle.circle.width, builder, format_dist);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "center: ");
    sprint_tuple_string(&circle.circle.center, builder, format_dist);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "radius: ");
    sprint_dist_string(circle.circle.radius, builder, format_dist);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "clear: ");
    sprint_dist_string(circle.circle.clear, builder, format_dist);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(cutout): ");
    sprint_bool_string(circle.circle.cutout, builder);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(soldermask): ");
    sprint_bool_string(circle.circle.soldermask, builder);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(start): ");
    sprint_angle_string(circle.circle.start, builder, format_angle);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(stop): ");
    sprint_angle_string(circle.circle.stop, builder, format_angle);
    sprint_stringbuilder_put_chr(builder, '\n');

    sprint_stringbuilder_put_str(builder, "(fill): ");
    sprint_bool_string(circle.circle.fill, builder);
    sprint_stringbuilder_put_chr(builder, '\n');
    sprint_element_destroy(&circle);

    sprint_stringbuilder_put_str(builder, "String test: ");
    sprint_str_string("my string raw", builder, SPRINT_PRIM_FORMAT_RAW);
    sprint_stringbuilder_put_chr(builder, ' ');
    sprint_str_string("my string cooked", builder, SPRINT_PRIM_FORMAT_COOKED);
    sprint_stringbuilder_put_chr(builder, '\n');
}*/

int gui_main(void)
{
    GdiFont* font;
    struct nk_context *ctx;

    WNDCLASSW wc;
    ATOM atom;
    RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    DWORD style = WS_SYSMENU | WS_BORDER | WS_CAPTION;//WS_OVERLAPPEDWINDOW;
    DWORD exstyle = WS_EX_APPWINDOW;
    HWND wnd;
    HDC dc;
    int running = 1;
    int needs_refresh = 1;

    /* Win32 */
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandleW(0);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"NuklearWindowClass";
    atom = RegisterClassW(&wc);

    AdjustWindowRectEx(&rect, style, FALSE, exstyle);
    wnd = CreateWindowExW(exstyle, wc.lpszClassName, L"Nuklear Demo",
                          style | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
                          rect.right - rect.left, rect.bottom - rect.top,
                          NULL, NULL, wc.hInstance, NULL);
    dc = GetDC(wnd);

    /* GUI */
    font = nk_gdifont_create("Segoe UI", 14);
    ctx = nk_gdi_init(font, dc, WINDOW_WIDTH, WINDOW_HEIGHT);

    struct nk_color table[NK_COLOR_COUNT];
    table[NK_COLOR_TEXT]                    = nk_rgb(0x00, 0x00, 0x00);
    table[NK_COLOR_WINDOW]                  = nk_rgb(0xF2, 0xF2, 0xF2);
    table[NK_COLOR_HEADER]                  = nk_rgb(0xCF, 0xD3, 0xD7);
    table[NK_COLOR_BORDER]                  = nk_rgb(0xC4, 0xC4, 0xC4);
    table[NK_COLOR_BUTTON]                  = nk_rgb(0xFF, 0xFF, 0xFF);
    table[NK_COLOR_BUTTON_HOVER]            = nk_rgb(0xF2, 0xF2, 0xF2);
    table[NK_COLOR_BUTTON_ACTIVE]           = nk_rgb(0xE5, 0xE5, 0xE5);
    table[NK_COLOR_TOGGLE]                  = nk_rgb(0xFF, 0xFF, 0xFF);
    table[NK_COLOR_TOGGLE_HOVER]            = nk_rgb(0xC4, 0xC4, 0xC4);
    table[NK_COLOR_TOGGLE_CURSOR]           = nk_rgb(0x52, 0x52, 0x52);
    table[NK_COLOR_SELECT]                  = nk_rgb(0x4F, 0x9E, 0xE3);
    table[NK_COLOR_SELECT_ACTIVE]           = nk_rgb(0x35, 0x75, 0xB0);
    table[NK_COLOR_SLIDER]                  = nk_rgb(0xFF, 0xFF, 0xFF);
    table[NK_COLOR_SLIDER_CURSOR]           = nk_rgb(0x4D, 0x4D, 0x4D);
    table[NK_COLOR_SLIDER_CURSOR_HOVER]     = nk_rgb(0x40, 0x40, 0x40);
    table[NK_COLOR_SLIDER_CURSOR_ACTIVE]    = nk_rgb(0x33, 0x33, 0x33);
    table[NK_COLOR_PROPERTY]                = nk_rgb(0xFF, 0xFF, 0xFF);
    table[NK_COLOR_EDIT]                    = nk_rgb(0xFF, 0xFF, 0xFF);
    table[NK_COLOR_EDIT_CURSOR]             = nk_rgb(0x4D, 0x4D, 0x4D);
    table[NK_COLOR_COMBO]                   = nk_rgb(0xFF, 0xFF, 0xFF);
    table[NK_COLOR_CHART]                   = nk_rgb(0xFF, 0xFF, 0xFF);
    table[NK_COLOR_CHART_COLOR]             = nk_rgb(0x4D, 0x4D, 0x4D);
    table[NK_COLOR_CHART_COLOR_HIGHLIGHT]   = nk_rgb(0x40, 0x40, 0x40);
    table[NK_COLOR_SCROLLBAR]               = nk_rgb(0xF2, 0xF2, 0xF2);
    table[NK_COLOR_SCROLLBAR_CURSOR]        = nk_rgb(0xC4, 0xC4, 0xC4);
    table[NK_COLOR_SCROLLBAR_CURSOR_HOVER]  = nk_rgb(0xB8, 0xB8, 0xB8);
    table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgb(0xAB, 0xAB, 0xAB);
    table[NK_COLOR_TAB_HEADER]              = nk_rgb(0xCF, 0xD3, 0xD7);
    nk_style_from_table(ctx, table);

    while (running)
    {
        /* Input */
        MSG msg;
        nk_input_begin(ctx);
        if (needs_refresh == 0) {
            if (GetMessageW(&msg, NULL, 0, 0) <= 0)
                running = 0;
            else {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
            needs_refresh = 1;
        } else needs_refresh = 0;

        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                running = 0;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
            needs_refresh = 1;
        }
        nk_input_end(ctx);

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
                     //0))
                     //NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                     NK_WINDOW_TITLE))
                     //NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property1 = 20;
            static int property2 = 20;

            nk_layout_row_static(ctx, 30, 80, 2);
            if (nk_button_label(ctx, "button1"))
                fprintf(stdout, "button1 pressed\n");
            if (nk_button_label(ctx, "button2"))
                fprintf(stdout, "button2 pressed\n");
            nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(ctx, 22, 2);
            nk_property_int(ctx, "Compression:", 0, &property1, 100, 10, 1);
            nk_property_int(ctx, "Other:", 0, &property2, 100, 10, 1);
            nk_layout_row_dynamic(ctx, 22, 2);
            nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, buf, sizeof(buf) - 1, nk_filter_default);
            if (nk_button_label(ctx, "Done"))
                printf("%s\n", buf);

            nk_layout_row_dynamic(ctx, 22, 3);
            nk_progress(ctx, &mprog, 100, NK_MODIFIABLE);
            nk_slider_int(ctx, 0, &mslider, 16, 1);
            nk_checkbox_label(ctx, "check", &mcheck);

            const float values[]={26.0f,13.0f,30.0f,15.0f,25.0f,10.0f,20.0f,40.0f,12.0f,8.0f,22.0f,28.0f};
            nk_layout_row_dynamic(ctx, 150, 1);
            nk_chart_begin(ctx, NK_CHART_COLUMN, NK_LEN(values), 0, 50);
            for (size_t i = 0; i < NK_LEN(values); ++i)
                nk_chart_push(ctx, values[i]);
            nk_chart_end(ctx);
        }
        nk_end(ctx);

        /* Draw */
        nk_gdi_render(nk_rgb(240,240,240));
    }

    nk_gdifont_del(font);
    ReleaseDC(wnd, dc);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}

#else

#include "nuklear.h"
#include "nuklear_sdl.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

int gui_main(void)
{
    /* Platform */
    SDL_Window *win;
    SDL_Renderer *renderer;
    int running = 1;
    int flags = 0;
    float font_scale = 1;

    /* GUI */
    struct nk_context *ctx;
    struct nk_colorf bg;

    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Demo",
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);

    if (win == NULL) {
        SDL_Log("Error SDL_CreateWindow %s", SDL_GetError());
        exit(-1);
    }

    flags |= SDL_RENDERER_ACCELERATED;
    flags |= SDL_RENDERER_PRESENTVSYNC;

#if 0
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");
#endif

    renderer = SDL_CreateRenderer(win, -1, flags);

    if (renderer == NULL) {
        SDL_Log("Error SDL_CreateRenderer %s", SDL_GetError());
        exit(-1);
    }

    /* scale the renderer output for High-DPI displays */
    {
        int render_w, render_h;
        int window_w, window_h;
        float scale_x, scale_y;
        SDL_GetRendererOutputSize(renderer, &render_w, &render_h);
        SDL_GetWindowSize(win, &window_w, &window_h);
        scale_x = (float)(render_w) / (float)(window_w);
        scale_y = (float)(render_h) / (float)(window_h);
        SDL_RenderSetScale(renderer, scale_x, scale_y);
        font_scale = scale_y;
    }

    /* GUI */
    ctx = nk_sdl_init(win, renderer);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {
        struct nk_font_atlas *atlas;
        struct nk_font_config config = nk_font_config(0);
        struct nk_font *font;

        /* set up the font atlas and add desired font; note that font sizes are
         * multiplied by font_scale to produce better results at higher DPIs */
        nk_sdl_font_stash_begin(&atlas);
        font = nk_font_atlas_add_default(atlas, 13 * font_scale, &config);
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13 * font_scale, &config);*/
        nk_sdl_font_stash_end();

        /* this hack makes the font appear to be scaled down to the desired
         * size and is only necessary when font_scale > 1 */
        font->handle.height /= font_scale;
        /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
        nk_style_set_font(ctx, &font->handle);
    }

#ifdef INCLUDE_STYLE
    /*set_style(ctx, THEME_WHITE);*/
    /*set_style(ctx, THEME_RED);*/
    /*set_style(ctx, THEME_BLUE);*/
    /*set_style(ctx, THEME_DARK);*/
#endif

    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    while (running)
    {
        /* Input */
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) goto cleanup;
            nk_sdl_handle_event(&evt);
        }
        nk_input_end(ctx);

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                     NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                     NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "button"))
                fprintf(stdout, "button pressed\n");
            nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
                nk_layout_row_dynamic(ctx, 120, 1);
                bg = nk_color_picker(ctx, bg, NK_RGBA);
                nk_layout_row_dynamic(ctx, 25, 1);
                bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
                bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
                bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
                bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
                nk_combo_end(ctx);
            }
        }
        nk_end(ctx);

        /* -------------- EXAMPLES ---------------- */
#ifdef INCLUDE_CALCULATOR
        calculator(ctx);
#endif
#ifdef INCLUDE_CANVAS
        canvas(ctx);
#endif
#ifdef INCLUDE_OVERVIEW
        overview(ctx);
#endif
#ifdef INCLUDE_NODE_EDITOR
        node_editor(ctx);
#endif
        /* ----------------------------------------- */

        SDL_SetRenderDrawColor(renderer, bg.r * 255, bg.g * 255, bg.b * 255, bg.a * 255);
        SDL_RenderClear(renderer);

        nk_sdl_render(NK_ANTI_ALIASING_ON);

        SDL_RenderPresent(renderer);
    }

    cleanup:
    nk_sdl_shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

#endif