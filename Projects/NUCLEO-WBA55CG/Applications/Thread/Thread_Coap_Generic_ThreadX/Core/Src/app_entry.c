/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_entry.c
  * @author  MCD Application Team
  * @brief   Entry point of the application
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_common.h"
#include "log_module.h"
#include "app_conf.h"
#include "main.h"
#include "app_entry.h"
#include "stm32_rtos.h"
#if (CFG_LPM_LEVEL != 0)
#include "app_sys.h"
#include "stm32_lpm.h"
#endif /* (CFG_LPM_LEVEL != 0) */
#include "stm32_timer.h"
#if (CFG_LOG_SUPPORTED != 0)
#include "stm32_adv_trace.h"
#include "serial_cmd_interpreter.h"
#endif /* CFG_LOG_SUPPORTED */
#include "app_thread.h"
#include "otp.h"
#include "scm.h"
#include "ll_sys.h"

/* Private includes -----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32wbaxx_nucleo.h"
#include "serial_cmd_interpreter.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */
#if (CFG_BUTTON_SUPPORTED == 1)
typedef struct
{
  Button_TypeDef      button;
  UTIL_TIMER_Object_t longTimerId;
  uint8_t             longPressed;
  uint32_t            waitingTime;
} ButtonDesc_t;
#endif /* (CFG_BUTTON_SUPPORTED == 1) */

/* USER CODE END PTD */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN PD */
#if (CFG_BUTTON_SUPPORTED == 1)
#define BUTTON_LONG_PRESS_SAMPLE_MS           (50u)         // Sample Button every 50ms.
#define BUTTON_LONG_PRESS_THRESHOLD_MS        (500u)        // Normally 500ms if we use 'Long pression' on button.
#define BUTTON_NB_MAX                         (B3 + 1u)
#endif /* (CFG_BUTTON_SUPPORTED == 1) */
/* Push Button SW1 Task related defines */
#define TASK_BUTTON_SW1_STACK_SIZE            RTOS_STACK_SIZE_NORMAL
#define TASK_BUTTON_SW1_PRIORITY              CFG_TASK_PRIO_BUTTON_SWx
#define TASK_BUTTON_SW1_PREEM_TRES            CFG_TASK_PREEMP_BUTTON_SWx

/* Push Button SW2 Task related defines */
#define TASK_BUTTON_SW2_STACK_SIZE            RTOS_STACK_SIZE_NORMAL
#define TASK_BUTTON_SW2_PRIORITY              CFG_TASK_PRIO_BUTTON_SWx
#define TASK_BUTTON_SW2_PREEM_TRES            CFG_TASK_PREEMP_BUTTON_SWx

/* Push Button SW3 Task related defines */
#define TASK_BUTTON_SW3_STACK_SIZE            RTOS_STACK_SIZE_NORMAL
#define TASK_BUTTON_SW3_PRIORITY              CFG_TASK_PRIO_BUTTON_SWx
#define TASK_BUTTON_SW3_PREEM_TRES            CFG_TASK_PREEMP_BUTTON_SWx

/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private constants ---------------------------------------------------------*/
/* USER CODE BEGIN PC */

/* USER CODE END PC */

/* Private variables ---------------------------------------------------------*/

#if (CFG_LOG_SUPPORTED != 0)
/* Log configuration */
static Log_Module_t Log_Module_Config = { .verbose_level = APPLI_CONFIG_LOG_LEVEL, .region = LOG_REGION_ALL_REGIONS };
#endif /* (CFG_LOG_SUPPORTED != 0) */

/* ThreadX objects declaration */

static TX_THREAD      RngTaskHandle;
static TX_SEMAPHORE   RngSemaphore;

/* USER CODE BEGIN PV */
#if (CFG_BUTTON_SUPPORTED == 1)
/* Button management */
TX_SEMAPHORE          ButtonSw1Semaphore, ButtonSw2Semaphore, ButtonSw3Semaphore;
TX_THREAD             ButtonSw1Thread, ButtonSw2Thread, ButtonSw3Thread;
static ButtonDesc_t   buttonDesc[BUTTON_NB_MAX] = { { B1, { 0 }, 0, 0 } , { B2, { 0 } , 0, 0 }, { B3, { 0 }, 0, 0 } };
#endif /* (CFG_BUTTON_SUPPORTED == 1) */

/* USER CODE END PV */

/* Global variables ----------------------------------------------------------*/
/* ThreadX byte pool pointer for whole WPAN middleware */
TX_BYTE_POOL  * pBytePool;
CHAR          * pStack;

/* USER CODE BEGIN GV */

/* USER CODE END GV */

/* Private functions prototypes-----------------------------------------------*/
static void System_Init( void );
static void SystemPower_Config( void );
static void Config_HSE(void);
static void APPE_RNG_Init( void );

static void RNG_Task_Entry(ULONG lArgument);

#ifndef TX_LOW_POWER_USER_ENTER
void ThreadXLowPowerUserEnter( void );
#endif
#ifndef TX_LOW_POWER_USER_EXIT
void ThreadXLowPowerUserExit( void );
#endif

/* USER CODE BEGIN PFP */
#if (CFG_LED_SUPPORTED == 1)
static void Led_Init                      ( void );
#endif /* (CFG_LED_SUPPORTED == 1) */
#if (CFG_BUTTON_SUPPORTED == 1)
static void Button_Init                   ( void );
static void Button_TriggerActions         ( void * arg );
#endif /* (CFG_BUTTON_SUPPORTED == 1) */

/* USER CODE END PFP */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
/* USER CODE END EV */

/* Functions Definition ------------------------------------------------------*/
/**
 * @brief   Wireless Private Area Network configuration.
 */
void MX_APPE_Config(void)
{
  /* Configure HSE Tuning */
  Config_HSE();
}

/**
 * @brief   Wireless Private Area Network initialisation.
 */
uint32_t MX_APPE_Init(void *p_param)
{
  APP_DEBUG_SIGNAL_SET(APP_APPE_INIT);

  /* Save ThreadX byte pool for whole WPAN middleware */
  pBytePool = p_param;

  /* System initialization */
  System_Init();

  /* Configure the system Power Mode */
  SystemPower_Config();

  /* Initialize the Random Number Generator module */
  APPE_RNG_Init();

  /* USER CODE BEGIN APPE_Init_1 */
  /* Initialize Peripherals */
#if (CFG_LED_SUPPORTED == 1)
  Led_Init();
#endif /* (CFG_LED_SUPPORTED == 1) */
#if (CFG_BUTTON_SUPPORTED == 1)
  Button_Init();
#endif /* (CFG_BUTTON_SUPPORTED == 1) */

  /* USER CODE END APPE_Init_1 */

  /* Thread Initialisation */
  APP_THREAD_Init();
  ll_sys_config_params();

  /* USER CODE BEGIN APPE_Init_2 */

  /* USER CODE END APPE_Init_2 */

  APP_DEBUG_SIGNAL_RESET(APP_APPE_INIT);

  return WPAN_SUCCESS;
}

/* USER CODE BEGIN FD */
#if ( CFG_BUTTON_SUPPORTED == 1 ) 

/**
 * @brief   Indicate if the selected button was pressedn during a 'long time' or not.
 *
 * @param   btnIdx    Button to test, listed in enum Button_TypeDef
 * @return  '1' if pressed during a 'long time', else '0'.
 */
uint8_t APPE_ButtonIsLongPressed( uint16_t btnIdx )
{
  uint8_t pressStatus = 0;

  if ( btnIdx < BUTTON_NB_MAX )
  {
    pressStatus = buttonDesc[btnIdx].longPressed;
  }

  return pressStatus;
}

/**
 * @brief  Action of button 1 when pressed, to be implemented by user.
 * @param  None
 * @retval None
 */
__WEAK void APPE_Button1Action( void )
{
}

/**
 * @brief  Action of button 2 when pressed, to be implemented by user.
 * @param  None
 * @retval None
 */
__WEAK void APPE_Button2Action( void )
{
}

/**
 * @brief  Action of button 3 when pressed, to be implemented by user.
 * @param  None
 * @retval None
 */
__WEAK void APPE_Button3Action( void )
{
}

#endif /* ( CFG_BUTTON_SUPPORTED == 1 )  */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/**
 * @brief Configure HSE by read this Tuning from OTP
 *
 */
static void Config_HSE(void)
{
  OTP_Data_s* otp_ptr = NULL;

  /* Read HSE_Tuning from OTP */
  if (OTP_Read(DEFAULT_OTP_IDX, &otp_ptr) != HAL_OK)
  {
    /* OTP no present in flash, apply default gain */
    HAL_RCCEx_HSESetTrimming(0x0C);
  }
  else
  {
    HAL_RCCEx_HSESetTrimming(otp_ptr->hsetune);
  }
}

/**
 *
 */
static void System_Init( void )
{
  /* Clear RCC RESET flag */
  LL_RCC_ClearResetFlags();

  UTIL_TIMER_Init();

  /* Enable wakeup out of standby from RTC ( UTIL_TIMER )*/
  HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN7_HIGH_3);

#if (CFG_LOG_SUPPORTED != 0)
  /* Initialize the logs ( using the USART ) */
  Log_Module_Init( Log_Module_Config );
  Log_Module_Set_Region( LOG_REGION_APP );
  Log_Module_Add_Region( LOG_REGION_THREAD );

  /* Initialize the Command Interpreter */
  Serial_CMD_Interpreter_Init();
#endif  /* (CFG_LOG_SUPPORTED != 0) */

#if(CFG_RT_DEBUG_DTB == 1)
  /* DTB initialization and configuration */
  RT_DEBUG_DTBInit();
  RT_DEBUG_DTBConfig();
#endif /* CFG_RT_DEBUG_DTB */

  return;
}

/**
 * @brief  Configure the system for power optimization
 *
 * @note  This API configures the system to be ready for low power mode
 *
 * @param  None
 * @retval None
 */
static void SystemPower_Config(void)
{
#if (CFG_SCM_SUPPORTED == 1)
  /* Initialize System Clock Manager */
  scm_init();
#endif /* CFG_SCM_SUPPORTED */

#if (CFG_DEBUGGER_LEVEL == 0)
  /* Pins used by SerialWire Debug are now analog input */
  GPIO_InitTypeDef DbgIOsInit = {0};
  DbgIOsInit.Mode = GPIO_MODE_ANALOG;
  DbgIOsInit.Pull = GPIO_NOPULL;
  DbgIOsInit.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  HAL_GPIO_Init(GPIOA, &DbgIOsInit);

  DbgIOsInit.Mode = GPIO_MODE_ANALOG;
  DbgIOsInit.Pull = GPIO_NOPULL;
  DbgIOsInit.Pin = GPIO_PIN_3|GPIO_PIN_4;
  __HAL_RCC_GPIOB_CLK_ENABLE();
  HAL_GPIO_Init(GPIOB, &DbgIOsInit);
#endif /* CFG_DEBUGGER_LEVEL */

#if (CFG_LPM_LEVEL != 0)
  /* Initialize low Power Manager. By default enabled */
  UTIL_LPM_Init();

#if (CFG_LPM_STDBY_SUPPORTED == 1)
  /* Enable SRAM1, SRAM2 and RADIO retention*/
  LL_PWR_SetSRAM1SBRetention(LL_PWR_SRAM1_SB_FULL_RETENTION);
  LL_PWR_SetSRAM2SBRetention(LL_PWR_SRAM2_SB_FULL_RETENTION);
  LL_PWR_SetRadioSBRetention(LL_PWR_RADIO_SB_FULL_RETENTION); /* Retain sleep timer configuration */

#endif /* (CFG_LPM_STDBY_SUPPORTED == 1) */

  /* Disable LowPower during Init */
  UTIL_LPM_SetStopMode(1U << CFG_LPM_APP, UTIL_LPM_DISABLE);
  UTIL_LPM_SetOffMode(1U << CFG_LPM_APP, UTIL_LPM_DISABLE);
#endif /* (CFG_LPM_LEVEL != 0)  */

  /* USER CODE BEGIN SystemPower_Config */

  /* USER CODE END SystemPower_Config */
}

static void RNG_Task_Entry(ULONG lArgument)
{
  UNUSED(lArgument);

  for(;;)
  {
    tx_semaphore_get( &RngSemaphore, TX_WAIT_FOREVER );
    HW_RNG_Process();
    tx_thread_relinquish();
  }
}

/**
 * @brief Initialize Random Number Generator module
 */
static void APPE_RNG_Init(void)
{
  UINT TXstatus;
  CHAR *pStack;

  HW_RNG_Start();

  /* Create Random Number Generator ThreadX objects */

  TXstatus = tx_byte_allocate(pBytePool, (void **)&pStack, TASK_STACK_SIZE_RNG, TX_NO_WAIT);

  if( TXstatus == TX_SUCCESS )
  {
    TXstatus = tx_thread_create(&RngTaskHandle, "RNG Task", RNG_Task_Entry, 0,
                                 pStack, TASK_STACK_SIZE_RNG,
                                 TASK_PRIO_RNG, TASK_PREEMP_RNG,
                                 TX_NO_TIME_SLICE, TX_AUTO_START);

    TXstatus |= tx_semaphore_create(&RngSemaphore, "RNG Semaphore", 0);
  }

  if( TXstatus != TX_SUCCESS )
  {
    LOG_ERROR_APP( "RNG ThreadX objects creation FAILED, status: %d", TXstatus);
    Error_Handler();
  }
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */
#if ( CFG_LED_SUPPORTED == 1 )

static void Led_Init( void )
{
  /* Leds Initialization */
  BSP_LED_Init(LED_BLUE);
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);

  APP_LED_ON(LED_GREEN);
}

#endif // (CFG_LED_SUPPORTED == 1)
#if ( CFG_BUTTON_SUPPORTED == 1 )

/**
 * @brief  Management of the SW1 pushbutton task
 * @param  lArgument  Not used.
 * @retval None
 */
static void ButtonSw1Task( ULONG lArgument )
{
  UNUSED( lArgument );
  
  for(;;)
  {
    tx_semaphore_get( &ButtonSw1Semaphore, TX_WAIT_FOREVER );
    APPE_Button1Action();
    tx_thread_relinquish();
  }
}
    
/**
 * @brief  Management of the SW2 pushbutton task
 * @param  lArgument  Not used.
 * @retval None
 */
static void ButtonSw2Task( ULONG lArgument )
{
  UNUSED( lArgument );
  
  for(;;)
  {
    tx_semaphore_get( &ButtonSw2Semaphore, TX_WAIT_FOREVER );
    APPE_Button2Action();
    tx_thread_relinquish();
  }
}

/**
 * @brief  Management of the SW3 pushbutton task
 * @param  lArgument  Not used.
 * @retval None
 */
static void ButtonSw3Task( ULONG lArgument )
{
  UNUSED( lArgument );
  
  for(;;)
  {
    tx_semaphore_get( &ButtonSw3Semaphore, TX_WAIT_FOREVER );
    APPE_Button3Action();
    tx_thread_relinquish();
  }
}

static void Button_InitTask( void )
{
  UINT        ThreadXStatus;
  
  /* Register Semaphore to launch the pushbutton SW1 Task */
  ThreadXStatus = tx_semaphore_create( &ButtonSw1Semaphore, "ButtonSw1 Semaphore", 0 );
  
  /* Create the pushbutton SWx Thread and this Stack */
  if ( ThreadXStatus == TX_SUCCESS )
  {
    ThreadXStatus = tx_byte_allocate( pBytePool, (VOID**) &pStack, TASK_BUTTON_SW1_STACK_SIZE, TX_NO_WAIT);
  }
  if ( ThreadXStatus == TX_SUCCESS )
  {
    ThreadXStatus = tx_thread_create(  &ButtonSw1Thread, "ButtonSw1 Thread", ButtonSw1Task, 0, pStack,
                                        TASK_BUTTON_SW1_STACK_SIZE, TASK_BUTTON_SW1_PRIORITY, TASK_BUTTON_SW1_PREEM_TRES,
                                        TX_NO_TIME_SLICE, TX_AUTO_START );
  }
  
  /* Verify if it's OK */
  if ( ThreadXStatus != TX_SUCCESS )
  { 
    APP_DBG( "ERROR THREADX : PUSH BUTTON SW1 THREAD CREATION FAILED (0x%04X)", ThreadXStatus );
    while(1);
  }
  
  
  /* Register Semaphore to launch the pushbutton SW2 Task */
  ThreadXStatus = tx_semaphore_create( &ButtonSw2Semaphore, "ButtonSw2 Semaphore", 0 );
  
  /* Create the pushbutton SW2 Thread and this Stack */
  if ( ThreadXStatus == TX_SUCCESS )
  {
    ThreadXStatus = tx_byte_allocate( pBytePool, (VOID**) &pStack, TASK_BUTTON_SW2_STACK_SIZE, TX_NO_WAIT);
  }
  if ( ThreadXStatus == TX_SUCCESS )
  {
    ThreadXStatus = tx_thread_create(  &ButtonSw2Thread, "ButtonSw2 Thread", ButtonSw2Task, 0, pStack,
                                        TASK_BUTTON_SW2_STACK_SIZE, TASK_BUTTON_SW2_PRIORITY, TASK_BUTTON_SW2_PREEM_TRES,
                                        TX_NO_TIME_SLICE, TX_AUTO_START );
  }
  
  /* Verify if it's OK */
  if ( ThreadXStatus != TX_SUCCESS )
  { 
    APP_DBG( "ERROR THREADX : PUSH BUTTON SW2 THREAD CREATION FAILED (0x%04X)", ThreadXStatus );
    while(1);
  }
  
  
  /* Register Semaphore to launch the pushbutton SW3 Task */
  ThreadXStatus = tx_semaphore_create( &ButtonSw3Semaphore, "ButtonSw3 Semaphore", 0 );
  
  /* Create the pushbutton SW3 Thread and this Stack */
  if ( ThreadXStatus == TX_SUCCESS )
  {
    ThreadXStatus = tx_byte_allocate( pBytePool, (VOID**) &pStack, TASK_BUTTON_SW3_STACK_SIZE, TX_NO_WAIT);
  }
  if ( ThreadXStatus == TX_SUCCESS )
  {
    ThreadXStatus = tx_thread_create(  &ButtonSw3Thread, "ButtonSw3 Thread", ButtonSw3Task, 0, pStack,
                                        TASK_BUTTON_SW3_STACK_SIZE, TASK_BUTTON_SW3_PRIORITY, TASK_BUTTON_SW3_PREEM_TRES,
                                        TX_NO_TIME_SLICE, TX_AUTO_START );
  }
  
  /* Verify if it's OK */
  if ( ThreadXStatus != TX_SUCCESS )
  { 
    APP_DBG( "ERROR THREADX : PUSH BUTTON SW3 THREAD CREATION FAILED (0x%04X)", ThreadXStatus );
    while(1);
  }
}


static void Button_Init( void )
{
  Button_TypeDef  buttonIndex;
  
  /* Buttons HW Initialization */
  BSP_PB_Init( B1, BUTTON_MODE_EXTI );
  BSP_PB_Init( B2, BUTTON_MODE_EXTI );
  BSP_PB_Init( B3, BUTTON_MODE_EXTI );

  /* Button task initialisation */
  Button_InitTask();
  
  /* Button timers initialisation (one for each button) */
  for ( buttonIndex = B1; buttonIndex < BUTTON_NB_MAX; buttonIndex++ )
  { 
    UTIL_TIMER_Create( &buttonDesc[buttonIndex].longTimerId, 0, UTIL_TIMER_PERIODIC, &Button_TriggerActions, &buttonDesc[buttonIndex] ); 
  }
}


/**
 *
 */
static void Button_TriggerActions( void * arg )
{
  ButtonDesc_t  * p_buttonDesc = arg;
  int32_t       buttonState;

  buttonState = BSP_PB_GetState( p_buttonDesc->button );

  /* If Button pressed and Threshold time not finish, continue waiting */
  p_buttonDesc->waitingTime += BUTTON_LONG_PRESS_SAMPLE_MS;
  if ( ( buttonState == 1 ) && ( p_buttonDesc->waitingTime < BUTTON_LONG_PRESS_THRESHOLD_MS ) )
  {
    return;
  }

  /* Save button state */
  p_buttonDesc->longPressed = buttonState;

  /* Stop Timer */
  UTIL_TIMER_Stop( &p_buttonDesc->longTimerId );

  switch ( p_buttonDesc->button )
  {
    case B1:
        tx_semaphore_put( &ButtonSw1Semaphore );
        break;

    case B2:
        tx_semaphore_put( &ButtonSw2Semaphore );
        break;

    case B3:
        tx_semaphore_put( &ButtonSw3Semaphore );
        break;

    default:
        break;
  }
}

#endif /* (CFG_BUTTON_SUPPORTED == 1) */

/* USER CODE END FD_LOCAL_FUNCTIONS */

/*************************************************************
 *
 * WRAP FUNCTIONS
 *
 *************************************************************/

/**
 * @brief Callback used by Random Number Generator to launch Task to generate Random Numbers
 */
void HWCB_RNG_Process( void )
{
  if (RngSemaphore.tx_semaphore_count == 0)
  {
    tx_semaphore_put(&RngSemaphore);
  }
}

#if ((CFG_LOG_SUPPORTED == 0) && (CFG_LPM_LEVEL != 0))
/* RNG module turn off HSI clock when traces are not used and low power used */
void RNG_KERNEL_CLK_OFF(void)
{
  /* USER CODE BEGIN RNG_KERNEL_CLK_OFF_1 */

  /* USER CODE END RNG_KERNEL_CLK_OFF_1 */
  LL_RCC_HSI_Disable();
  /* USER CODE BEGIN RNG_KERNEL_CLK_OFF_2 */

  /* USER CODE END RNG_KERNEL_CLK_OFF_2 */
}

/* SCM module turn off HSI clock when traces are not used and low power used */
void SCM_HSI_CLK_OFF(void)
{
  /* USER CODE BEGIN SCM_HSI_CLK_OFF_1 */

  /* USER CODE END SCM_HSI_CLK_OFF_1 */
  LL_RCC_HSI_Disable();
  /* USER CODE BEGIN SCM_HSI_CLK_OFF_2 */

  /* USER CODE END SCM_HSI_CLK_OFF_2 */
}
#endif /* ((CFG_LOG_SUPPORTED == 0) && (CFG_LPM_LEVEL != 0)) */

#if (CFG_LOG_SUPPORTED != 0)
void UTIL_ADV_TRACE_PreSendHook(void)
{
#if (CFG_LPM_LEVEL != 0)
  /* Disable Stop mode before sending a LOG message over UART */
  UTIL_LPM_SetStopMode(1U << CFG_LPM_LOG, UTIL_LPM_DISABLE);
#endif /* (CFG_LPM_LEVEL != 0) */
  /* USER CODE BEGIN UTIL_ADV_TRACE_PreSendHook */

  /* USER CODE END UTIL_ADV_TRACE_PreSendHook */
}

void UTIL_ADV_TRACE_PostSendHook(void)
{
#if (CFG_LPM_LEVEL != 0)
  /* Enable Stop mode after LOG message over UART sent */
  UTIL_LPM_SetStopMode(1U << CFG_LPM_LOG, UTIL_LPM_ENABLE);
#endif /* (CFG_LPM_LEVEL != 0) */
  /* USER CODE BEGIN UTIL_ADV_TRACE_PostSendHook */

  /* USER CODE END UTIL_ADV_TRACE_PostSendHook */
}

#endif /* (CFG_LOG_SUPPORTED != 0) */

/**
 * @brief   Enter in LowPower Mode after a ThreadX call
 */
void ThreadXLowPowerUserEnter( void )
{
  /* USER CODE BEGIN ThreadXLowPowerUserEnter_1 */

  /* USER CODE END ThreadXLowPowerUserEnter_1 */

#if ( CFG_LPM_LEVEL != 0 )
  LL_PWR_ClearFlag_STOP();

  LL_RCC_ClearResetFlags();

  /* Wait until HSE is ready */
  while ( LL_RCC_HSE_IsReady() == 0 );

  UTILS_ENTER_LIMITED_CRITICAL_SECTION( RCC_INTR_PRIO << 4U );
  scm_hserdy_isr();
  UTILS_EXIT_LIMITED_CRITICAL_SECTION();
  HAL_SuspendTick();

  /* Disable SysTick Interrupt */
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
  UTIL_LPM_EnterLowPower();
#endif /* CFG_LPM_LEVEL */

  /* USER CODE BEGIN ThreadXLowPowerUserEnter_2 */

  /* USER CODE END ThreadXLowPowerUserEnter_2 */
  return;
}

/**
 * @brief   Exit of LowPower Mode after a ThreadX call
 */
void ThreadXLowPowerUserExit( void )
{
  /* USER CODE BEGIN ThreadXLowPowerUserExit_1 */

  /* USER CODE END ThreadXLowPowerUserExit_1 */

#if ( CFG_LPM_LEVEL != 0 )
  HAL_ResumeTick();

  /* Enable SysTick Interrupt */
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  LL_AHB5_GRP1_EnableClock( LL_AHB5_GRP1_PERIPH_RADIO );
  ll_sys_dp_slp_exit();
#endif /* CFG_LPM_LEVEL */

  /* USER CODE BEGIN ThreadXLowPowerUserExit_2 */

  /* USER CODE END ThreadXLowPowerUserExit_2 */
  return;
}

/**
 * @brief Function Assert AEABI in case of not described on 'libc' libraries.
 */
__WEAK void __aeabi_assert(const char * szExpression, const char * szFile, int iLine)
{
  Error_Handler();
}

/* USER CODE BEGIN FD_WRAP_FUNCTIONS */
#if ( CFG_BUTTON_SUPPORTED == 1 ) 

/**
 *
 */
void BSP_PB_Callback( Button_TypeDef button )
{
  buttonDesc[button].longPressed = 0;
  buttonDesc[button].waitingTime = 0;
  UTIL_TIMER_StartWithPeriod( &buttonDesc[button].longTimerId, BUTTON_LONG_PRESS_SAMPLE_MS );
}

#endif /* ( CFG_BUTTON_SUPPORTED == 1 )  */

/* USER CODE END FD_WRAP_FUNCTIONS */
