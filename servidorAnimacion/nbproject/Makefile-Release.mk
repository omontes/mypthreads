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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/MyPthread/ContextManage.o \
	${OBJECTDIR}/MyPthread/Dispatcher.o \
	${OBJECTDIR}/MyPthread/Mutex.o \
	${OBJECTDIR}/MyPthread/MyMutex.o \
	${OBJECTDIR}/MyPthread/MyPthread.o \
	${OBJECTDIR}/MyPthread/Queue.o \
	${OBJECTDIR}/MyPthread/RoundRobin.o \
	${OBJECTDIR}/MyPthread/TCB.o \
	${OBJECTDIR}/MyPthread/TCB_Queue.o \
	${OBJECTDIR}/MyPthread/TCB_list.o \
	${OBJECTDIR}/MyPthread/Timer.o \
	${OBJECTDIR}/figura.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/tserver.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servidoranimacion

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servidoranimacion: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servidoranimacion ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/MyPthread/ContextManage.o: MyPthread/ContextManage.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/ContextManage.o MyPthread/ContextManage.c

${OBJECTDIR}/MyPthread/Dispatcher.o: MyPthread/Dispatcher.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/Dispatcher.o MyPthread/Dispatcher.c

${OBJECTDIR}/MyPthread/Mutex.o: MyPthread/Mutex.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/Mutex.o MyPthread/Mutex.c

${OBJECTDIR}/MyPthread/MyMutex.o: MyPthread/MyMutex.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/MyMutex.o MyPthread/MyMutex.c

${OBJECTDIR}/MyPthread/MyPthread.o: MyPthread/MyPthread.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/MyPthread.o MyPthread/MyPthread.c

${OBJECTDIR}/MyPthread/Queue.o: MyPthread/Queue.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/Queue.o MyPthread/Queue.c

${OBJECTDIR}/MyPthread/RoundRobin.o: MyPthread/RoundRobin.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/RoundRobin.o MyPthread/RoundRobin.c

${OBJECTDIR}/MyPthread/TCB.o: MyPthread/TCB.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/TCB.o MyPthread/TCB.c

${OBJECTDIR}/MyPthread/TCB_Queue.o: MyPthread/TCB_Queue.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/TCB_Queue.o MyPthread/TCB_Queue.c

${OBJECTDIR}/MyPthread/TCB_list.o: MyPthread/TCB_list.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/TCB_list.o MyPthread/TCB_list.c

${OBJECTDIR}/MyPthread/Timer.o: MyPthread/Timer.c 
	${MKDIR} -p ${OBJECTDIR}/MyPthread
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyPthread/Timer.o MyPthread/Timer.c

${OBJECTDIR}/figura.o: figura.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/figura.o figura.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/tserver.o: tserver.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tserver.o tserver.c

${OBJECTDIR}/tserver.h.gch: tserver.h 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o "$@" tserver.h

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servidoranimacion

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
