F405_TARGETS    += $(TARGET)
FEATURES        += VCP CHIBIOS ONBOARDFLASH

HSE_VALUE       = 8000000

TARGET_SRC =  \
              drivers/accgyro_spi_bmi160.c \
