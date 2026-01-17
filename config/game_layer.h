
// Geeksville add game layer

// Game layer: Replaces left 3x6 + three thumb keys with gaming layout.
// Number keys 1-5 shift to 6-0 when shift is held.
SIMPLE_MORPH(game_1_6, SFT, &kp N1, &kp N6)
SIMPLE_MORPH(game_2_7, SFT, &kp N2, &kp N7)
SIMPLE_MORPH(game_3_8, SFT, &kp N3, &kp N8)
SIMPLE_MORPH(game_4_9, SFT, &kp N4, &kp N9)
SIMPLE_MORPH(game_5_0, SFT, &kp N5, &kp N0)
// SIMPLEx_MORPH(game_esc_tab, SFT, &kp ESC, &kp TAB)

ZMK_LAYER(Game,
//╭──────┬──────┬──────┬──────┬──────┬──────╮                          ╭──────┬──────┬──────┬──────┬──────┬──────╮
  &kp TAB &game_1_6 &game_2_7 &game_3_8 &game_4_9 &game_5_0              ___    ___    ___    ___    ___    ___    &to DEF
//├──────┼──────┼──────┼──────┼──────┼──────┤                          ├──────┼──────┼──────┼──────┼──────┼──────┤
  &kp ESC  &kp Q  &kp A  &kp W  &kp D  &kp R          ___ ___ ___          ___    ___    ___    ___    ___    ___
//├──────┼──────┼──────┼──────┼──────┼──────┤                          ├──────┼──────┼──────┼──────┼──────┼──────┤
  &kp LCTRL &kp M &kp C &kp S  &kp E  &kp F             ___              ___    ___    ___    ___    ___    ___
//╰──────┴──────┴──────┼──────┼──────┼──────┤                          ├──────┼──────┼──────┼──────┴──────┴──────╯
                &kp LALT &kp SPACE &kp LSHFT                             ___    ___ &smart_mouse
//                     ╰──────┴──────┴──────╯                          ╰──────┴──────┴──────╯
)