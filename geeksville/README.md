# Geeksville notes

Alas, devcontainers don't work well with nix.  So instead just follow the original instructions after making
an Ubuntu based distrobox instance.  MAKE SURE TO ENABLE SYSTEMD in the selection gui.

Then add direnv to the shared ~/.bashrc (though I already did this)
> echo 'eval "$(direnv hook bash)"' >> ~/.bashrc

Then run the following commands in the "nix-devshell" distrobox:

```
bash # make sure we are using bash (and pull in the rc)
direnv allow # to pull in all required nix cruft
just init # setup build
just build all
```
