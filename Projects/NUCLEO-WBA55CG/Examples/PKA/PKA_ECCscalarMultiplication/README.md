## <b>PKA_ECCscalarMultiplication Example Description</b>

How to use the PKA peripheral to execute ECC scalar multiplication. This 
allows generating a public key from a private key.

For this example, a .pem file has been created using openssl external tool. (https://www.openssl.org)
This file is located under Src/ecdsa_priv_prime256v1.pem.

To ease the usage of this .pem files, 2 files, Src/ecdsa_priv_prime256v1.c and Inc/ecdsa_priv_prime256v1.h 
are present to reflect its content. The explanation of how to create those file from a .pem is embedded in 
Src/ecdsa_priv_prime256v1.c.

The selected curve for this example is P-256 (ECDSA-256) published by NIST in 
Federal Information Processing Standards Publication FIPS PUB 186-4. The description
of this curve is present in file Src/prime256v1.c. 

Those two information are provided to PKA using the PKA_ECCMulInTypeDef "in" variable.

The result of the operation is the public key part of the .pem file. So the example compare the computed
result to the content of the .pem file to ensure the validity of the operation.

In case of success, the LD1 (BLUE) is ON.

In case of any error, the LD1 (BLUE) is toggling slowly.

#### <b>Notes</b>

1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
   based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
   a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
   than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
   To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
   to have correct HAL operation.

### <b>Keywords</b>

Security, PKA, FIPS PUB 186-4, ECC scalar multiplication

### <b>Directory contents</b>
  
  - PKA/PKA_ECCscalarMultiplication/Inc/stm32wbaxx_hal_conf.h      HAL configuration file
  - PKA/PKA_ECCscalarMultiplication/Inc/stm32wbaxx_nucleo_conf.h   BSP configuration file
  - PKA/PKA_ECCscalarMultiplication/Inc/stm32wbaxx_it.h            Interrupt handlers header file
  - PKA/PKA_ECCscalarMultiplication/Inc/main.h                     Header for main.c module
  - PKA/PKA_ECCscalarMultiplication/Src/stm32wbaxx_it.c            Interrupt handlers
  - PKA/PKA_ECCscalarMultiplication/Src/main.c                     Main program
  - PKA/PKA_ECCscalarMultiplication/Src/stm32wbaxx_hal_msp.c       HAL MSP module 
  - PKA/PKA_ECCscalarMultiplication/Src/system_stm32wbaxx.c        STM32WBAxx system source file
  - PKA/PKA_ECCscalarMultiplication/Src/prime256v1.c               Description of P-256 (ECDSA-256)
  - PKA/PKA_ECCscalarMultiplication/Inc/prime256v1.h               Header for prime256v1.c
  - PKA/PKA_ECCscalarMultiplication/Src/ecdsa_priv_prime256v1.pem  ecdsa private key generated using openssl
  - PKA/PKA_ECCscalarMultiplication/Src/ecdsa_priv_prime256v1.c    Reflect the content of ecdsa_priv_prime256v1.pem in array format
  - PKA/PKA_ECCscalarMultiplication/Inc/ecdsa_priv_prime256v1.h    Header for ecdsa_priv_prime256v1.c

### <b>Hardware and Software environment</b> 

  - This example runs on STM32WBA55CGUx devices.
  
  - This example has been tested with an STMicroelectronics NUCLEO-WBA55CG
    board and can be easily tailored to any other supported device 
    and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following:

 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 
