#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/animation/gameanimation.o \
	${OBJECTDIR}/src/biome/foresttilevisualizer.o \
	${OBJECTDIR}/src/biome/tilevisualizer.o \
	${OBJECTDIR}/src/camera/camera.o \
	${OBJECTDIR}/src/engine/engine.o \
	${OBJECTDIR}/src/frame/objectframe.o \
	${OBJECTDIR}/src/frame/objectframegenerator.o \
	${OBJECTDIR}/src/frame/objectframelibrary.o \
	${OBJECTDIR}/src/frame/objectframelist.o \
	${OBJECTDIR}/src/geometry/intersectiontester.o \
	${OBJECTDIR}/src/geometry/polygonbuilder.o \
	${OBJECTDIR}/src/geometry/transformations.o \
	${OBJECTDIR}/src/glyph/glyphrenderinfo.o \
	${OBJECTDIR}/src/glyph/glyphset.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/main/mainwindow.o \
	${OBJECTDIR}/src/map/map.o \
	${OBJECTDIR}/src/map/mapgenerator.o \
	${OBJECTDIR}/src/painter/worldpainter.o \
	${OBJECTDIR}/src/physics/collisionhull.o \
	${OBJECTDIR}/src/physicsengine/physicsengine.o \
	${OBJECTDIR}/src/pixel/pixelutil.o \
	${OBJECTDIR}/src/player/player.o \
	${OBJECTDIR}/src/player/playeranimation.o \
	${OBJECTDIR}/src/renderer/glyphrenderer.o \
	${OBJECTDIR}/src/renderer/tilerenderer.o \
	${OBJECTDIR}/src/resource/mainresources.o \
	${OBJECTDIR}/src/ruukku/config/packing.o \
	${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist.o \
	${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer.o \
	${OBJECTDIR}/src/ruukku/mesh/interleavebuffer.o \
	${OBJECTDIR}/src/ruukku/mesh/primitivelist.o \
	${OBJECTDIR}/src/ruukku/mesh/shaderprogram.o \
	${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo.o \
	${OBJECTDIR}/src/ruukku/mesh/vertexbuffer.o \
	${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo.o \
	${OBJECTDIR}/src/ruukku/opengl/glbuffer.o \
	${OBJECTDIR}/src/ruukku/opengl/glerror.o \
	${OBJECTDIR}/src/ruukku/opengl/glprogram.o \
	${OBJECTDIR}/src/ruukku/opengl/glshader.o \
	${OBJECTDIR}/src/ruukku/opengl/gltexture.o \
	${OBJECTDIR}/src/ruukku/opengl/gltexture2d.o \
	${OBJECTDIR}/src/ruukku/opengl/gltexture3d.o \
	${OBJECTDIR}/src/ruukku/opengl/glvertexarray.o \
	${OBJECTDIR}/src/ruukku/pixel/surface.o \
	${OBJECTDIR}/src/ruukku/system/keyboardstate.o \
	${OBJECTDIR}/src/ruukku/system/sdl.o \
	${OBJECTDIR}/src/ruukku/system/window.o \
	${OBJECTDIR}/src/ruukku/system/windowmanager.o \
	${OBJECTDIR}/src/shader/glyphshader.o \
	${OBJECTDIR}/src/shader/tileshader.o \
	${OBJECTDIR}/src/tile/tile.o \
	${OBJECTDIR}/src/tile/tilephysics.o \
	${OBJECTDIR}/src/time/worldtime.o \
	${OBJECTDIR}/src/util/datafile.o \
	${OBJECTDIR}/src/world/world.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f3

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../MinGW/msys/1.0/lib -lmingw32 -lSDL2main -lglew32.dll -lopengl32 -lSDL2.dll -lpng12.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/runrun.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/runrun.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/runrun ${OBJECTFILES} ${LDLIBSOPTIONS} -mwindows

${OBJECTDIR}/src/animation/gameanimation.o: src/animation/gameanimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/animation
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/animation/gameanimation.o src/animation/gameanimation.cpp

${OBJECTDIR}/src/biome/foresttilevisualizer.o: src/biome/foresttilevisualizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/biome
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/biome/foresttilevisualizer.o src/biome/foresttilevisualizer.cpp

${OBJECTDIR}/src/biome/tilevisualizer.o: src/biome/tilevisualizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/biome
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/biome/tilevisualizer.o src/biome/tilevisualizer.cpp

${OBJECTDIR}/src/camera/camera.o: src/camera/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/camera
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/camera/camera.o src/camera/camera.cpp

${OBJECTDIR}/src/engine/engine.o: src/engine/engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/engine
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/engine/engine.o src/engine/engine.cpp

${OBJECTDIR}/src/frame/objectframe.o: src/frame/objectframe.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/frame
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame/objectframe.o src/frame/objectframe.cpp

${OBJECTDIR}/src/frame/objectframegenerator.o: src/frame/objectframegenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/frame
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame/objectframegenerator.o src/frame/objectframegenerator.cpp

${OBJECTDIR}/src/frame/objectframelibrary.o: src/frame/objectframelibrary.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/frame
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame/objectframelibrary.o src/frame/objectframelibrary.cpp

${OBJECTDIR}/src/frame/objectframelist.o: src/frame/objectframelist.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/frame
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame/objectframelist.o src/frame/objectframelist.cpp

${OBJECTDIR}/src/geometry/intersectiontester.o: src/geometry/intersectiontester.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/geometry
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/geometry/intersectiontester.o src/geometry/intersectiontester.cpp

${OBJECTDIR}/src/geometry/polygonbuilder.o: src/geometry/polygonbuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/geometry
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/geometry/polygonbuilder.o src/geometry/polygonbuilder.cpp

${OBJECTDIR}/src/geometry/transformations.o: src/geometry/transformations.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/geometry
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/geometry/transformations.o src/geometry/transformations.cpp

${OBJECTDIR}/src/glyph/glyphrenderinfo.o: src/glyph/glyphrenderinfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/glyph
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/glyph/glyphrenderinfo.o src/glyph/glyphrenderinfo.cpp

${OBJECTDIR}/src/glyph/glyphset.o: src/glyph/glyphset.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/glyph
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/glyph/glyphset.o src/glyph/glyphset.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/main/mainwindow.o: src/main/mainwindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main/mainwindow.o src/main/mainwindow.cpp

${OBJECTDIR}/src/map/map.o: src/map/map.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/map
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/map/map.o src/map/map.cpp

${OBJECTDIR}/src/map/mapgenerator.o: src/map/mapgenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/map
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/map/mapgenerator.o src/map/mapgenerator.cpp

${OBJECTDIR}/src/painter/worldpainter.o: src/painter/worldpainter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/painter
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/painter/worldpainter.o src/painter/worldpainter.cpp

${OBJECTDIR}/src/physics/collisionhull.o: src/physics/collisionhull.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/physics
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/physics/collisionhull.o src/physics/collisionhull.cpp

${OBJECTDIR}/src/physicsengine/physicsengine.o: src/physicsengine/physicsengine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/physicsengine
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/physicsengine/physicsengine.o src/physicsengine/physicsengine.cpp

${OBJECTDIR}/src/pixel/pixelutil.o: src/pixel/pixelutil.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/pixel
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/pixel/pixelutil.o src/pixel/pixelutil.cpp

${OBJECTDIR}/src/player/player.o: src/player/player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/player
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/player/player.o src/player/player.cpp

${OBJECTDIR}/src/player/playeranimation.o: src/player/playeranimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/player
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/player/playeranimation.o src/player/playeranimation.cpp

${OBJECTDIR}/src/renderer/glyphrenderer.o: src/renderer/glyphrenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/glyphrenderer.o src/renderer/glyphrenderer.cpp

${OBJECTDIR}/src/renderer/tilerenderer.o: src/renderer/tilerenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/tilerenderer.o src/renderer/tilerenderer.cpp

${OBJECTDIR}/src/resource/mainresources.o: src/resource/mainresources.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/resource
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/resource/mainresources.o src/resource/mainresources.cpp

${OBJECTDIR}/src/ruukku/config/packing.o: src/ruukku/config/packing.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/config
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/config/packing.o src/ruukku/config/packing.cpp

${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist.o: src/ruukku/mesh/indexedprimitivelist.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist.o src/ruukku/mesh/indexedprimitivelist.cpp

${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer.o: src/ruukku/mesh/indexedvertexbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer.o src/ruukku/mesh/indexedvertexbuffer.cpp

${OBJECTDIR}/src/ruukku/mesh/interleavebuffer.o: src/ruukku/mesh/interleavebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/interleavebuffer.o src/ruukku/mesh/interleavebuffer.cpp

${OBJECTDIR}/src/ruukku/mesh/primitivelist.o: src/ruukku/mesh/primitivelist.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/primitivelist.o src/ruukku/mesh/primitivelist.cpp

${OBJECTDIR}/src/ruukku/mesh/shaderprogram.o: src/ruukku/mesh/shaderprogram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/shaderprogram.o src/ruukku/mesh/shaderprogram.cpp

${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo.o: src/ruukku/mesh/vertexarrayinfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo.o src/ruukku/mesh/vertexarrayinfo.cpp

${OBJECTDIR}/src/ruukku/mesh/vertexbuffer.o: src/ruukku/mesh/vertexbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/vertexbuffer.o src/ruukku/mesh/vertexbuffer.cpp

${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo.o: src/ruukku/mesh/vertexbufferinfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo.o src/ruukku/mesh/vertexbufferinfo.cpp

${OBJECTDIR}/src/ruukku/opengl/glbuffer.o: src/ruukku/opengl/glbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glbuffer.o src/ruukku/opengl/glbuffer.cpp

${OBJECTDIR}/src/ruukku/opengl/glerror.o: src/ruukku/opengl/glerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glerror.o src/ruukku/opengl/glerror.cpp

${OBJECTDIR}/src/ruukku/opengl/glprogram.o: src/ruukku/opengl/glprogram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glprogram.o src/ruukku/opengl/glprogram.cpp

${OBJECTDIR}/src/ruukku/opengl/glshader.o: src/ruukku/opengl/glshader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glshader.o src/ruukku/opengl/glshader.cpp

${OBJECTDIR}/src/ruukku/opengl/gltexture.o: src/ruukku/opengl/gltexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/gltexture.o src/ruukku/opengl/gltexture.cpp

${OBJECTDIR}/src/ruukku/opengl/gltexture2d.o: src/ruukku/opengl/gltexture2d.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/gltexture2d.o src/ruukku/opengl/gltexture2d.cpp

${OBJECTDIR}/src/ruukku/opengl/gltexture3d.o: src/ruukku/opengl/gltexture3d.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/gltexture3d.o src/ruukku/opengl/gltexture3d.cpp

${OBJECTDIR}/src/ruukku/opengl/glvertexarray.o: src/ruukku/opengl/glvertexarray.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glvertexarray.o src/ruukku/opengl/glvertexarray.cpp

${OBJECTDIR}/src/ruukku/pixel/surface.o: src/ruukku/pixel/surface.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/pixel
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/pixel/surface.o src/ruukku/pixel/surface.cpp

${OBJECTDIR}/src/ruukku/system/keyboardstate.o: src/ruukku/system/keyboardstate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/system
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/system/keyboardstate.o src/ruukku/system/keyboardstate.cpp

${OBJECTDIR}/src/ruukku/system/sdl.o: src/ruukku/system/sdl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/system
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/system/sdl.o src/ruukku/system/sdl.cpp

${OBJECTDIR}/src/ruukku/system/window.o: src/ruukku/system/window.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/system
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/system/window.o src/ruukku/system/window.cpp

${OBJECTDIR}/src/ruukku/system/windowmanager.o: src/ruukku/system/windowmanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/system
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/system/windowmanager.o src/ruukku/system/windowmanager.cpp

${OBJECTDIR}/src/shader/glyphshader.o: src/shader/glyphshader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/shader
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/shader/glyphshader.o src/shader/glyphshader.cpp

${OBJECTDIR}/src/shader/tileshader.o: src/shader/tileshader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/shader
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/shader/tileshader.o src/shader/tileshader.cpp

${OBJECTDIR}/src/tile/tile.o: src/tile/tile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tile
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tile/tile.o src/tile/tile.cpp

${OBJECTDIR}/src/tile/tilephysics.o: src/tile/tilephysics.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tile
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tile/tilephysics.o src/tile/tilephysics.cpp

${OBJECTDIR}/src/time/worldtime.o: src/time/worldtime.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/time
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/time/worldtime.o src/time/worldtime.cpp

${OBJECTDIR}/src/util/datafile.o: src/util/datafile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/util
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/util/datafile.o src/util/datafile.cpp

${OBJECTDIR}/src/world/world.o: src/world/world.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/world
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/world/world.o src/world/world.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/geometry_intersectiontester.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/geometry_segment.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/geometry_intersectiontester.o: tests/geometry_intersectiontester.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -I. -I. -I. -I. -std=c++11 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/geometry_intersectiontester.o tests/geometry_intersectiontester.cpp


${TESTDIR}/tests/geometry_segment.o: tests/geometry_segment.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -I. -I. -std=c++11 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/geometry_segment.o tests/geometry_segment.cpp


${OBJECTDIR}/src/animation/gameanimation_nomain.o: ${OBJECTDIR}/src/animation/gameanimation.o src/animation/gameanimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/animation
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/animation/gameanimation.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/animation/gameanimation_nomain.o src/animation/gameanimation.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/animation/gameanimation.o ${OBJECTDIR}/src/animation/gameanimation_nomain.o;\
	fi

${OBJECTDIR}/src/biome/foresttilevisualizer_nomain.o: ${OBJECTDIR}/src/biome/foresttilevisualizer.o src/biome/foresttilevisualizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/biome
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/biome/foresttilevisualizer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/biome/foresttilevisualizer_nomain.o src/biome/foresttilevisualizer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/biome/foresttilevisualizer.o ${OBJECTDIR}/src/biome/foresttilevisualizer_nomain.o;\
	fi

${OBJECTDIR}/src/biome/tilevisualizer_nomain.o: ${OBJECTDIR}/src/biome/tilevisualizer.o src/biome/tilevisualizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/biome
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/biome/tilevisualizer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/biome/tilevisualizer_nomain.o src/biome/tilevisualizer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/biome/tilevisualizer.o ${OBJECTDIR}/src/biome/tilevisualizer_nomain.o;\
	fi

${OBJECTDIR}/src/camera/camera_nomain.o: ${OBJECTDIR}/src/camera/camera.o src/camera/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/camera
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/camera/camera.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/camera/camera_nomain.o src/camera/camera.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/camera/camera.o ${OBJECTDIR}/src/camera/camera_nomain.o;\
	fi

${OBJECTDIR}/src/engine/engine_nomain.o: ${OBJECTDIR}/src/engine/engine.o src/engine/engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/engine
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/engine/engine.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/engine/engine_nomain.o src/engine/engine.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/engine/engine.o ${OBJECTDIR}/src/engine/engine_nomain.o;\
	fi

${OBJECTDIR}/src/frame/objectframe_nomain.o: ${OBJECTDIR}/src/frame/objectframe.o src/frame/objectframe.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/frame
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/frame/objectframe.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame/objectframe_nomain.o src/frame/objectframe.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/frame/objectframe.o ${OBJECTDIR}/src/frame/objectframe_nomain.o;\
	fi

${OBJECTDIR}/src/frame/objectframegenerator_nomain.o: ${OBJECTDIR}/src/frame/objectframegenerator.o src/frame/objectframegenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/frame
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/frame/objectframegenerator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame/objectframegenerator_nomain.o src/frame/objectframegenerator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/frame/objectframegenerator.o ${OBJECTDIR}/src/frame/objectframegenerator_nomain.o;\
	fi

${OBJECTDIR}/src/frame/objectframelibrary_nomain.o: ${OBJECTDIR}/src/frame/objectframelibrary.o src/frame/objectframelibrary.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/frame
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/frame/objectframelibrary.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame/objectframelibrary_nomain.o src/frame/objectframelibrary.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/frame/objectframelibrary.o ${OBJECTDIR}/src/frame/objectframelibrary_nomain.o;\
	fi

${OBJECTDIR}/src/frame/objectframelist_nomain.o: ${OBJECTDIR}/src/frame/objectframelist.o src/frame/objectframelist.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/frame
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/frame/objectframelist.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame/objectframelist_nomain.o src/frame/objectframelist.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/frame/objectframelist.o ${OBJECTDIR}/src/frame/objectframelist_nomain.o;\
	fi

${OBJECTDIR}/src/geometry/intersectiontester_nomain.o: ${OBJECTDIR}/src/geometry/intersectiontester.o src/geometry/intersectiontester.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/geometry
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/geometry/intersectiontester.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/geometry/intersectiontester_nomain.o src/geometry/intersectiontester.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/geometry/intersectiontester.o ${OBJECTDIR}/src/geometry/intersectiontester_nomain.o;\
	fi

${OBJECTDIR}/src/geometry/polygonbuilder_nomain.o: ${OBJECTDIR}/src/geometry/polygonbuilder.o src/geometry/polygonbuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/geometry
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/geometry/polygonbuilder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/geometry/polygonbuilder_nomain.o src/geometry/polygonbuilder.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/geometry/polygonbuilder.o ${OBJECTDIR}/src/geometry/polygonbuilder_nomain.o;\
	fi

${OBJECTDIR}/src/geometry/transformations_nomain.o: ${OBJECTDIR}/src/geometry/transformations.o src/geometry/transformations.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/geometry
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/geometry/transformations.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/geometry/transformations_nomain.o src/geometry/transformations.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/geometry/transformations.o ${OBJECTDIR}/src/geometry/transformations_nomain.o;\
	fi

${OBJECTDIR}/src/glyph/glyphrenderinfo_nomain.o: ${OBJECTDIR}/src/glyph/glyphrenderinfo.o src/glyph/glyphrenderinfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/glyph
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/glyph/glyphrenderinfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/glyph/glyphrenderinfo_nomain.o src/glyph/glyphrenderinfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/glyph/glyphrenderinfo.o ${OBJECTDIR}/src/glyph/glyphrenderinfo_nomain.o;\
	fi

${OBJECTDIR}/src/glyph/glyphset_nomain.o: ${OBJECTDIR}/src/glyph/glyphset.o src/glyph/glyphset.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/glyph
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/glyph/glyphset.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/glyph/glyphset_nomain.o src/glyph/glyphset.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/glyph/glyphset.o ${OBJECTDIR}/src/glyph/glyphset_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

${OBJECTDIR}/src/main/mainwindow_nomain.o: ${OBJECTDIR}/src/main/mainwindow.o src/main/mainwindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/main
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main/mainwindow.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main/mainwindow_nomain.o src/main/mainwindow.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main/mainwindow.o ${OBJECTDIR}/src/main/mainwindow_nomain.o;\
	fi

${OBJECTDIR}/src/map/map_nomain.o: ${OBJECTDIR}/src/map/map.o src/map/map.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/map
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/map/map.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/map/map_nomain.o src/map/map.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/map/map.o ${OBJECTDIR}/src/map/map_nomain.o;\
	fi

${OBJECTDIR}/src/map/mapgenerator_nomain.o: ${OBJECTDIR}/src/map/mapgenerator.o src/map/mapgenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/map
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/map/mapgenerator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/map/mapgenerator_nomain.o src/map/mapgenerator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/map/mapgenerator.o ${OBJECTDIR}/src/map/mapgenerator_nomain.o;\
	fi

${OBJECTDIR}/src/painter/worldpainter_nomain.o: ${OBJECTDIR}/src/painter/worldpainter.o src/painter/worldpainter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/painter
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/painter/worldpainter.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/painter/worldpainter_nomain.o src/painter/worldpainter.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/painter/worldpainter.o ${OBJECTDIR}/src/painter/worldpainter_nomain.o;\
	fi

${OBJECTDIR}/src/physics/collisionhull_nomain.o: ${OBJECTDIR}/src/physics/collisionhull.o src/physics/collisionhull.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/physics
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/physics/collisionhull.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/physics/collisionhull_nomain.o src/physics/collisionhull.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/physics/collisionhull.o ${OBJECTDIR}/src/physics/collisionhull_nomain.o;\
	fi

${OBJECTDIR}/src/physicsengine/physicsengine_nomain.o: ${OBJECTDIR}/src/physicsengine/physicsengine.o src/physicsengine/physicsengine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/physicsengine
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/physicsengine/physicsengine.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/physicsengine/physicsengine_nomain.o src/physicsengine/physicsengine.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/physicsengine/physicsengine.o ${OBJECTDIR}/src/physicsengine/physicsengine_nomain.o;\
	fi

${OBJECTDIR}/src/pixel/pixelutil_nomain.o: ${OBJECTDIR}/src/pixel/pixelutil.o src/pixel/pixelutil.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/pixel
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pixel/pixelutil.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/pixel/pixelutil_nomain.o src/pixel/pixelutil.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pixel/pixelutil.o ${OBJECTDIR}/src/pixel/pixelutil_nomain.o;\
	fi

${OBJECTDIR}/src/player/player_nomain.o: ${OBJECTDIR}/src/player/player.o src/player/player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/player
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/player/player.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/player/player_nomain.o src/player/player.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/player/player.o ${OBJECTDIR}/src/player/player_nomain.o;\
	fi

${OBJECTDIR}/src/player/playeranimation_nomain.o: ${OBJECTDIR}/src/player/playeranimation.o src/player/playeranimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/player
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/player/playeranimation.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/player/playeranimation_nomain.o src/player/playeranimation.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/player/playeranimation.o ${OBJECTDIR}/src/player/playeranimation_nomain.o;\
	fi

${OBJECTDIR}/src/renderer/glyphrenderer_nomain.o: ${OBJECTDIR}/src/renderer/glyphrenderer.o src/renderer/glyphrenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/renderer/glyphrenderer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/glyphrenderer_nomain.o src/renderer/glyphrenderer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/renderer/glyphrenderer.o ${OBJECTDIR}/src/renderer/glyphrenderer_nomain.o;\
	fi

${OBJECTDIR}/src/renderer/tilerenderer_nomain.o: ${OBJECTDIR}/src/renderer/tilerenderer.o src/renderer/tilerenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/renderer/tilerenderer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/tilerenderer_nomain.o src/renderer/tilerenderer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/renderer/tilerenderer.o ${OBJECTDIR}/src/renderer/tilerenderer_nomain.o;\
	fi

${OBJECTDIR}/src/resource/mainresources_nomain.o: ${OBJECTDIR}/src/resource/mainresources.o src/resource/mainresources.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/resource
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/resource/mainresources.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/resource/mainresources_nomain.o src/resource/mainresources.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/resource/mainresources.o ${OBJECTDIR}/src/resource/mainresources_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/config/packing_nomain.o: ${OBJECTDIR}/src/ruukku/config/packing.o src/ruukku/config/packing.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/config
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/config/packing.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/config/packing_nomain.o src/ruukku/config/packing.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/config/packing.o ${OBJECTDIR}/src/ruukku/config/packing_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist_nomain.o: ${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist.o src/ruukku/mesh/indexedprimitivelist.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist_nomain.o src/ruukku/mesh/indexedprimitivelist.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist.o ${OBJECTDIR}/src/ruukku/mesh/indexedprimitivelist_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer_nomain.o: ${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer.o src/ruukku/mesh/indexedvertexbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer_nomain.o src/ruukku/mesh/indexedvertexbuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer.o ${OBJECTDIR}/src/ruukku/mesh/indexedvertexbuffer_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/mesh/interleavebuffer_nomain.o: ${OBJECTDIR}/src/ruukku/mesh/interleavebuffer.o src/ruukku/mesh/interleavebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/mesh/interleavebuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/interleavebuffer_nomain.o src/ruukku/mesh/interleavebuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/mesh/interleavebuffer.o ${OBJECTDIR}/src/ruukku/mesh/interleavebuffer_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/mesh/primitivelist_nomain.o: ${OBJECTDIR}/src/ruukku/mesh/primitivelist.o src/ruukku/mesh/primitivelist.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/mesh/primitivelist.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/primitivelist_nomain.o src/ruukku/mesh/primitivelist.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/mesh/primitivelist.o ${OBJECTDIR}/src/ruukku/mesh/primitivelist_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/mesh/shaderprogram_nomain.o: ${OBJECTDIR}/src/ruukku/mesh/shaderprogram.o src/ruukku/mesh/shaderprogram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/mesh/shaderprogram.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/shaderprogram_nomain.o src/ruukku/mesh/shaderprogram.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/mesh/shaderprogram.o ${OBJECTDIR}/src/ruukku/mesh/shaderprogram_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo_nomain.o: ${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo.o src/ruukku/mesh/vertexarrayinfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo_nomain.o src/ruukku/mesh/vertexarrayinfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo.o ${OBJECTDIR}/src/ruukku/mesh/vertexarrayinfo_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/mesh/vertexbuffer_nomain.o: ${OBJECTDIR}/src/ruukku/mesh/vertexbuffer.o src/ruukku/mesh/vertexbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/mesh/vertexbuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/vertexbuffer_nomain.o src/ruukku/mesh/vertexbuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/mesh/vertexbuffer.o ${OBJECTDIR}/src/ruukku/mesh/vertexbuffer_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo_nomain.o: ${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo.o src/ruukku/mesh/vertexbufferinfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/mesh
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo_nomain.o src/ruukku/mesh/vertexbufferinfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo.o ${OBJECTDIR}/src/ruukku/mesh/vertexbufferinfo_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/opengl/glbuffer_nomain.o: ${OBJECTDIR}/src/ruukku/opengl/glbuffer.o src/ruukku/opengl/glbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/opengl/glbuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glbuffer_nomain.o src/ruukku/opengl/glbuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/opengl/glbuffer.o ${OBJECTDIR}/src/ruukku/opengl/glbuffer_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/opengl/glerror_nomain.o: ${OBJECTDIR}/src/ruukku/opengl/glerror.o src/ruukku/opengl/glerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/opengl/glerror.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glerror_nomain.o src/ruukku/opengl/glerror.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/opengl/glerror.o ${OBJECTDIR}/src/ruukku/opengl/glerror_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/opengl/glprogram_nomain.o: ${OBJECTDIR}/src/ruukku/opengl/glprogram.o src/ruukku/opengl/glprogram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/opengl/glprogram.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glprogram_nomain.o src/ruukku/opengl/glprogram.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/opengl/glprogram.o ${OBJECTDIR}/src/ruukku/opengl/glprogram_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/opengl/glshader_nomain.o: ${OBJECTDIR}/src/ruukku/opengl/glshader.o src/ruukku/opengl/glshader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/opengl/glshader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glshader_nomain.o src/ruukku/opengl/glshader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/opengl/glshader.o ${OBJECTDIR}/src/ruukku/opengl/glshader_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/opengl/gltexture_nomain.o: ${OBJECTDIR}/src/ruukku/opengl/gltexture.o src/ruukku/opengl/gltexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/opengl/gltexture.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/gltexture_nomain.o src/ruukku/opengl/gltexture.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/opengl/gltexture.o ${OBJECTDIR}/src/ruukku/opengl/gltexture_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/opengl/gltexture2d_nomain.o: ${OBJECTDIR}/src/ruukku/opengl/gltexture2d.o src/ruukku/opengl/gltexture2d.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/opengl/gltexture2d.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/gltexture2d_nomain.o src/ruukku/opengl/gltexture2d.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/opengl/gltexture2d.o ${OBJECTDIR}/src/ruukku/opengl/gltexture2d_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/opengl/gltexture3d_nomain.o: ${OBJECTDIR}/src/ruukku/opengl/gltexture3d.o src/ruukku/opengl/gltexture3d.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/opengl/gltexture3d.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/gltexture3d_nomain.o src/ruukku/opengl/gltexture3d.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/opengl/gltexture3d.o ${OBJECTDIR}/src/ruukku/opengl/gltexture3d_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/opengl/glvertexarray_nomain.o: ${OBJECTDIR}/src/ruukku/opengl/glvertexarray.o src/ruukku/opengl/glvertexarray.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/opengl
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/opengl/glvertexarray.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/opengl/glvertexarray_nomain.o src/ruukku/opengl/glvertexarray.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/opengl/glvertexarray.o ${OBJECTDIR}/src/ruukku/opengl/glvertexarray_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/pixel/surface_nomain.o: ${OBJECTDIR}/src/ruukku/pixel/surface.o src/ruukku/pixel/surface.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/pixel
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/pixel/surface.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/pixel/surface_nomain.o src/ruukku/pixel/surface.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/pixel/surface.o ${OBJECTDIR}/src/ruukku/pixel/surface_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/system/keyboardstate_nomain.o: ${OBJECTDIR}/src/ruukku/system/keyboardstate.o src/ruukku/system/keyboardstate.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/system/keyboardstate.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/system/keyboardstate_nomain.o src/ruukku/system/keyboardstate.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/system/keyboardstate.o ${OBJECTDIR}/src/ruukku/system/keyboardstate_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/system/sdl_nomain.o: ${OBJECTDIR}/src/ruukku/system/sdl.o src/ruukku/system/sdl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/system/sdl.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/system/sdl_nomain.o src/ruukku/system/sdl.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/system/sdl.o ${OBJECTDIR}/src/ruukku/system/sdl_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/system/window_nomain.o: ${OBJECTDIR}/src/ruukku/system/window.o src/ruukku/system/window.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/system/window.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/system/window_nomain.o src/ruukku/system/window.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/system/window.o ${OBJECTDIR}/src/ruukku/system/window_nomain.o;\
	fi

${OBJECTDIR}/src/ruukku/system/windowmanager_nomain.o: ${OBJECTDIR}/src/ruukku/system/windowmanager.o src/ruukku/system/windowmanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ruukku/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ruukku/system/windowmanager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ruukku/system/windowmanager_nomain.o src/ruukku/system/windowmanager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ruukku/system/windowmanager.o ${OBJECTDIR}/src/ruukku/system/windowmanager_nomain.o;\
	fi

${OBJECTDIR}/src/shader/glyphshader_nomain.o: ${OBJECTDIR}/src/shader/glyphshader.o src/shader/glyphshader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/shader
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/shader/glyphshader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/shader/glyphshader_nomain.o src/shader/glyphshader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/shader/glyphshader.o ${OBJECTDIR}/src/shader/glyphshader_nomain.o;\
	fi

${OBJECTDIR}/src/shader/tileshader_nomain.o: ${OBJECTDIR}/src/shader/tileshader.o src/shader/tileshader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/shader
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/shader/tileshader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/shader/tileshader_nomain.o src/shader/tileshader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/shader/tileshader.o ${OBJECTDIR}/src/shader/tileshader_nomain.o;\
	fi

${OBJECTDIR}/src/tile/tile_nomain.o: ${OBJECTDIR}/src/tile/tile.o src/tile/tile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tile
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/tile/tile.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tile/tile_nomain.o src/tile/tile.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/tile/tile.o ${OBJECTDIR}/src/tile/tile_nomain.o;\
	fi

${OBJECTDIR}/src/tile/tilephysics_nomain.o: ${OBJECTDIR}/src/tile/tilephysics.o src/tile/tilephysics.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tile
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/tile/tilephysics.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tile/tilephysics_nomain.o src/tile/tilephysics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/tile/tilephysics.o ${OBJECTDIR}/src/tile/tilephysics_nomain.o;\
	fi

${OBJECTDIR}/src/time/worldtime_nomain.o: ${OBJECTDIR}/src/time/worldtime.o src/time/worldtime.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/time
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/time/worldtime.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/time/worldtime_nomain.o src/time/worldtime.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/time/worldtime.o ${OBJECTDIR}/src/time/worldtime_nomain.o;\
	fi

${OBJECTDIR}/src/util/datafile_nomain.o: ${OBJECTDIR}/src/util/datafile.o src/util/datafile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/util
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/util/datafile.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/util/datafile_nomain.o src/util/datafile.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/util/datafile.o ${OBJECTDIR}/src/util/datafile_nomain.o;\
	fi

${OBJECTDIR}/src/world/world_nomain.o: ${OBJECTDIR}/src/world/world.o src/world/world.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/world
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/world/world.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I../../MinGW/msys/1.0/include -Isrc -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/world/world_nomain.o src/world/world.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/world/world.o ${OBJECTDIR}/src/world/world_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/runrun.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
