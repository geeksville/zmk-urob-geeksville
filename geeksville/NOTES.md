
My typing speed is about 50 wpm on regular keyboard.

## Setup

* https://zmk.dev/docs/user-setup for firmware
* https://github.com/kmonad/kmonad on linux to allow custom doubletap for \ for instance
* GREAT hardware build guide: https://medium.com/@burgessj247/building-your-keyboard-5d59382b5613

* Use this board config: https://github.com/geeksville/corne-j-geeksville from mfg
* But then import it as a module into the miryoku per https://github.com/a741725193/zmk-new_corne/blob/main/README_EN.md
* Possibly by using the "outboard" feature: https://github.com/manna-harbour/miryoku_zmk?tab=readme-ov-file#supported-keyboards
* Use a config similar to this per the miryoku docs: https://github.com/manna-harbour/miryoku_zmk/blob/master/config/corneish_zen.keymap (a 42 key layout)

* TO BUILD MY VERSION use this action: https://github.com/geeksville/miryoku_geeksville/actions/workflows/build-eyelash_corne.yml

* Use this https://github.com/maatthc/keyboard_layers_app_companion to visualize
* Per https://www.youtube.com/watch?v=XtOQRHpXnj4 created custom repo at https://github.com/geeksville/corne-keyboard-config - this is the 'stock' qwerty layout copied from the original developer
* But better to use https://github.com/manna-harbour/miryoku_zmk/tree/master/docs/quickstart and "Build Options" on my custom fork actions.  Per https://github.com/manna-harbour/miryoku_zmk/#options for board use "nice_nano" for shield use: "corne_left nice_view_adapter nice_view,corne_right nice_view_adapter nice_view" for kconfig use "CONFIG_ZMK_DISPLAY=y CONFIG_ZMK_POINTING=y"
* Possibly do this to get the displays working https://www.reddit.com/r/ErgoMechKeyboards/comments/1g7w5bx/niceview_customization/
* Github actions on that repo build firmware

* How to do a gaming layout: https://www.reddit.com/r/ErgoMechKeyboards/comments/qzfiae/my_impressions_on_miryoku_36_key_layout_system/
* store device tree in build results: https://zmk.dev/docs/troubleshooting/building-issues#devicetree-related-issues for instance https://github.com/geeksville/miryoku_geeksville/actions/runs/20612132533/job/59198595890

* add studio support to the regular load (if it doesn't already have it) https://zmk.dev/docs/features/studio#adding-zmk-studio-support-to-a-keyboard

* FIXME after booting with regular load, then booting with miryoku load, compare the device trees and fix:
  * turn on serial debugging
  * remove extra missing encoder key per https://zmk.dev/docs/development/hardware-integration/new-shield and https://zmk.dev/docs/config/layout#matrix-transform 
  * see this tip to fix busted things: https://www.reddit.com/r/ErgoMechKeyboards/comments/1g7w5bx/niceview_customization/lub02mv/?context=10000
  * the following are missing from "chosen" in the devicetree: 		zephyr,display = &nice_view;
		zmk,studio-rpc-uart = &snippet_studio_rpc_usb_uart;
  * assign soft-off to a key combo (similar to regular load) https://github.com/manna-harbour/miryoku_zmk?tab=readme-ov-file#soft-off 
  * add reserved layouts so that zmkstudio work https://zmk.dev/docs/features/studio

* add backlash doubletap: That pesky \ is a bit of a headache to remember where it’s located on in the layers, so I added a double-tap to the / key, so a quick double press sends \.

* how to do settings_reset if needed: https://zmk.dev/docs/troubleshooting/connection-issues#building-a-reset-firmware

* enable usb logging with /workspaces/zmk-modules/corne-j-geeksville/build.yaml uncomment indicated lines
* experiment with changing sleep time to save battery

## Miryoku tuning

* enable right shift

### Add a game layer

per https://github.com/manna-harbour/miryoku/tree/master/docs/reference 
Add it as a "tap" layer, but only changing the left side keymaps (right keyboard goes unused until exiting game layer).  This means that you can exit game layer by using the same tap key on the right.

During thumb key layer-tap hold, keys on the same hand as the hold, other than mods, are used for additional features that are not needed during normal typing.

The top row pinkie column key activates the bootloader.

The top row index, middle, and ring column keys are used to switch between and return to alternate Base layers. Index is Base, middle is Extra, and ring is Tap. The Extra alpha arrangement defaults to QWERTY. Tap has only the tap functions of Base with no dual-function keys. Returning from Tap requires a reset or adding a custom keybinding. The Tap alpha arrangement defaults to Colemak Mod-DH. Alternative alpha arrangements are also available.

### Use keyboard LEDs to indicate layer status

see https://github.com/zmkfirmware/zmk/issues/554 for discussion.  ideally game mode button turns on led behind that key.

### improve bluetooth sleep wake behavior if necessary

Logitech's "Secret Sauce": Even when a Logitech keyboard is in deep sleep, it usually buffers the first keypress. You hit a key, the keyboard wakes up, reconnects, and then flushes that key to the computer. You might see a 500ms delay, but the letter still appears.

### Adjust timing

> I changed all layer taps and hold taps to be "balanced" flavor which is a zmk term that lets you use the keys quickly as long as the other key presses are fully contained within the mod/layer button press. As long as when you roll while typing you release the first pressed key before the second pressed key, this allows you to mod/layer much faster without worrying about accidental modding/layering.

Might be only an issue for fast typists...  Instead just tweak U_TAPPING_TERM
See gemini comments re custom lt behavirs:
tapping-term-ms = <150>;  // <--- ADJUST THIS VALUE
quick-tap-ms = <200>;     // Recommended (see below)
Increase (e.g., 300ms): Makes it easier to TAP. You have a wider window to press and release the key. Good if you find yourself accidentally triggering the Layer when you meant to type a space/letter.
Decrease (e.g., 150ms): Makes it easier to HOLD. You don't have to wait as long for the layer to activate. Good if the layer feels "laggy" or unresponsive.

Change this at flavor = "tap-preferred/balanced"; in miryoku_behaviors.dtsi
And use &blt instead of &lt

### Adjust symbol layout

see ![spaceship](spaceship.png) but really probably better to copy the following

My customized symbol layer is: (the extra underscore symbol could be replaced with something else...)
```
    ` ~ # & |    ^ { } [ ]
    ! _ : = $    @ ( ) _ ;
    % ? * + \    " - < > /

FIXME, remove _ from here, because it is already on a better position with the left thumb?
FIXME, find best possible usage of the other two left thumb symbols?
```

### [Comment](https://www.reddit.com/r/ErgoMechKeyboards/comments/1cim5s9/miryoku_for_programming/l2adh8g/) by /u/ShelZuuz

Miryoku doesn't have any kind of thought into the symbol layer. It's a "let's just follow the qwerty ISO symbols on top of the number pad", which, considering it's otherwise a Colemak layout is phoning it in a bit IMHO.

I use the following symbol layer layout on a 3x5 (C++ dev here). Now I'm not saying anybody else should be using it as is, but I do think it's a good idea to at least put a similar active thought process into designing your own symbol layer. 

```
    ` ~ # & |    ^ { } [ ]
    ! _ : = $    @ ( ) _ ;
    % ? * + \    / - < > "
```

**With this overarching thought process:**

Put the most commonly used symbols on the home row and also put symbols that are commonly used in bigrams or trigrams as a rolling streak. My most natural hand roll is outward so my rolling side is on the right keyboard. If your natural roll is inward the rolling keys should be on the left (so that parenthesis/braces/brackets/semi are in natural order as well as roll order).

**With that in mind:**

* My activation tap-hold key for the symbol layer is 4th finger home row on both sides (qwerty: S and L, colemak: R and I ). Since my brain won't allow pressing both of those together to result in a different symbol depending on the order you press it in, it needs to be the same symbol on both sides and thus should be your most commonly used singleton symbol. Which is underscore in my codebase.
* Next is getting the most common symbol trigram, which is (); so this fills out the right hand side home row for me and it forms an incredibly satisfying left to right sequence of (qwerty: S J K ; colemak:R N E O). Since ; corresponds with the qwerty semi you technically don't need it in the symbol layer, but it's easier to type while the Layer key is still down. I use Colemak DHB, but the ; key in Colemake is on a stretch pinkie position which I don't like. If your programming language doesn't commonly use semis then you probably don't need this on home row or even the symbol layer.
* I want to align {} with () so it's directly above it.
* <> wants to be where it is, because it was there first, and it's not going to move over one key to the left for anyone.
* This makes a natural place to put the minus sign directly to the left of that so you can easily do the -> pointer bigram, which is common in C++.
* The remaining common bigram is != which is on home row placement on the left.
* I wanted the slashes in mirror positions so that ends the layout on the right.
* Plus is in mirror with minus.
* Colon is used in home row as well, and it may be swapped with ! since it's less used than !, except that two colons in a row are common eg std::string, where two ! in a row are less so. Typing double keys in a pinkie is awkward.
* And the rest of the keys are mostly just spread out where I seem to most easily remember it.

## typing practice

https://gnusenpai.net/colemakclub/ (use this to learn homerow and a bit more, eventually transition to keybr once about 8 wpm)
https://www.keybr.com/ (use colemakDH-matrix layout)
https://monkeytype.com/ (gamified)

How to learn typing: https://www.reddit.com/r/ErgoMechKeyboards/comments/xn6vys/where_to_learn_colemak_keyboard_layout/iptfg8t/

## touchpad

recent driver: https://github.com/kureyakey/cirque-input-module
datasheet https://www.mouser.com/datasheet/2/892/TM023023_SPI-I2C-PINNTrackpad_SPEC1-1-1223670.pdf?srsltid=AfmBOorymOYk-phpkm-40ZS6k6vXa5kZat-nJxCaY9YqfcymCmiyQcVH
samplecode https://github.com/cirque-corp/Cirque_Pinnacle_1CA027/tree/master (or other projects in that same acct)
driver by main zmk dev: https://github.com/petejohanson/cirque-input-module
Needs this PR added? https://github.com/petejohanson/cirque-input-module/pull/2/files
But definitely missing the SHUTDOWN support

## case ideas

https://github.com/GEIGEIGEIST/TOTEM/tree/main/case

great thread on 3d printing keys https://www.reddit.com/r/ErgoMechKeyboards/comments/1q20z89/has_anyone_successfully_3d_printed_decentlooking/

Brillant auto tenting generator: https://github.com/GreenKeebz/Tenting

## related idea: open source 'stream deck' that works with ttgoish hardware?

Best StreamController spottify player: https://github.com/bamarc/SpotifyForStreamController but sounds busted per issue comments

Kinda like?
https://github.com/Lenochxd/WebDeck

But targeted at ttgo hardware and have it talk to https://github.com/StreamController/StreamController

To fix stream controller kde integration install https://github.com/StreamController/StreamController/issues/350 

Existing vscode side server for other streamdeck API: https://github.com/nicollasricas/decks-vscode
The corresponding client code for that other API: https://github.com/nicollasricas/vscode-deck (I think this is it) - it uses websockets to squirt JSON to the the server
How to use: https://marketplace.visualstudio.com/items?itemName=nicollasr.vscode-streamdeck
My project placeholder - possibly delete if I don't do anything: https://github.com/geeksville/VSCodeController

BETTER WAY: Use this extension instead: https://github.com/cursorless-dev/command-server
With this client! https://github.com/cursorless-dev/talon-command-client
hmm files are yucky

How about https://marketplace.visualstudio.com/items?itemName=SemanticWorkbenchTeam.mcp-server-vscode and using MCP

OK BEST: https://marketplace.visualstudio.com/items?itemName=eliostruyf.vscode-remote-control

This spottify plugin sounds buggy and kinda poorly written: https://github.com/ReneLu/SpotifyControl/issues

## related idea: fix kde battery display so it can show both split keyboard batteries

NOTE: This can't currently work because bluez doesn't support it on the client side.

https://zmk.dev/docs/config/split

> describe for me (in technical detail) how kde knows to show battery levels for bluetooth keyboards. where does it find this info? from the kernel? from bluez?

The Official Spec
Bluetooth SIG: Battery Service 1.0 (PDF)

Note: You don't need to create an account to download the PDF, even if they try to make it look like you do.

The "Cheat Sheet" for Implementation
If you don't want to wade through 20 pages of PDF padding, here is the entire spec in 4 lines:

Service UUID: 0x180F
Characteristic UUID: 0x2A19 (Battery Level)
Data Type: uint8 (Percent, 0 to 100).
Properties:
Read: Mandatory.
Notify: Optional (but effectively Mandatory if you want the icon to update without the PC polling you every 5 seconds).

Technical Gotchas
Multiple Batteries: If your device has two batteries (e.g., a split keyboard), you can instantiate the Battery Service twice. The OS differentiates them using the "Characteristic Presentation Format" descriptor (which tells the OS "This is the Left" vs "This is the Right").

Range: The spec strictly defines 0 to 100. Values 101-255 are "Reserved." Do not send 255 to indicate an error; just stop updating.

## Rejected ideas

* visualizers https://www.reddit.com/r/ErgoMechKeyboards/comments/ym6l7y/live_view_of_current_keymap_how_i_learn_changes/ to visualize (possibly with help of https://github.com/Neradoc/discotool)


https://www.moergo.com/collections/glove80-keyboards/products/glove80-split-ergonomic-keyboard-revision-2?variant=47282998771985

or this one <a href="https://typeractive.xyz/">https://typeractive.xyz/</a> 

Use this layout? https://theaustinwilcox.com/posts/switching-to-miryoku/
Which is based on https://colemakmods.github.io/mod-dh/ 
How to show keyboard layout: https://www.reddit.com/r/ErgoMechKeyboards/comments/1479ew6/miryoku_layout_key_caps/jnv6kil/

To print/plot keyboard layouts use this json format from the common web editor: https://github.com/manna-harbour/miryoku/discussions/71#discussioncomment-2108278

my custom layout (currently same as miriko): https://www.keyboard-layout-editor.com/#/gists/ee374401d888a0b6c4d084079a7ab120 
I would recommend blank keycaps and taping a print out of the reference to the bottom of your monitor or just opening it in a browser window when you need it because

1) you don't have to look down as far

2) your fingers won't be in the way

3) you get better contrast and colors especially for trying to read all the different layers

4) it can be removed when you no longer need it, but may be still tempted to use a reference as a crutch. Removing it can really speed up getting to full touch typing once you have it mostly down

5) I've never seen anyone make caps that have that much info or this specific layout. This is especially hard if you want a different keycap profile for each row (how sloped each row is).

6) in my opinion, blank keycaps are more aestheticly pleasing, so are better for the long run anyway

## 2nd keyboard beekeeb toucan
https://shopify.com/74566369587/account/orders/da334f60b75d1a2b2ed84878b67f5ed2
https://www.reddit.com/r/ErgoMechKeyboards/comments/1q0o5a2/a_few_more_pics_and_thoughts_on_the_beekeeb_toucan/nx03giq/
https://github.com/geeksville/zmk-keyboard-toucan

How to tweak scroll direction: https://youtu.be/0Jv1G2LUI-8?si=f-4mv2tPBj9dDB3_&t=334

## printable keycaps

1. The Gold Standard: MBK (Flat/Uniform)
This is likely what is already on your board if you bought a kit. It is flat with a wide surface area.

Search on Printables: MBK Keycaps by Joakim Stenberg (or look for the infused-kim repo on GitHub).

The File You Want: Look for the file ending in _homing.stl.

The Feature: Usually a tactile bar (ridge) at the bottom edge, or a deep dish (spherical scoop) depending on the remix.

Why: It keeps the profile low and matches the rest of the board perfectly.

2. The Ergonomic Choice: Chicago Steno (Sculpted)
If you want your fingers to feel hugged.

Search on Printables: Chicago Steno Low Profile Keycaps by levpopov.

The File You Want: cs_row_r3_homing_dots.stl or ...homing_bar.stl.

The Feature: These have a deeper spherical scoop than MBK, plus a physical dot or bar in the center.

Why: The scoop centers your finger automatically, so you don't even need the dot half the time.

3. The "Legs" Warning (Read this or you will cry)
Printing Choc V1 stems is the dark souls of 3D printing. The two little plastic legs ("fangs") are incredibly fragile and love to snap off inside your $5 switches, effectively ruining the switch.

If using FDM:

Do not print flat on the bed. The layer lines will make the legs snap instantly.

Tilt them 45 degrees backward (legends facing up/diagonal). This aligns the layer lines along the length of the legs for strength.

Use a 0.25mm nozzle if you have one. A 0.4mm nozzle is playing with fire for those tiny legs.

If using Resin (SLA):

Do not use standard brittle resin. You need ABS-like or a mix with Tenacious (flexible) resin. Standard resin legs will snap if you look at them wrong.

Next Step: Would you like me to find a specific "stem removal tool" model just in case you snap a leg off inside your favorite switch?
