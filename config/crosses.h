/*                                      54 KEY MATRIX / LAYOUT MAPPING

  ╭────────────────────────╮               ╭────────────────────────╮
  │  0   1   2   3   4   5 │               │  6   7   8   9  10  11 │
  │ 12  13  14  15  16  17 ╰──╮         ╭──╯ 18  19  20  21  22  23 │
  │ 24  25  26  27  28  29    ╰────┬────╯    30  31  32  33  34  35 │
  │ 36  37  38  39  40  41         │         42  43  44  45  46  47 │
  ╰───╮ 48  49  50 ╭───────────────┴───────────────╮ 51  52  53 ╭───╯
      ╰────────────╯                               ╰────────────╯
 ╭─────────────────────────╮               ╭─────────────────────────╮
 │ xxx xxx xxx xxx xxx xxx │               │ xxx xxx xxx xxx xxx xxx │
 │ LT5 LT4 LT3 LT2 LT1 LT0 │               │ RT0 RT1 RT2 RT3 RT4 RT5 │
 │ LM5 LM4 LM3 LM2 LM1 LM0 ╰──╮         ╭──╯ RM0 RM1 RM2 RM3 RM4 RM5 │
 │ LB5 LB4 LB3 LB2 LB1 LB0    ╰────┬────╯    RB0 RB1 RB2 RB3 RB4 RB5 │
 ╰───╮LH2 LH1 LH0╭─────────────────┴────────────────╮RH0 RH1 RH2╭────╯
     ╰───────────╯                                  ╰───────────╯

 T : Top
 M : Middle
 B : Bottom
 H : Hand
*/

#pragma once

#define LT0  17  // left-top row
#define LT1  16
#define LT2  15
#define LT3  14
#define LT4  13
#define LT5  12

#define RT0  18  // right-top row
#define RT1  19
#define RT2  20
#define RT3  21
#define RT4  22
#define RT5  23

#define LM0 24  // left-middle row
#define LM1 25
#define LM2 26
#define LM3 27
#define LM4 28
#define LM5 29

#define RM0 30  // right-middle row
#define RM1 31
#define RM2 32
#define RM3 33
#define RM4 34
#define RM5 35

#define LB0 36  // left-bottom row
#define LB1 37
#define LB2 38
#define LB3 39
#define LB4 40
#define LB5 41

#define RB0 42  // right-bottom row
#define RB1 43
#define RB2 44
#define RB3 45
#define RB4 46
#define RB5 47

#define LH0 50  // left thumb keys
#define LH1 49
#define LH2 48

#define RH0 51  // right thumb keys
#define RH1 52
#define RH2 53



