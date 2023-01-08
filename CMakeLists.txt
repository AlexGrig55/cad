cmake_minimum_required(VERSION 3.22)

#========================Auxilary functions=====================
function(GET_FILES_FROM_DIR path regExpForFilter)
	file(GLOB files "${path}/${regExpForFilter}")

	get_property(tmpVar GLOBAL PROPERTY globVar)
	set(listFiles ${tmpVar} ${files})
	set_property(GLOBAL PROPERTY globVar ${listFiles})

	file(GLOB files "${path}/*")
	foreach(localPath ${files})
		if(IS_DIRECTORY ${localPath})
			GET_FILES_FROM_DIR(${localPath} ${regExpForFilter})
		endif()
	endforeach()

endfunction(GET_FILES_FROM_DIR)

function(GROUP_SRC srcs startPath)
	get_filename_component(startPath "${startPath}" ABSOLUTE)

	foreach(localFile ${srcs})

		#convert source file to absolute
		get_filename_component(ABSOLUTE_PATH "${localFile}" ABSOLUTE)
		get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)

		if (NOT "${PARENT_DIR}" STREQUAL ${startPath})
			# Remove common directory prefix to make the group
			string(REPLACE "${startPath}/" "" GROUP "${PARENT_DIR}")
			source_group("${GROUP}" FILES "${localFile}")
		endif()

	endforeach()

endfunction(GROUP_SRC)
#========================Auxilary functions=====================



set(PROJECT_NAME cad)

project(${PROJECT_NAME} LANGUAGES CXX)


#===============================Set cache values========================================
set(IS_STATIC_LIB_${PROJECT_NAME} TRUE CACHE BOOL "Configs")
set(PATH_TO_GEOM_LIB "" CACHE PATH "Configs")
#===============================Set cache values========================================


#===============================Set project setting========================================
set(FLAG_PREFIX -)
if (MSVC)
	set(FLAG_PREFIX /)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG_PREFIX}MP")#using threads for compile
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG_PREFIX}WX")#warning is err
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAG_PREFIX}Oi ${FLAG_PREFIX}Ot ${FLAG_PREFIX}GL")
#===============================Set project setting========================================


#==============================Find pathes to src===============================
set(SOURCE_DIR "src")
set(INCLUDE_DIR "include/${PROJECT_NAME}")

set_property(GLOBAL PROPERTY globVar "")
GET_FILES_FROM_DIR( ${SOURCE_DIR} "*.c*")
GET_FILES_FROM_DIR( ${SOURCE_DIR} "*.h*")
get_property(SRC_FILES GLOBAL PROPERTY globVar)

set_property(GLOBAL PROPERTY globVar "")
GET_FILES_FROM_DIR( ${INCLUDE_DIR} "*.h*")
get_property(INCLUDE_FILES GLOBAL PROPERTY globVar)

set(ALL_FILES ${SRC_FILES} ${INCLUDE_FILES})
#==============================Find pathes to src===============================


#==============================Add lib===============================
if(${IS_STATIC_LIB_${PROJECT_NAME}})
	add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

	target_compile_definitions(${PROJECT_NAME} PUBLIC CAD_STATIC=1)
else()
	add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

	target_compile_definitions(${PROJECT_NAME} PRIVATE CAD_SHARED=1)
	target_compile_definitions(${PROJECT_NAME} PRIVATE CAD_EXPORT=1)
endif()
#==============================Add lib===============================


#=============================Add sub proj==========================
if(NOT EXISTS ${PATH_TO_GEOM_LIB}/CMakeLists.txt)
	message(FATAL_ERROR "Path to <geom> lib not found, set correct path")
endif()

file(MAKE_DIRECTORY sub_proj/geom)
add_subdirectory(${PATH_TO_GEOM_LIB} sub_proj/geom)
target_link_libraries(${PROJECT_NAME} PUBLIC geom)
target_include_directories(${PROJECT_NAME} PUBLIC ${PATH_TO_GEOM_LIB}/include)
#=============================Add sub proj==========================


#==================== Create filters======================================
GROUP_SRC("${SRC_FILES}" ${SOURCE_DIR})
GROUP_SRC("${INCLUDE_FILES}" ${INCLUDE_DIR})
#==================== Create filters======================================

#==================== include======================================
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR}/..)
#==================== include======================================
