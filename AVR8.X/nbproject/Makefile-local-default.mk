#
# Generated Makefile - do not edit!
#
#
# This file contains information about the location of compilers and other tools.
# If you commmit this file into your revision control server, you will be able to 
# to checkout the project and build it from the command line with make. However,
# if more than one person works on the same project, then this file might show
# conflicts since different users are bound to have compilers in different places.
# In that case you might choose to not commit this file and let MPLAB X recreate this file
# for each user. The disadvantage of not commiting this file is that you must run MPLAB X at
# least once so the file gets created and the project can be built. Finally, you can also
# avoid using this file at all if you are only building from the command line with make.
# You can invoke make with the values of the macros:
# $ makeMP_CC="/opt/microchip/mplabc30/v3.30c/bin/pic30-gcc" ...  
#
PATH_TO_IDE_BIN=/Applications/microchip/mplabx/v6.05/MPLAB X IDE v6.05.app/Contents/Resources/mplab_ide/platform/../mplab_ide/modules/../../bin/
# Adding MPLAB X bin directory to path.
PATH:=/Applications/microchip/mplabx/v6.05/MPLAB X IDE v6.05.app/Contents/Resources/mplab_ide/platform/../mplab_ide/modules/../../bin/:$(PATH)
# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH="/Applications/microchip/mplabx/v6.05/sys/java/zulu8.64.0.19-ca-fx-jre8.0.345-macosx_aarch64/zulu-8.jre/Contents/Home/bin/"
OS_CURRENT="$(shell uname -s)"
MP_CC="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin/avr-gcc"
MP_CPPC="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin/avr-g++"
# MP_BC is not defined
MP_AS="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin/avr-as"
MP_LD="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin/avr-ld"
MP_AR="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin/avr-gcc-ar"
DEP_GEN=${MP_JAVA_PATH}java -jar "/Applications/microchip/mplabx/v6.05/MPLAB X IDE v6.05.app/Contents/Resources/mplab_ide/platform/../mplab_ide/modules/../../bin/extractobjectdependencies.jar"
MP_CC_DIR="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin"
MP_CPPC_DIR="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin"
# MP_BC_DIR is not defined
MP_AS_DIR="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin"
MP_LD_DIR="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin"
MP_AR_DIR="/Users/nuntipat/Downloads/avr8-gnu-toolchain-darwin_x86_64/bin"
DFP_DIR=/Applications/microchip/mplabx/v6.05/packs/Microchip/ATtiny_DFP/3.0.151
