#!/bin/bash

test_file=./Build/test/mqtt_demo/bin/project_test

### use valgrind
# test_file="valgrind -v --leak-check=full --show-leak-kinds=definite,indirect ./Build/test/mqtt_demo/bin/project_test"

${test_file}
