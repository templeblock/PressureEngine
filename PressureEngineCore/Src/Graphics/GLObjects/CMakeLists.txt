list(APPEND PRESSURE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/FrameBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/IndexBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VertexArray.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VertexBuffer.cpp)	
	
	
list(APPEND PRESSURE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/FrameBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GLObjects.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IndexBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VertexArray.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VertexBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VertexBufferLayout.h)


set(PRESSURE_SRC ${PRESSURE_SRC} PARENT_SCOPE)	
set(PRESSURE_HEADERS ${PRESSURE_HEADERS} PARENT_SCOPE)	