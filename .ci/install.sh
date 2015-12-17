#!/usr/bin/env bash

if [[ "${TRAVIS_OS_NAME}" == osx ]]; then
    brew install check cmake
fi
