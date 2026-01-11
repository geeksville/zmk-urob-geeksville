# Geeksville notes

Alas, devcontainers don't work well with nix.  So instead just follow the original instructions after making
an Ubuntu based distrobox instance.  MAKE SURE TO ENABLE SYSTEMD in the selection gui.

## TODO

* Possibly add . to the nummode layer?  To allow typing 345.23 easily.

## Build instructions
Then add direnv to the shared ~/.bashrc (though I already did this)
> echo 'eval "$(direnv hook bash)"' >> ~/.bashrc

Then run the following commands in the "nix-devshell" distrobox:

```
bash # make sure we are using bash (and pull in the rc)
direnv allow # to pull in all required nix cruft
just init # setup build
just build all
```

Note: the ble status advertisements spit out warnings due to:

```
[100/555] Building C object CMakeFiles/app.dir/home/kevinh/development/keyboard/zmk-urob-geeksville/modules/prospector-zmk-module/src/status_advertisement.c.obj
/home/kevinh/development/keyboard/zmk-urob-geeksville/modules/prospector-zmk-module/src/status_advertisement.c:80:9: note: '#pragma message: *** PROSPECTOR SIMPLE SEPARATED ADVERTISING ***'
   80 | #pragma message "*** PROSPECTOR SIMPLE SEPARATED ADVERTISING ***"
      |         ^~~~~~~
In file included from /home/kevinh/development/keyboard/zmk-urob-geeksville/zephyr/include/zephyr/device.h:13,
                 from /home/kevinh/development/keyboard/zmk-urob-geeksville/zephyr/include/zephyr/drivers/usb/usb_dc.h:20,
                 from /home/kevinh/development/keyboard/zmk-urob-geeksville/zephyr/include/zephyr/usb/usb_device.h:41,
                 from /home/kevinh/development/keyboard/zmk-urob-geeksville/zmk/app/include/zmk/usb.h:9,
                 from /home/kevinh/development/keyboard/zmk-urob-geeksville/modules/prospector-zmk-module/src/status_advertisement.c:19:
/home/kevinh/development/keyboard/zmk-urob-geeksville/zephyr/include/zephyr/init.h:193:44: warning: initialization of 'int (*)(void)' from incompatible pointer type 'int (*)(const struct device *)' [-Wincompatible-pointer-types]
  193 |                         .init_fn = {.sys = (init_fn_)},                        \
      |                                            ^
/home/kevinh/development/keyboard/zmk-urob-geeksville/zephyr/include/zephyr/init.h:174:9: note: in expansion of macro 'SYS_INIT_NAMED'
  174 |         SYS_INIT_NAMED(init_fn, init_fn, level, prio)
      |         ^~~~~~~~~~~~~~
/home/kevinh/development/keyboard/zmk-urob-geeksville/modules/prospector-zmk-module/src/status_advertisement.c:796:1: note: in expansion of macro 'SYS_INIT'
  796 | SYS_INIT(stop_default_advertising, APPLICATION, 90);
      | ^~~~~~~~

```

This **might** be okay?  because the ptr is in a union where the argument is used correctly.  We'll see
if it runs...

It also prints some warnings about misconfigured CONFIG entries when building the right half (because
some of those flags only are set on the left).  Might be okay also...
