list(APPEND PRESSURE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/DepthOfField.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DepthOfFieldShader.cpp)	
	
	
list(APPEND PRESSURE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/DepthOfField.h
    ${CMAKE_CURRENT_SOURCE_DIR}/DepthOfFieldShader.h)


set(PRESSURE_SRC ${PRESSURE_SRC} PARENT_SCOPE)	
set(PRESSURE_HEADERS ${PRESSURE_HEADERS} PARENT_SCOPE)	