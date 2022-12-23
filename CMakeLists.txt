cmake_minimum_required(VERSION 3.22)

get_filename_component(CMAKE_MODULE_PATH "../CMakeFunctions" ABSOLUTE)
include(auxil_functions)
include(general_function)


#=======================General setting=================================#
set(ProjName cad)                                                       #
																		#
set(IS_LIB true)                                                       #
set(NEED_CONSOLE true)                                                 #
set(NEED_RESOURCES false)                                                #
set(NEED_FORMS false)                                                    #
																		#
set(NEED_QT false)                                                       #
set(QT_LIST_OF_MODULES Core Gui Widgets OpenGL OpenGLWidgets)           #
																		#
#===============add sub projects========================================#
																		#
#set (nameSubProj ptd)                                                   #
#ADD_SUB_PROJ(${ProjName} ${nameSubProj} ../${nameSubProj})              #
#
#set (nameSubProj table_widget)                                          #
#ADD_SUB_PROJ(${ProjName} ${nameSubProj} ../${nameSubProj})              #

##===============add Libs ==============================================#
##add xlnt lib                                                          #
#FIND_PROJECT(xlnt ../xlnt/share/xlnt)                                  #
#																		#
##add cavc header only lib                                              #
#list(APPEND LIST_PRIVATE_INCLUDES_DIR ../cavc/include)                 #
#=======================================================================#



project(${ProjName} LANGUAGES CXX)

#====================set configure and general flafgs===============
ADD_FLAGS()

#general work
GENERAL_FUNC(${ProjName} ${IS_LIB} ${NEED_CONSOLE} ${NEED_RESOURCES} ${NEED_FORMS} ${NEED_QT})

#off console
ADD_LINKER_FLAGS(${NEED_CONSOLE} ${IS_LIB})
