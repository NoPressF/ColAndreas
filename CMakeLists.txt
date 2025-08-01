cmake_minimum_required(VERSION 3.5)
project(ColAndreas)

set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CA_VERSION "v1.5.0")
set(CA_DATABASE_VERSION 2)
add_definitions(-DCA_VERSION="${CA_VERSION}" -DCA_DATABASE_VERSION=${CA_DATABASE_VERSION})

add_subdirectory(omp-sdk)
add_subdirectory(omp-gdk)

add_definitions(-DBT_NO_SIMD_OPERATOR_OVERLOADS)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
	${OMP_GDK_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/bullet3-2.87/src
    ${CMAKE_CURRENT_SOURCE_DIR}/pawn/source
    ${CMAKE_CURRENT_SOURCE_DIR}/pawn/source/linux
)

add_definitions(
    -DHAVE_STDINT_H=1
    -DPAWN_CELL_SIZE=32
)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING " " FORCE)
endif()

option(BuildWizard "Compile the Wizard application." OFF)

if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /nologo /EHsc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /nologo /EHsc /W3")
    
    set(CMAKE_C_FLAGS_RELEASE "/MD /O2 /Ob2 /DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /DNDEBUG")
    
    set(CMAKE_C_FLAGS_DEBUG "/MDd /Zi /Od /RTC1")
    set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Od /RTC1")
    
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MD /Zi /O2 /Ob1")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /O2 /Ob1")
    
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NOLOGO /MACHINE:X86")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/DEBUG")
    
    add_definitions(-DWIN32 -D_WIN32)
else()
    add_definitions(-DLINUX)
    
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -fPIC -std=c++11 -Wno-write-strings")
    
    set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
    
    set(CMAKE_C_FLAGS_RELEASE "-O3 -g0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g0")
    
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g3")
    
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32 -fshort-wchar -shared")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-O3 -s")
endif()

file(GLOB SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "ColAndreas"
)
target_link_libraries(${PROJECT_NAME}
	PRIVATE
    OMP-SDK
	omp-gdk
    "${CMAKE_CURRENT_SOURCE_DIR}/bullet3-2.87/build3/lib/Release/BulletCollision.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/bullet3-2.87/build3/lib/Release/BulletDynamics.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/bullet3-2.87/build3/lib/Release/LinearMath.lib"
)

if(NOT WIN32 AND "${BULLET_COLLISION_LIBRARY}" MATCHES ".a$")
	set_target_properties(ColAndreas PROPERTIES SUFFIX "_static.so")
endif()

if(BuildWizard)
	add_subdirectory(WizardApp)
endif()