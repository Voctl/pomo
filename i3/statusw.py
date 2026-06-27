#!/usr/bin/env python3
import sys
import json
import os

#Denis baba yorgun

def get_pomo_block():
    statusp = '/tmp/pomo_status'
    if os.path.exists(status_path):
        try:
            with open(statusp, 'r') as f:
                data = json.load(f)
                full_text = data.get('full_text', '').strip()
                if full_text:
                    return {
                        "name": "pomodoro",
                        "full_text": f" {full_text} ",
                        "color": data.get("color", "#FF9900")
                    }
        except Exception:
            pass
    return None

def main():
    try:
        header = sys.stdin.readline()
        if not header:
            return
        sys.stdout.write(header)
        sys.stdout.flush()
    except Exception:
        return

    try:
        line2 = sys.stdin.readline()
        if not line2:
            return
        sys.stdout.write(line2)
        sys.stdout.flush()
    except Exception:
        return

    while True:
        try:
            line = sys.stdin.readline()
            if not line:
                break
            
            stripped = line.strip()
            prefix = ""
            if stripped.startswith(','):
                prefix = ","
                json_str = stripped[1:]
            else:
                json_str = stripped
            
            blocks = json.loads(json_str)
            pomo = get_pomo_block()
            if pomo:
                blocks.insert(0, pomo)
                
            sys.stdout.write(prefix + json.dumps(blocks) + '\n')
            sys.stdout.flush()
        except Exception:
            sys.stdout.write(line)
            sys.stdout.flush()

if __name__ == '__main__':
    main()
