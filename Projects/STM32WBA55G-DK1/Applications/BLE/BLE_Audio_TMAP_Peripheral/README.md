## __BLE_Audio_TMAP_Peripheral Application Description__

How to use the Telephony and Media Profile profile in Unicast Server role (Call Terminal and/or Unicast Media Receiver) and Broadcast Sink role (Broadcast Media Received)
as specified by the Bluetooth SIG.

The TMAP Peripheral application, in Unicast Server role, advertises and accepts Isochronous Connection from a remote TMAP Client (Call Gateway and/or Unicast Media Sender).
The TMAP Peripheral supports Volume Control, Call Control and Media Control features.
The TMAP Peripheral application, in Broadcast role, scans and synchronizes audio streams from remote PBP Sources.

### __Keywords__

Connectivity, BLE, BLE protocol, BLE pairing, BLE profile, BLE audio

### __Directory contents__

  - BLE_Audio_TMAP_Peripheral/Core/Inc/app_common.h                                        App Common application configuration file for STM32WPAN Middleware.
  - BLE_Audio_TMAP_Peripheral/Core/Inc/app_conf.h                                          Application configuration file for STM32WPAN Middleware.
  - BLE_Audio_TMAP_Peripheral/Core/Inc/app_entry.h                                         Interface to the application
  - BLE_Audio_TMAP_Peripheral/Core/Inc/main.h                                              Header for main.c file. This file contains the common defines of the application.
  - BLE_Audio_TMAP_Peripheral/Core/Inc/stm32wba55g_discovery_conf.h                        STM32WBA55G_DK1 board configuration file.
  - BLE_Audio_TMAP_Peripheral/Core/Inc/stm32wbaxx_hal_conf.h                               HAL configuration file.
  - BLE_Audio_TMAP_Peripheral/Core/Inc/stm32wbaxx_it.h                                     This file contains the headers of the interrupt handlers.
  - BLE_Audio_TMAP_Peripheral/Core/Inc/utilities_conf.h                                    Header for configuration file for STM32 Utilities.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/app_ble.h                                     Header for ble application
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/app_menu.h                                	   Header for Menu file.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/app_menu_cfg.h                            	   Header for Menu Configuration file.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/ble_conf.h                                    Configuration file for BLE Middleware.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/ble_dbg_conf.h                                Debug configuration file for BLE Middleware.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/tmap_app.h									   Header for tmap_app.c module
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/tmap_app_conf.h                           	   Application configuration file for tmap_app.c module
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/pbp/pbp.h                       This file contains definitions used for Media Control Profile
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/pbp/pbp_alloc.h                 This file contains definitions used for Public Broadcast Profile Allocation context
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/pbp/pbp_config.h                This file contains Public Broadcast Profile Configuration
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/pbp/pbp_log.h                   This file contains definitions and configuration used for Public Broadcast Profile Logging
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmap.h                     This file contains definitions used for Telephony and Media Audio Profile
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmap_alloc.h               This file contains definitions used for Telephony and Media Audio Profile Allocation context
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmap_config.h              This file contains Telephony and Media Audio Profile Configuration
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmap_db.h                  This file contains definitions used for TMAP Profile Database.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmap_log.h                 This file contains definitions and configuration used for Telephony and Media Audio Profile Logging
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmas.h   				   Service file contains definitions used for Telephony and Media Audio
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/bpka.h                                     This file contains the interface of the BLE PKA module.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/host_stack_if.h                            This file contains the interface for the stack tasks
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/ll_sys_if.h                                Header file for initiating system
  - BLE_Audio_TMAP_Peripheral/System/Config/CRC_Ctrl/crc_ctrl_conf.h                       Configuration Header for crc_ctrl.c module
  - BLE_Audio_TMAP_Peripheral/System/Config/Debug_GPIO/app_debug.h                         Real Time Debug module application APIs and signal table
  - BLE_Audio_TMAP_Peripheral/System/Config/Debug_GPIO/app_debug_signal_def.h              Real Time Debug module application signal definition
  - BLE_Audio_TMAP_Peripheral/System/Config/Debug_GPIO/debug_config.h                      Real Time Debug module general configuration file
  - BLE_Audio_TMAP_Peripheral/System/Config/Flash/simple_nvm_arbiter_conf.h                Configuration header for simple_nvm_arbiter.c module
  - BLE_Audio_TMAP_Peripheral/System/Config/Log/log_module.h                               Header file of the log module.
  - BLE_Audio_TMAP_Peripheral/System/Config/LowPower/app_sys.h                             Header for app_sys.c
  - BLE_Audio_TMAP_Peripheral/System/Config/LowPower/peripheral_init.h                     Header for peripheral init module
  - BLE_Audio_TMAP_Peripheral/System/Config/LowPower/user_low_power_config.h               Header for user_low_power_config.c
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/hw.h                                       This file contains the interface of STM32 HW drivers.
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/hw_if.h                                    Hardware Interface
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/stm32_lpm_if.h                             Header for stm32_lpm_if.c module (device specific LP management)
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/timer_if.h                                 Configuration of the timer_if.c instances
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/usart_if.h                                 Header file for stm32_adv_trace interface file
  - BLE_Audio_TMAP_Peripheral/System/Modules/ble_timer.h                                   This header defines the timer functions used by the BLE stack
  - BLE_Audio_TMAP_Peripheral/System/Modules/crc_ctrl.h                                    Header for CRC client manager module
  - BLE_Audio_TMAP_Peripheral/System/Modules/dbg_trace.h                                   Header for dbg_trace.c
  - BLE_Audio_TMAP_Peripheral/System/Modules/general_config.h                              This file contains definitions that can be changed to configure some modules of the STM32 firmware application.
  - BLE_Audio_TMAP_Peripheral/System/Modules/otp.h                                         Header file for One Time Programmable (OTP) area
  - BLE_Audio_TMAP_Peripheral/System/Modules/scm.h                                         Header for scm.c module
  - BLE_Audio_TMAP_Peripheral/System/Modules/stm_list.h                                    Header file for linked list library.
  - BLE_Audio_TMAP_Peripheral/System/Modules/stm_queue.h                                   Header for stm_queue.c
  - BLE_Audio_TMAP_Peripheral/System/Modules/utilities_common.h                            Common file to utilities
  - BLE_Audio_TMAP_Peripheral/System/Modules/baes/baes.h                                   This file contains the interface of the basic AES software module.
  - BLE_Audio_TMAP_Peripheral/System/Modules/baes/baes_global.h                            This file contains the internal definitions of the AES software module.
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/flash_driver.h                          Header for flash_driver.c module
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/flash_manager.h                         Header for flash_manager.c module
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/rf_timing_synchro.h                     Header for rf_timing_synchro.c module
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/simple_nvm_arbiter.h                    Header for simple_nvm_arbiter.c module
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/simple_nvm_arbiter_common.h             Common header of simple_nvm_arbiter.c module
  - BLE_Audio_TMAP_Peripheral/System/Modules/MemoryManager/advanced_memory_manager.h       Header for advance_memory_manager.c module
  - BLE_Audio_TMAP_Peripheral/System/Modules/MemoryManager/stm32_mm.h                      Header for stm32_mm.c module
  - BLE_Audio_TMAP_Peripheral/System/Modules/Nvm/nvm.h                                     This file contains the interface of the NVM manager.
  - BLE_Audio_TMAP_Peripheral/System/Modules/RFControl/rf_antenna_switch.h                 RF related module to handle dedictated GPIOs for antenna switch
  - BLE_Audio_TMAP_Peripheral/System/Modules/RTDebug/debug_signals.h                       Real Time Debug module System and Link Layer signal definition
  - BLE_Audio_TMAP_Peripheral/System/Modules/RTDebug/local_debug_tables.h                  Real Time Debug module System and Link Layer signal
  - BLE_Audio_TMAP_Peripheral/System/Modules/RTDebug/RTDebug.h                             Real Time Debug module API declaration
  - BLE_Audio_TMAP_Peripheral/System/Modules/RTDebug/RTDebug_dtb.h                         Real Time Debug module API declaration for DTB usage
  - BLE_Audio_TMAP_Peripheral/System/Modules/SerialCmdInterpreter/serial_cmd_interpreter.h Header file for the serial commands interpreter module.
  - BLE_Audio_TMAP_Peripheral/Core/Src/app_entry.c                                         Entry point of the application
  - BLE_Audio_TMAP_Peripheral/Core/Src/image.c                                             image used for the LCD
  - BLE_Audio_TMAP_Peripheral/Core/Src/main.c                                              Main program body
  - BLE_Audio_TMAP_Peripheral/Core/Src/stm32wbaxx_hal_msp.c                                This file provides code for the MSP Initialization and de-Initialization codes.
  - BLE_Audio_TMAP_Peripheral/Core/Src/stm32wbaxx_it.c                                     Interrupt Service Routines.
  - BLE_Audio_TMAP_Peripheral/Core/Src/system_stm32wbaxx.c                                 CMSIS Cortex-M33 Device Peripheral Access Layer System Source File
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/app_ble.c                                     BLE Application
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/tmap_app.c                                    TMAP Application
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/usecase_dev_mgmt.c              This file contains Device Management for Use Case Profiles
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/pbp/pbp.c					   This file contains Public Broadcast Profile feature
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/pbp/pbp_alloc.c				   This file contains Public Broadcast Profile Allocation context
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmap.c                     This file contains Telephony and Media Audio Profile feature
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmap_alloc.c               This file contains Telephony and Media Audio Profile Allocation context
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmap_db.c                  This file contains interfaces of TMAP Database
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/App/AudioUseCases/tmap/tmas.c                     This file contains Telephony and Media Audio Service
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/bleplat.c                                  This file implements the platform functions for BLE stack library.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/ble_audio_if.c                       	   This file implements the interface functions for BLE Audio Profiles of the Generic Audio Framework
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/ble_audio_plat.c                           This file implements the platform functions for BLE Audio Profiles
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/ble_codec.c                                This file implements the Codec functions for BLE stack library.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/bpka.c                                     This file implements the BLE PKA module.
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/codec_if.c                                 File for codec manager integration : process and high speed timer. This timer needs to run on the same clock domain as the audio interface
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/host_stack_if.c                            Source file for the stack tasks
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/linklayer_plat.c                           Source file for the linklayer plateform adaptation layer
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/ll_sys_if.c                                Source file for initiating system
  - BLE_Audio_TMAP_Peripheral/STM32_WPAN/Target/power_table.c                              This file contains supported power tables
  - BLE_Audio_TMAP_Peripheral/System/Config/CRC_Ctrl/crc_ctrl_conf.c                       Source for CRC client controller module configuration file
  - BLE_Audio_TMAP_Peripheral/System/Config/Debug_GPIO/app_debug.c                         Real Time Debug module application side APIs
  - BLE_Audio_TMAP_Peripheral/System/Config/Flash/simple_nvm_arbiter_conf.c                The Simple NVM arbiter module provides an interface to write and/or restore data from SRAM to FLASH with use of NVMs.
  - BLE_Audio_TMAP_Peripheral/System/Config/Log/log_module.c                               Source file of the log module.
  - BLE_Audio_TMAP_Peripheral/System/Config/LowPower/peripheral_init.c                     Header for peripheral init module
  - BLE_Audio_TMAP_Peripheral/System/Config/LowPower/user_low_power_config.c               Low power related user configuration.
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/hw_aes.c                                   This file contains the AES driver for STM32WBA
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/hw_otp.c                                   This file contains the OTP driver.
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/hw_pka.c                                   This file contains the PKA driver for STM32WBA
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/hw_rng.c                                   This file contains the RNG driver for STM32WBA
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/pka_p256.c                            	   This file is an optional part of the PKA driver for STM32WBA.
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/stm32_lpm_if.c                             Low layer function to enter/exit low power modes (stop, sleep)
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/timer_if.c                                 Configure RTC Alarm, Tick and Calendar manager
  - BLE_Audio_TMAP_Peripheral/System/Interfaces/usart_if.c                                 Source file for interfacing the stm32_adv_trace to hardware
  - BLE_Audio_TMAP_Peripheral/System/Modules/app_sys.c                                     Application system for STM32WPAN Middleware.
  - BLE_Audio_TMAP_Peripheral/System/Modules/ble_timer.c                                   This module implements the timer core functions
  - BLE_Audio_TMAP_Peripheral/System/Modules/crc_ctrl.c                                    Source for CRC client controller module
  - BLE_Audio_TMAP_Peripheral/System/Modules/otp.c                                         Source file for One Time Programmable (OTP) area
  - BLE_Audio_TMAP_Peripheral/System/Modules/scm.c                                         Functions for the System Clock Manager.
  - BLE_Audio_TMAP_Peripheral/System/Modules/stm_list.c                                    TCircular Linked List Implementation.
  - BLE_Audio_TMAP_Peripheral/System/Modules/stm_queue.c                                   Queue management
  - BLE_Audio_TMAP_Peripheral/System/Modules/baes/baes_ccm.c                           	   This file contains the AES CCM implementation.
  - BLE_Audio_TMAP_Peripheral/System/Modules/baes/baes_cmac.c                              This file contains the AES CMAC implementation.
  - BLE_Audio_TMAP_Peripheral/System/Modules/baes/baes_ecb.c                               This file contains the AES ECB functions implementation.
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/flash_driver.c                          The Flash Driver module is the interface layer between Flash management modules and HAL Flash drivers
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/flash_manager.c						   The Flash Manager module provides an interface to write raw data from SRAM to FLASH
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/rf_timing_synchro.c                     The RF Timing Synchronization module provides an interface to synchronize the flash processing versus the RF activity to make sure the RF timing is not broken
  - BLE_Audio_TMAP_Peripheral/System/Modules/Flash/rsimple_nvm_arbiter.c				   The Simple NVM arbiter module provides an interface to write and/or restore data from SRAM to FLASH with use of NVMs.
  - BLE_Audio_TMAP_Peripheral/System/Modules/MemoryManager/advanced_memory_manager.c       Memory Manager
  - BLE_Audio_TMAP_Peripheral/System/Modules/MemoryManager/stm32_mm.c                      Memory Manager Utility
  - BLE_Audio_TMAP_Peripheral/System/Modules/Nvm/nvm_emul.c                                This file implements the RAM version of the NVM manager for STM32WBX. It is made for test purpose
  - BLE_Audio_TMAP_Peripheral/System/Modules/RFControl/rf_antenna_switch.c                 RF related module to handle dedictated GPIOs for antenna switch
  - BLE_Audio_TMAP_Peripheral/System/Modules/RTDebug/RTDebug.c                             Real Time Debug module API definition
  - BLE_Audio_TMAP_Peripheral/System/Modules/RTDebug/RTDebug_dtb.c                         Real Time Debug module API definition for DTB usage
  - BLE_Audio_TMAP_Peripheral/System/Modules/SerialCmdInterpreter/serial_cmd_interpreter.c Source file for the serial commands interpreter module.


### __Hardware and Software environment__

  - This example runs on STM32WBA55xx devices with SMPS.
    Connect the Discovery Board to your PC with a USB cable type C.
	Connect a headset (optionnaly with microphone to enable bidirectional streams) on Jack Connector CN3.

### __How to use it?__

In order to make the program work, you must do the following:

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 - At startup, after pressing the Right direction on the joystick, the user enters in a menu offering following actions:
	- "Start Unicast" : the application starts the features associated to the TMAP Unicast Server role (Unicast Server, Media Control, Call Control, Volume Control).
	- "Start Broadcast" : the application starts the features associated to the TMAP Broadcast Sink role
	- "Audio Config" : the user can select if the application is an Headphone, an Earbud Right, or an Earbud Left
	- "Clear Sec. DB" : clear all the information of the bonded devices
 - Once "Start Unicast" in TMAP Peripheral is executed, the application starts advertising with a name displayed on the screen and wait for an incoming connection from a remote Unicast Client.
    - Using a device compatible with BLE Audio Unicast Client role (Smartphone supporting LE Audio Feature for example), connect to the TMAP Peripheral and perform Link-Up of available services.
	- Once the Unicast Client is connected, it can start a streaming procedure (Media Playing or Call) to send audio to the TMAP Peripheral. High Quality Media unidirectional streams can be established, as well as conversational bidirectional streams.
	- Once application is connected to a Central, it can manage Call Control, Media Control or Volume control if features is supported by both devices.
	- Once application is connected to a Central, using the Right direction on the joystick, the menu can be accessed:
		- Select Volume Control to access a panel where the volume can be adjusted and displayed using the VCP as VCP Renderer role (Volume Up / Volume Down / Mute)
		- Select Media Control to access a panel where the media tracks can be controlled and displayed using the MCP as Media Control Client (Next Track / Previous Track / Play|Pause)
		- Select Call Control to access a panel where the current calls can be controlled and displayed using the CCP as Call Control Client (Answer Call / Terminate Call)
		- Select Disconnect to disconnect from the device
 - Once "Start Broadcast" in TMAP Peripheral is executed, the application scans the remote Broadcast Sources and display them on the LCD.
	- Select with the Joystick the Broadcast Source to synchronize to.
	- Once the TMAP Peripheral is synchronized to the Broadcast Source and Audio Stream is received, Audio is available on Jack Connector.
	- Once synchronization with the Broadcast Source is complete, using the Right direction on the joystick, local volume can be modified and Audio Sink can be stopped (Broadcast desynchronization)