#!/usr/bin/env python3
"""Independent executable reference for the documented Record Parser contract.

This does not inspect or execute either source variant and works on arbitrary
bytes, which makes it appropriate as the oracle for new minimization inputs.
"""
import sys


def main() -> int:
    data = sys.stdin.buffer.read(4098)
    prefix = b"name:"
    valid = (7 <= len(data) <= 4096 and data.startswith(prefix) and data.endswith(b"\n")
             and all((ord('0') <= b <= ord('9') or ord('a') <= b <= ord('z')
                      or ord('A') <= b <= ord('Z')) for b in data[5:-1])
             and 1 <= len(data[5:-1]) <= 15)
    if valid:
        sys.stdout.buffer.write(b"OK:" + data[5:])
        return 0
    sys.stdout.buffer.write(b"ERR\n")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
