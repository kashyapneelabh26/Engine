#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "QuantLib::QuantLib" for configuration "RelWithDebInfo"
set_property(TARGET QuantLib::QuantLib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(QuantLib::QuantLib PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libQuantLib.1.38.0.dylib"
  IMPORTED_SONAME_RELWITHDEBINFO "@rpath/libQuantLib.1.dylib"
  )

list(APPEND _cmake_import_check_targets QuantLib::QuantLib )
list(APPEND _cmake_import_check_files_for_QuantLib::QuantLib "${_IMPORT_PREFIX}/lib/libQuantLib.1.38.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
