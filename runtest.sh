#!/bin/bash

test_file=./Build/test/mqtt_demo/bin/project_test

if [ $# != 0 ]; then
  for arg in "$@"; do
    if [ "$arg" = "val" ]; then
      ### use valgrind
      test_file="valgrind -v --leak-check=full --show-leak-kinds=definite,indirect ${test_file}"

    fi

  done
fi

${test_file}
