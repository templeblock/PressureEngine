list(APPEND PRESSURE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/Keyboard.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Mouse.cpp)	
	
	
list(APPEND PRESSURE_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/Input.h
	${CMAKE_CURRENT_SOURCE_DIR}/Keyboard.h
	${CMAKE_CURRENT_SOURCE_DIR}/Mouse.h)


set(PRESSURE_SRC ${PRESSURE_SRC} PARENT_SCOPE)	
set(PRESSURE_HEADERS ${PRESSURE_HEADERS} PARENT_SCOPE)	