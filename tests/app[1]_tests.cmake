add_test([=[char2bin_str.any]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=char2bin_str.any]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[char2bin_str.any]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[uint2hex.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=uint2hex.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[uint2hex.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[uint2.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=uint2.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[uint2.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[is_num.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=is_num.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[is_num.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[str2uint.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=str2uint.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[str2uint.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[cpu.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=cpu.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[cpu.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[memory.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=memory.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[memory.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[trim.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=trim.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[trim.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[split.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=split.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[split.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[vector.any_tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=vector.any_tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[vector.any_tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[core.tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=core.tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[core.tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[command.tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=command.tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[command.tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[i_ALU.tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=i_ALU.tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[i_ALU.tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[f_ALU.tests]=]  /home/mephi/cpp/almost_cpu/tests/app [==[--gtest_filter=f_ALU.tests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[f_ALU.tests]=]  PROPERTIES WORKING_DIRECTORY /home/mephi/cpp/almost_cpu/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  app_TESTS char2bin_str.any uint2hex.any_tests uint2.any_tests is_num.any_tests str2uint.any_tests cpu.any_tests memory.any_tests trim.any_tests split.any_tests vector.any_tests core.tests command.tests i_ALU.tests f_ALU.tests)
