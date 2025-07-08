# CMake generated Testfile for 
# Source directory: /Users/neelabhkashyap/Numeraxial-Quant-Risk/Engine
# Build directory: /Users/neelabhkashyap/Numeraxial-Quant-Risk/Engine/OREAnalytics
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples "nosetests" "run_examples_testsuite.py")
set_tests_properties(examples PROPERTIES  WORKING_DIRECTORY "/Users/neelabhkashyap/Numeraxial-Quant-Risk/Engine/Examples" _BACKTRACE_TRIPLES "/Users/neelabhkashyap/Numeraxial-Quant-Risk/Engine/CMakeLists.txt;44;add_test;/Users/neelabhkashyap/Numeraxial-Quant-Risk/Engine/CMakeLists.txt;0;")
subdirs("QuantLib")
subdirs("QuantExt")
subdirs("OREData")
subdirs("OREAnalytics")
subdirs("App")
subdirs("ORE-SWIG")
