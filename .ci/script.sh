#!/bin/bash

make && make test
if [[ $0 -ne 0 ]]; then
    ./test/test_zappy_server 2>/dev/null
    ./test/test_zappy_server.sh
fi
