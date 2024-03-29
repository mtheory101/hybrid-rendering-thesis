###
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#
# Note: Some of the libraries GMEngine may link to may have additional
# requirements or restrictions.
#
###

cmake_minimum_required(VERSION 2.8)

set(NAME HybridMethods)
project(${NAME})

file(GLOB_RECURSE OPTIX_SCRIPTS ${CMAKE_SOURCE_DIR}/bin/resources/optix/*.cu)
file(GLOB_RECURSE GLSL_SHADERS ${CMAKE_SOURCE_DIR}/bin/resources/shaders/*.*)
file(GLOB_RECURSE INI_CONFIGS ${CMAKE_SOURCE_DIR}/bin/resources/ini/*.ini)
file(GLOB_RECURSE MATERIAL_CONFIGS ${CMAKE_SOURCE_DIR}/bin/resources/materials/*.mat)

file(GLOB_RECURSE GL3W_HEADER ${CMAKE_SOURCE_DIR}/depends/include/GL3/*.h)
file(GLOB_RECURSE GLUT_HEADER ${CMAKE_SOURCE_DIR}/depends/include/GL/*.h)
file(GLOB_RECURSE ASSIMP_HEADER_H ${CMAKE_SOURCE_DIR}/depends/include/AssImp/*.h)
file(GLOB_RECURSE ASSIMP_HEADER ${CMAKE_SOURCE_DIR}/depends/include/AssImp/*.hpp)
file(GLOB 		  FILE_HEADER ./File/*.h)
file(GLOB		  FILE_BART_HEADER ./File/BARTLoader/*.h)
file(GLOB		  PARSER_HEADER ./Parser/*.h)
file(GLOB		  PARSER_BART_HEADER ./Parser/BART/*.h)
file(GLOB 		  RENDER_HEADER ./Render/*.h)
file(GLOB 		  RENDER_GBUFFER_PASS_HEADER ./Render/Passes/GBuffer/*.h)
file(GLOB 		  RENDER_LIGHTSOURCE_PASS_HEADER ./Render/Passes/Lightsource/*.h)
file(GLOB 		  RENDER_BLOOM_PASS_HEADER ./Render/Passes/Bloom/*.h)
file(GLOB 		  RENDER_SSAO_PASS_HEADER ./Render/Passes/SSAO/*.h)
file(GLOB 		  RENDER_RAY_PASS_HEADER ./Render/Passes/Raytrace/*.h)
file(GLOB 		  RENDER_FINAL_PASS_HEADER ./Render/Passes/Final/*.h)
file(GLOB_RECURSE RAYTRACER_HEADER ./Raytracer/*.h)
file(GLOB_RECURSE SCENE_HEADER ./Scene/*.h)
file(GLOB ROOT_HEADER *.h)

file(GLOB_RECURSE GL3W_SOURCE ${CMAKE_SOURCE_DIR}/depends/include/GL3/*.c)
file(GLOB_RECURSE GLUT_SOURCE ${CMAKE_SOURCE_DIR}/depends/include/GL/src/*.c)
file(GLOB_RECURSE ASSIMP_SOURCE_C ${CMAKE_SOURCE_DIR}/depends/include/AssImp/*.c)
file(GLOB_RECURSE ASSIMP_SOURCE ${CMAKE_SOURCE_DIR}/depends/include/AssImp/*.cpp)
file(GLOB		  FILE_SOURCE ./File/*.cpp)
file(GLOB		  FILE_BART_SOURCE ./File/BARTLoader/*.cpp)
file(GLOB		  PARSER_SOURCE ./Parser/*.cpp)
file(GLOB		  PARSER_BART_SOURCE ./Parser/BART/*.cpp)
file(GLOB 		  RENDER_SOURCE ./Render/*.cpp)
file(GLOB 		  RENDER_GBUFFER_PASS_SOURCE ./Render/Passes/GBuffer/*.cpp)
file(GLOB 		  RENDER_LIGHTSOURCE_PASS_SOURCE ./Render/Passes/Lightsource/*.cpp)
file(GLOB 		  RENDER_BLOOM_PASS_SOURCE ./Render/Passes/Bloom/*.cpp)
file(GLOB 		  RENDER_SSAO_PASS_SOURCE ./Render/Passes/SSAO/*.cpp)
file(GLOB 		  RENDER_RAY_PASS_SOURCE ./Render/Passes/Raytrace/*.cpp)
file(GLOB 		  RENDER_FINAL_PASS_SOURCE ./Render/Passes/Final/*.cpp)
file(GLOB_RECURSE RAYTRACER_SOURCE ./Raytracer/*.cpp)
file(GLOB_RECURSE SCENE_SOURCE ./Scene/*.cpp)
file(GLOB ROOT_SOURCE *.cpp)

SOURCE_GROUP("Resource Files\\Optix\\" FILES ${OPTIX_SCRIPTS})
SOURCE_GROUP("Resource Files\\Shaders\\" FILES ${GLSL_SHADERS})
SOURCE_GROUP("Resource Files\\ini\\" FILES ${INI_CONFIGS})
SOURCE_GROUP("Resource Files\\Materials\\" FILES ${MATERIAL_CONFIGS})

SOURCE_GROUP("Header Files\\Depends\\Gl3w" FILES ${GL3W_HEADER})
SOURCE_GROUP("Header Files\\Depends\\Glut" FILES ${GLUT_HEADER})
SOURCE_GROUP("Header Files\\Depends\\AssImp" FILES ${ASSIMP_HEADER_H} ${ASSIMP_HEADER})
SOURCE_GROUP("Header Files\\File" FILES ${FILE_HEADER})
SOURCE_GROUP("Header Files\\File\\BARTLoader" FILES ${FILE_BART_HEADER})
SOURCE_GROUP("Header Files\\File\\BARTLoader" FILES ${FILE_BART_HEADER})
SOURCE_GROUP("Header Files\\Parser" FILES ${PARSER_HEADER})
SOURCE_GROUP("Header Files\\Parser\\BART" FILES ${PARSER_BART_HEADER})
SOURCE_GROUP("Header Files\\Render" FILES ${RENDER_HEADER})
SOURCE_GROUP("Header Files\\Render\\Passes\\GBuffer" FILES 		${RENDER_GBUFFER_PASS_HEADER})
SOURCE_GROUP("Header Files\\Render\\Passes\\Lightsource" FILES 	${RENDER_LIGHTSOURCE_PASS_HEADER})
SOURCE_GROUP("Header Files\\Render\\Passes\\Bloom" FILES 		${RENDER_BLOOM_PASS_HEADER})
SOURCE_GROUP("Header Files\\Render\\Passes\\SSAO" FILES 		${RENDER_SSAO_PASS_HEADER})
SOURCE_GROUP("Header Files\\Render\\Passes\\Raytrace" FILES 	${RENDER_RAY_PASS_HEADER})
SOURCE_GROUP("Header Files\\Render\\Passes\\Final" FILES 		${RENDER_FINAL_PASS_HEADER})
SOURCE_GROUP("Header Files\\Raytracer" FILES ${RAYTRACER_HEADER})
SOURCE_GROUP("Header Files\\Scene" FILES ${SCENE_HEADER})

SOURCE_GROUP("Source Files\\Depends\\Gl3w" FILES ${GL3W_SOURCE})
SOURCE_GROUP("Source Files\\Depends\\Glut" FILES ${GLUT_SOURCE})
SOURCE_GROUP("Source Files\\Depends\\AssImp" FILES ${ASSIMP_SOURCE_C} ${ASSIMP_SOURCE})
SOURCE_GROUP("Source Files\\File" FILES ${FILE_SOURCE})
SOURCE_GROUP("Source Files\\File\\BARTLoader" FILES ${FILE_BART_SOURCE})
SOURCE_GROUP("Source Files\\Parser" FILES ${PARSER_SOURCE})
SOURCE_GROUP("Source Files\\Parser\\BART" FILES ${PARSER_BART_SOURCE})
SOURCE_GROUP("Source Files\\Render" FILES ${RENDER_SOURCE})
SOURCE_GROUP("Source Files\\Render\\Passes\\GBuffer" FILES 		${RENDER_GBUFFER_PASS_SOURCE})
SOURCE_GROUP("Source Files\\Render\\Passes\\Lightsource" FILES 	${RENDER_LIGHTSOURCE_PASS_SOURCE})
SOURCE_GROUP("Source Files\\Render\\Passes\\Bloom" FILES 		${RENDER_BLOOM_PASS_SOURCE})
SOURCE_GROUP("Source Files\\Render\\Passes\\SSAO"  FILES 		${RENDER_SSAO_PASS_SOURCE})
SOURCE_GROUP("Source Files\\Render\\Passes\\Raytrace" FILES 	${RENDER_RAY_PASS_SOURCE})
SOURCE_GROUP("Source Files\\Render\\Passes\\Final" FILES 		${RENDER_FINAL_PASS_SOURCE})
SOURCE_GROUP("Source Files\\Raytracer" FILES ${RAYTRACER_SOURCE})
SOURCE_GROUP("Source Files\\Scene" FILES ${SCENE_SOURCE})

set(RESOURCES
	${OPTIX_SCRIPTS}
	${GLSL_SHADERS}
	${INI_CONFIGS}
	${MATERIAL_CONFIGS}
)

set(HDRS
	${GL3W_HEADER}
	${GLUT_HEADER}
	${ASSIMP_HEADER_H} 
	${ASSIMP_HEADER}
	${FILE_HEADER}
	${FILE_BART_HEADER}
	${PARSER_HEADER}
	${PARSER_BART_HEADER}
	${RENDER_HEADER}
	${RENDER_GBUFFER_PASS_HEADER}
	${RENDER_LIGHTSOURCE_PASS_HEADER}
	${RENDER_BLOOM_PASS_HEADER}
	${RENDER_SSAO_PASS_HEADER}
	${RENDER_RAY_PASS_HEADER}
	${RENDER_FINAL_PASS_HEADER}
	${RAYTRACER_HEADER}
	${ROOT_HEADER}
	${SCENE_HEADER}
)

set(SRCS
	${GL3W_SOURCE}
	${GLUT_SOURCE}
	${ASSIMP_SOURCE_C} 
	${ASSIMP_SOURCE}
	${FILE_SOURCE}
	${FILE_BART_SOURCE}
	${PARSER_SOURCE}
	${PARSER_BART_SOURCE}
	${RENDER_SOURCE}
	${RENDER_GBUFFER_PASS_SOURCE}
	${RENDER_LIGHTSOURCE_PASS_SOURCE}
	${RENDER_BLOOM_PASS_SOURCE}
	${RENDER_SSAO_PASS_SOURCE}
	${RENDER_RAY_PASS_SOURCE}
	${RENDER_FINAL_PASS_SOURCE}
	${RAYTRACER_SOURCE}
	${SCENE_SOURCE}
	${ROOT_SOURCE}
)

add_executable(${NAME} ${RESOURCES} ${HDRS} ${SRCS})

find_package(OpenGL REQUIRED)
find_package(CUDA REQUIRED)
find_package(Optix REQUIRED)
find_package(DevIL REQUIRED)

ADD_DEFINITIONS(-DFREEGLUT_STATIC -DASSIMP_BUILD_BOOST_WORKAROUND -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -DASSIMP_BUILD_NO_IFC_IMPORTER)

target_link_libraries(${NAME}
	OpenGL32
	${CUDA_LIB}
	${OPTIX_LIB}
	${OPTIXU_LIB}
	${IL_LIBRARY}
	${ILU_LIBRARY}
	${ILUT_LIBRARY}
)

IF(MSVC)
	TARGET_LINK_LIBRARIES(${NAME} WinMM)
ENDIF()

include( ${CMAKE_MODULE_PATH}/compile2ptx.cmake )
COMPILE_CU2PTX( ${OPTIX_SCRIPTS})

