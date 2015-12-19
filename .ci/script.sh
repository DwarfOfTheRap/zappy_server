#!/bin/bash

make && make test
if [[ "$?" -ne 0 ]]; then
    ./test/test_zappy_server 2>/dev/null
    ./test/test_zappy_server.sh
fi
