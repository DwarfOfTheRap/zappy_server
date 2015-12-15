#!/usr/bin/env bash

if [[ "${TRAVIS_OS_NAME}" == osx ]]; then
    brew install check cmake
else
    sudo apt-get update -qq
    sudo apt-get install -y check cmake
fi
