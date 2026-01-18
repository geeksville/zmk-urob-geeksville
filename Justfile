default:
    @just --list --unsorted

config := absolute_path('config')
build := absolute_path('.build')
out := absolute_path('firmware')
draw := absolute_path('draw')

# parse build.yaml and filter targets by expression
_parse_targets $expr:
    #!/usr/bin/env bash
    attrs="[.board, .shield, .snippet, .\"artifact-name\"]"
    filter="(($attrs | map(. // [.]) | combinations), ((.include // {})[] | $attrs)) | join(\",\")"
    echo "$(yq -r "$filter" build.yaml | grep -v "^," | grep -i "${expr/#all/.*}")"

# build firmware for single board & shield combination
_build_single $board $shield $snippet $artifact *west_args:
    #!/usr/bin/env bash
    set -euo pipefail
    artifact="${artifact:-${shield:+${shield// /+}-}${board}}"
    build_dir="{{ build / '$artifact' }}"

    echo "Building firmware for $artifact..."
    west build -s zmk/app -d "$build_dir" -b $board {{ west_args }} ${snippet:+-S "$snippet"} -- \
        -DZMK_CONFIG="{{ config }}" ${shield:+-DSHIELD="$shield"}

    if [[ -f "$build_dir/zephyr/zmk.uf2" ]]; then
        mkdir -p "{{ out }}" && cp "$build_dir/zephyr/zmk.uf2" "{{ out }}/$artifact.uf2"
    else
        mkdir -p "{{ out }}" && cp "$build_dir/zephyr/zmk.bin" "{{ out }}/$artifact.bin"
    fi

# build firmware for matching targets
build expr *west_args:
    #!/usr/bin/env bash
    set -euo pipefail
    targets=$(just _parse_targets {{ expr }})

    [[ -z $targets ]] && echo "No matching targets found. Aborting..." >&2 && exit 1
    echo "$targets" | while IFS=, read -r board shield snippet artifact; do
        just _build_single "$board" "$shield" "$snippet" "$artifact" {{ west_args }}
    done

# Shorthand to build my eyelash corne
build-eyelash *args:
    # just build eyelash_corne_left,nice_view,studio-rpc-usb-uart {{ args }}
    just build nice_nano_v2,eyeslash_corne_central_dongle {{ args }}
    just build nice_nano_v2,eyeslash_corne_peripheral_left {{ args }}
    just build nice_nano_v2,eyeslash_corne_peripheral_right {{ args }}

# Shorthand to build my left toucan
build-toucan *args:
    just build seeeduino_xiao_ble,toucan_left {{ args }}
    just build seeeduino_xiao_ble,toucan_right {{ args }}

# Flash firmware to keyboard (internal helper)
_flash artifact:
    #!/usr/bin/env bash
    set -euo pipefail
    mount_point="/run/media/kevinh/NICENANO"
    device="/dev/sda"
    uf2_file="{{ out }}/{{ artifact }}.uf2"
    
    # Ensure unmount happens on exit, even if previous operations fail
    trap 'if mountpoint -q "$mount_point" 2>/dev/null; then sudo umount "$mount_point" 2>/dev/null || true; fi' EXIT
    
    if [[ ! -f "$uf2_file" ]]; then
        echo "Error: $uf2_file not found. Build first." >&2
        exit 1
    fi
    
    # Mount if not already mounted
    if ! mountpoint -q "$mount_point"; then
        echo "Mounting $device to $mount_point..."
        sudo mkdir -p "$mount_point"
        sudo mount "$device" "$mount_point"
    fi
    
    echo "Copying $uf2_file to $mount_point..."
    sudo cp "$uf2_file" "$mount_point/zmk.uf2"
    sync
    
    echo "Done! {{ artifact }} flashed."

flash-eyelash-dongle:
    just _flash eyeslash_corne_central_dongle_oled
    
# Flash left eyelash_corne keyboard
flash-eyelash-left:
    # just _flash nice_view-eyelash_corne_left
    just _flash eyeslash_corne_peripheral_left+nice_view_custom-nice_nano_v2

# Flash right eyelash_corne keyboard
flash-eyelash-right:
    # Now using the dongle version
    # just _flash nice_view-eyelash_corne_right
    just _flash eyeslash_corne_peripheral_right+nice_view_custom-nice_nano_v2

flash-eyelash-reset:
    just _flash settings_reset-eyelash_corne_left

# Flash left toucan keyboard
flash-toucan-left:
    just _flash toucan_left+rgbled_adapter+nice_view_gem-seeeduino_xiao_ble

# Flash right toucan keyboard
flash-toucan-right:
    just _flash toucan_right+rgbled_adapter-seeeduino_xiao_ble

# clear build cache and artifacts
clean:
    rm -rf {{ build }} {{ out }}

# clear all automatically generated files
clean-all: clean
    rm -rf .west zmk

# clear nix cache
clean-nix:
    nix-collect-garbage --delete-old

# parse & plot keymap
draw-legacy:
    #!/usr/bin/env bash
    set -euo pipefail
    keymap -c "{{ draw }}/config.yaml" parse -z "{{ config }}/base.keymap" --virtual-layers Combos >"{{ draw }}/base.yaml"
    yq -Yi '.combos.[].l = ["Combos"]' "{{ draw }}/base.yaml"
    keymap -c "{{ draw }}/config.yaml" draw "{{ draw }}/base.yaml" -k "ferris/sweep" >"{{ draw }}/base.svg"

# my customized layout
draw:
    #!/usr/bin/env bash
    set -euo pipefail
    keymap -c "{{ draw }}/config.yaml" parse -z "{{ config }}/eyeslash_corne.keymap" --virtual-layers Combos >"{{ draw }}/base.yaml"
    yq -Yi '.combos.[].l = ["Combos"]' "{{ draw }}/base.yaml"
    keymap -c "{{ draw }}/config.yaml" draw "{{ draw }}/base.yaml" -j "{{ config }}/eyeslash_corne.json" >"{{ draw }}/base.svg"

# initialize west
init:
    west init -l config
    west update --fetch-opt=--filter=blob:none
    west zephyr-export

# list build targets
list:
    @just _parse_targets all | sed 's/,*$//' | sort | column

# update west
update:
    west update --fetch-opt=--filter=blob:none

# upgrade zephyr-sdk and python dependencies
upgrade-sdk:
    nix flake update --flake .

[no-cd]
test $testpath *FLAGS:
    #!/usr/bin/env bash
    set -euo pipefail
    testcase=$(basename "$testpath")
    build_dir="{{ build / "tests" / '$testcase' }}"
    config_dir="{{ '$(pwd)' / '$testpath' }}"
    cd {{ justfile_directory() }}

    if [[ "{{ FLAGS }}" != *"--no-build"* ]]; then
        echo "Running $testcase..."
        rm -rf "$build_dir"
        west build -s zmk/app -d "$build_dir" -b native_posix_64 -- \
            -DCONFIG_ASSERT=y -DZMK_CONFIG="$config_dir"
    fi

    ${build_dir}/zephyr/zmk.exe | sed -e "s/.*> //" |
        tee ${build_dir}/keycode_events.full.log |
        sed -n -f ${config_dir}/events.patterns > ${build_dir}/keycode_events.log
    if [[ "{{ FLAGS }}" == *"--verbose"* ]]; then
        cat ${build_dir}/keycode_events.log
    fi

    if [[ "{{ FLAGS }}" == *"--auto-accept"* ]]; then
        cp ${build_dir}/keycode_events.log ${config_dir}/keycode_events.snapshot
    fi
    diff -auZ ${config_dir}/keycode_events.snapshot ${build_dir}/keycode_events.log
