/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    service2_app.h
  * @author  MCD Application Team
  * @brief   Header for service2_app.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HTS_APP_H
#define HTS_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  HTS_CONN_HANDLE_EVT,
  HTS_DISCON_HANDLE_EVT,

  /* USER CODE BEGIN Service2_OpcodeNotificationEvt_t */

  /* USER CODE END Service2_OpcodeNotificationEvt_t */

  HTS_LAST_EVT,
} HTS_APP_OpcodeNotificationEvt_t;

typedef struct
{
  HTS_APP_OpcodeNotificationEvt_t          EvtOpcode;
  uint16_t                                 ConnectionHandle;

  /* USER CODE BEGIN HTS_APP_ConnHandleNotEvt_t */

  /* USER CODE END HTS_APP_ConnHandleNotEvt_t */
} HTS_APP_ConnHandleNotEvt_t;
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void HTS_APP_Init(void);
void HTS_APP_EvtRx(HTS_APP_ConnHandleNotEvt_t *p_Notification);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*HTS_APP_H */
