################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CCon3270.cpp \
../src/CConsGrab.cpp \
../src/CMenu.cpp \
../src/CMysql.cpp \
../src/CTemporizador.cpp \
../src/CTxtCrptDecript.cpp \
../src/Csessao.cpp \
../src/osmcs_scb1.cpp 

OBJS += \
./src/CCon3270.o \
./src/CConsGrab.o \
./src/CMenu.o \
./src/CMysql.o \
./src/CTemporizador.o \
./src/CTxtCrptDecript.o \
./src/Csessao.o \
./src/osmcs_scb1.o 

CPP_DEPS += \
./src/CCon3270.d \
./src/CConsGrab.d \
./src/CMenu.d \
./src/CMysql.d \
./src/CTemporizador.d \
./src/CTxtCrptDecript.d \
./src/Csessao.d \
./src/osmcs_scb1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/tcl8.6 -I/usr/include/tk -I/usr/include/mariadb -I/usr/include/mysql -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


