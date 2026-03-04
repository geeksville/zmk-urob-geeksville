// Geeksville add game layer

#ifdef SCROLL
// A nop layer just so wheht SCROLL_CMD is held down we can change the touchpad to instead generate
// scroll events.
#define SCROLL_CMD &mo SCROLL
#else
#define SCROLL_CMD ___
#endif

// Game layer: Replaces left 3x6 + three thumb keys with gaming layout.
// Number keys 1-5 shift to 6-0 when shift is held.
SIMPLE_MORPH(game_1_6, SFT, &kp N1, &kp N6)
SIMPLE_MORPH(game_2_7, SFT, &kp N2, &kp N7)
SIMPLE_MORPH(game_3_8, SFT, &kp N3, &kp N8)
SIMPLE_MORPH(game_4_9, SFT, &kp N4, &kp N9)
SIMPLE_MORPH(game_5_0, SFT, &kp N5, &kp N0)
// SIMPLEx_MORPH(game_esc_tab, SFT, &kp ESC, &kp TAB)

// Morphs to mirror right half alpha to left side shifted
// geeksville turn off mirroring for now
#if 0
SIMPLE_MORPH(k_r_f, SFT, &kp R, &kp F)
SIMPLE_MORPH(k_e_g, SFT, &kp E, &kp G)
SIMPLE_MORPH(k_w_h, SFT, &kp W, &kp H)
SIMPLE_MORPH(k_q_j, SFT, &kp Q, &kp J)
SIMPLE_MORPH(k_z_k, SFT, &kp Z, &kp K)

SIMPLE_MORPH(k_c_v, SFT, &kp C, &kp V)
SIMPLE_MORPH(k_d_b, SFT, &kp D, &kp B)
SIMPLE_MORPH(k_s_n, SFT, &kp S, &kp N)
SIMPLE_MORPH(k_a_m, SFT, &kp A, &kp M)
#else
#define k_r_f kp R
#define k_e_g kp E
#define k_w_h kp W
#define k_q_j kp Q
#define k_z_k kp Z
#define k_c_v kp C
#define k_d_b kp D
#define k_s_n kp S
#define k_a_m kp A
#endif

// morph arrow keys to right hand equiv of WASD
SIMPLE_MORPH(k_up, SFT, &kp U, &kp UP)
SIMPLE_MORPH(k_down, SFT, &kp H, &kp DOWN)
SIMPLE_MORPH(k_left, SFT, &kp G, &kp LEFT)
SIMPLE_MORPH(k_right, SFT, &kp J, &kp RIGHT)
SIMPLE_MORPH(k_comma, SFT, &kp Y, &kp COMMA)
SIMPLE_MORPH(k_dot, SFT, &kp I, &kp DOT)
SIMPLE_MORPH(k_minus, SFT, &kp B, &kp MINUS)
SIMPLE_MORPH(k_equal, SFT, &kp M, &kp EQUAL)

ZMK_42_LAYER(Game,
//╭──────┬──────┬──────┬──────┬──────╮              ╭──────┬──────┬──────┬──────┬──────╮
  &game_1_6 &game_2_7 &game_3_8 &game_4_9 &game_5_0, &kp T &k_comma  &k_up &k_dot  &kp O,
//├──────┼──────┼──────┼──────┼──────┤              ├──────┼──────┼──────┼──────┼──────┤
   &k_z_k &k_q_j  &k_w_h &k_e_g &k_r_f,              &kp F &k_left &k_down &k_right &kp K,
//├──────┼──────┼──────┼──────┼──────┤              ├──────┼──────┼──────┼──────┼──────┤
    &kp X &k_a_m  &k_s_n &k_d_b &k_c_v,              &kp V &k_minus &kp N  &k_equal &kp BSPC,
//╰──────┴──────┼──────┼──────┼──────┤              ├──────┼──────┼──────┼──────┴──────╯
           &kp SPACE &kp LSHFT,                        &mkp LCLK &mkp RCLK,
//              ╰──────┴──────┴                       ╰──────┴──────┴
// Outer keys:  OLT        OLM        OLB       ORT      ORM     ORB         OLH       ORH
              &kp ESC, &kp TAB,   &kp LCTRL,   &kp P,   &kp L,  &to DEF,  &kp LALT,  SCROLL_CMD
)

#ifdef SCROLL
// A nop layer just so wheht SCROLL_CMD is held down we can change the touchpad to instead generate
// scroll events.

ZMK_42_LAYER(Scrl,
    ___ ___ ___ ___ ___,    ___    ___    ___    ___    ___,
    ___ ___ ___ ___ ___,    ___    ___    ___    ___    ___,
    ___ ___ ___ ___ ___,    ___    ___    ___    ___    ___,
           ___ ___,            ___    ___,
           ___, ___, ___, ___, ___, ___, ___, ___)
#endif