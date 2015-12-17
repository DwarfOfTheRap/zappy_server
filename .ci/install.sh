#!/usr/bin/env bash

if [[ "${TRAVIS_OS_NAME}" == osx ]]; then
    brew install check cmake
elif [[ "${TRAVIS_OS_NAME}" == linux ]]; then
	sudo apt-get update
	sudo apt-get install check
fi
