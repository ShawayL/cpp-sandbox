add_executable(find_submatrix main.cpp)

add_executable(cpp_sandbox::find_submatrix ALIAS find_submatrix)

target_compile_features(find_submatrix PRIVATE cxx_std_11)
