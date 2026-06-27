```markdown
# pomo

Simple CLI Pomodoro timer with i3status integration.

## Features

- 25/5 minute work/break cycles (configurable)
- Live timer in terminal
- Desktop notifications
- Writes JSON status to `/tmp/pomo_status` for i3bar
- Minimal C implementation

## Build & Install

```sh
make
sudo make install
```

## Usage

```sh
pomo          # default 25/5
pomo 30 7     # custom times
pomo -h       # help
```

## i3 Integration

After `make install`:

1. Use the wrapper:
   ```sh
   exec ~/.config/i3/statusw.sh
   ```

2. In your `~/.config/i3/config`:
   ```i3
   bar {
       status_command ~/.config/i3/statusw.sh
   }
   ```

The Pomodoro block appears on the left of the status bar.

## Files

- `src/pomo.c` — core timer
- `i3/statusw.py` — i3status wrapper
- `i3/statusw.sh` — launcher

Clean. Fast. No bullshit.
