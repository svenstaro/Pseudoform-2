set(pong-cpp_srcs
	main.cpp
)

add_executable(pong-cpp
	${pong-cpp_srcs}
)

target_link_libraries(pong-cpp 
	Pseudoform
)
