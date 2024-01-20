#!/bin/bash

gcovr -r .. -e CMakeFiles | grep -v _deps | grep -vE "^(\s|tests|headers|.*\command\.cpp)"

