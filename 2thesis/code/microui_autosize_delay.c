static void autosize_delay_showcase(mu_Context* ctx)
{
    static bool show_c_and_d = false;
    static int frame_n = 0;
    static char char_arr[128];

    if (mu_begin_window_ex(ctx, "Autosize win", mu_rect(35, 35, 0, 0), (MU_OPT_AUTOSIZE | MU_OPT_NOCLOSE))) {

        if (!show_c_and_d) 
            mu_text(ctx, "AAAAAAAAAA\nBBBBBBBBBB");
        else 
            mu_text(ctx, "AAAAAAAAAA\nBBBBBBBBBB\nCCCCCCCCCC\nDDDDDDDDD");

        mu_end_window(ctx);
    }

    if (mu_begin_window_ex(ctx, "Show Cs & Ds", mu_rect(35, 180, 120, 80), (MU_OPT_NOCLOSE))) {

        if (mu_button(ctx, "On/Off")) 
            show_c_and_d = !show_c_and_d;

        mu_layout_row(ctx, 1, (int[]) { -1 }, 0);
        sprintf(char_arr, "Frame no.: %d", frame_n++);
        mu_label(ctx, char_arr);

        mu_end_window(ctx);
    }
}