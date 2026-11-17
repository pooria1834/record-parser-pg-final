# Record Parser contract

A complete input consists of the ASCII prefix `name:`, one to fifteen
ASCII letters or decimal digits, and a single final LF. On acceptance stdout
is `OK:` followed by the value and LF, with exit 0. Every other input has
stdout `ERR\n` and exit 2. The input buffer is bounded at 4096 bytes.
The fixture expectations are specified from this contract.
