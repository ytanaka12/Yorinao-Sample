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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/source/Interpolations.o \
	${OBJECTDIR}/source/LowLevelControl.o \
	${OBJECTDIR}/source/Serial_CSV_Format.o \
	${OBJECTDIR}/source/ServoBlaster.o \
	${OBJECTDIR}/source/TimeCount.o \
	${OBJECTDIR}/source/TimeKeeper.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lwiringPi
CXXFLAGS=-lwiringPi

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yorinao_sample

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yorinao_sample: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yorinao_sample ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/source/Interpolations.o: source/Interpolations.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/Interpolations.o source/Interpolations.cpp

${OBJECTDIR}/source/LowLevelControl.o: source/LowLevelControl.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/LowLevelControl.o source/LowLevelControl.cpp

${OBJECTDIR}/source/Serial_CSV_Format.o: source/Serial_CSV_Format.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/Serial_CSV_Format.o source/Serial_CSV_Format.cpp

${OBJECTDIR}/source/ServoBlaster.o: source/ServoBlaster.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/ServoBlaster.o source/ServoBlaster.cpp

${OBJECTDIR}/source/TimeCount.o: source/TimeCount.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/TimeCount.o source/TimeCount.cpp

${OBJECTDIR}/source/TimeKeeper.o: source/TimeKeeper.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/TimeKeeper.o source/TimeKeeper.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
