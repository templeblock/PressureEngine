list(APPEND PRESSURE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp)	
	
	
list(APPEND PRESSURE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.h)


set(PRESSURE_SRC ${PRESSURE_SRC} PARENT_SCOPE)	
set(PRESSURE_HEADERS ${PRESSURE_HEADERS} PARENT_SCOPE)	