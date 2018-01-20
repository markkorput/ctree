if( NOT TARGET ctree )
	get_filename_component( ctree_SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src" ABSOLUTE )
	get_filename_component( ctree_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../include" ABSOLUTE )
	get_filename_component( CINDER_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE )

	FILE(GLOB ctree_SOURCES ${ctree_SOURCE_PATH}/ctree/*.cpp)

	add_library( ctree ${ctree_SOURCES} )

	target_include_directories( ctree PUBLIC "${ctree_INCLUDE_PATH}" )
	target_include_directories( ctree SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )

	if( NOT TARGET cinder )
		    include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
		    find_package( cinder REQUIRED PATHS
		        "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
		        "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
	endif()
	target_link_libraries( ctree PRIVATE cinder )
endif()
