#!/usr/bin/env bash

if [[ "${TRAVIS_OS_NAME}" == osx ]]; then
    brew install check cmake
elif [[ "${TRAVIS_OS_NAME}" == linux ]]; then
	wget 'http://downloads.sourceforge.net/project/check/check/0.10.0/check-0.10.0.tar.gz'
	tar xzf 'check-0.10.0.tar.gz'
	cd 'check-0.10.0'
	./configure
	make
	make check
	sudo make install
fi
