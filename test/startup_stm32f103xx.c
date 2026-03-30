#include <stdint.h>

#define BootRAM 0xF108F85F

#ifdef __GNUC__
#  define ISR __attribute__((weak, alias("Default_Handler")))
#endif

extern uint8_t _sidata;
extern uint8_t _sdata;
extern uint8_t _edata;
extern uint8_t _sbss;
extern uint8_t _ebss;
extern uint8_t _estack;

void __libc_init_array(void);
[[noreturn]] int main(void);

void Reset_Handler(void);
void Default_Handler(void);
ISR void NMI_Handler(void);
ISR void HardFault_Handler(void);
ISR void MemManage_Handler(void);
ISR void BusFault_Handler(void);
ISR void UsageFault_Handler(void);
ISR void SVC_Handler(void);
ISR void DebugMon_Handler(void);
ISR void PendSV_Handler(void);
ISR void SysTick_Handler(void);
ISR void WWDG_IRQHandler(void);
ISR void PVD_IRQHandler(void);
ISR void TAMPER_IRQHandler(void);
ISR void RTC_IRQHandler(void);
ISR void FLASH_IRQHandler(void);
ISR void RCC_IRQHandler(void);
ISR void EXTI0_IRQHandler(void);
ISR void EXTI1_IRQHandler(void);
ISR void EXTI2_IRQHandler(void);
ISR void EXTI3_IRQHandler(void);
ISR void EXTI4_IRQHandler(void);
ISR void DMA1_Channel1_IRQHandler(void);
ISR void DMA1_Channel2_IRQHandler(void);
ISR void DMA1_Channel3_IRQHandler(void);
ISR void DMA1_Channel4_IRQHandler(void);
ISR void DMA1_Channel5_IRQHandler(void);
ISR void DMA1_Channel6_IRQHandler(void);
ISR void DMA1_Channel7_IRQHandler(void);
ISR void ADC1_2_IRQHandler(void);
ISR void USB_HP_CAN1_TX_IRQHandler(void);
ISR void USB_LP_CAN1_RX0_IRQHandler(void);
ISR void CAN1_RX1_IRQHandler(void);
ISR void CAN1_SCE_IRQHandler(void);
ISR void EXTI9_5_IRQHandler(void);
ISR void TIM1_BRK_IRQHandler(void);
ISR void TIM1_UP_IRQHandler(void);
ISR void TIM1_TRG_COM_IRQHandler(void);
ISR void TIM1_CC_IRQHandler(void);
ISR void TIM2_IRQHandler(void);
ISR void TIM3_IRQHandler(void);
ISR void TIM4_IRQHandler(void);
ISR void I2C1_EV_IRQHandler(void);
ISR void I2C1_ER_IRQHandler(void);
ISR void I2C2_EV_IRQHandler(void);
ISR void I2C2_ER_IRQHandler(void);
ISR void SPI1_IRQHandler(void);
ISR void SPI2_IRQHandler(void);
ISR void USART1_IRQHandler(void);
ISR void USART2_IRQHandler(void);
ISR void USART3_IRQHandler(void);
ISR void EXTI15_10_IRQHandler(void);
ISR void RTC_Alarm_IRQHandler(void);
ISR void USBWakeUp_IRQHandler(void);

[[gnu::section(".isr_vector")]]
const uint32_t g_pfnVectors[] = {
  (uint32_t)&_estack,
  (uint32_t)&Reset_Handler,
  (uint32_t)&NMI_Handler,
  (uint32_t)&HardFault_Handler,
  (uint32_t)&MemManage_Handler,
  (uint32_t)&BusFault_Handler,
  (uint32_t)&UsageFault_Handler,
  0,
  0,
  0,
  0,
  (uint32_t)&SVC_Handler,
  (uint32_t)&DebugMon_Handler,
  0,
  (uint32_t)&PendSV_Handler,
  (uint32_t)&SysTick_Handler,
  (uint32_t)&WWDG_IRQHandler,
  (uint32_t)&PVD_IRQHandler,
  (uint32_t)&TAMPER_IRQHandler,
  (uint32_t)&RTC_IRQHandler,
  (uint32_t)&FLASH_IRQHandler,
  (uint32_t)&RCC_IRQHandler,
  (uint32_t)&EXTI0_IRQHandler,
  (uint32_t)&EXTI1_IRQHandler,
  (uint32_t)&EXTI2_IRQHandler,
  (uint32_t)&EXTI3_IRQHandler,
  (uint32_t)&EXTI4_IRQHandler,
  (uint32_t)&DMA1_Channel1_IRQHandler,
  (uint32_t)&DMA1_Channel2_IRQHandler,
  (uint32_t)&DMA1_Channel3_IRQHandler,
  (uint32_t)&DMA1_Channel4_IRQHandler,
  (uint32_t)&DMA1_Channel5_IRQHandler,
  (uint32_t)&DMA1_Channel6_IRQHandler,
  (uint32_t)&DMA1_Channel7_IRQHandler,
  (uint32_t)&ADC1_2_IRQHandler,
  (uint32_t)&USB_HP_CAN1_TX_IRQHandler,
  (uint32_t)&USB_LP_CAN1_RX0_IRQHandler,
  (uint32_t)&CAN1_RX1_IRQHandler,
  (uint32_t)&CAN1_SCE_IRQHandler,
  (uint32_t)&EXTI9_5_IRQHandler,
  (uint32_t)&TIM1_BRK_IRQHandler,
  (uint32_t)&TIM1_UP_IRQHandler,
  (uint32_t)&TIM1_TRG_COM_IRQHandler,
  (uint32_t)&TIM1_CC_IRQHandler,
  (uint32_t)&TIM2_IRQHandler,
  (uint32_t)&TIM3_IRQHandler,
  (uint32_t)&TIM4_IRQHandler,
  (uint32_t)&I2C1_EV_IRQHandler,
  (uint32_t)&I2C1_ER_IRQHandler,
  (uint32_t)&I2C2_EV_IRQHandler,
  (uint32_t)&I2C2_ER_IRQHandler,
  (uint32_t)&SPI1_IRQHandler,
  (uint32_t)&SPI2_IRQHandler,
  (uint32_t)&USART1_IRQHandler,
  (uint32_t)&USART2_IRQHandler,
  (uint32_t)&USART3_IRQHandler,
  (uint32_t)&EXTI15_10_IRQHandler,
  (uint32_t)&RTC_Alarm_IRQHandler,
  (uint32_t)&USBWakeUp_IRQHandler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  BootRAM
};

#ifdef __GNUC__
__attribute__((noreturn))
#endif
void Reset_Handler(void) {
  uint32_t *p_data = (uint32_t *)&_sdata;
  const uint32_t *p_idata = (uint32_t *)&_sidata;
  for (; p_data < (uint32_t *)&_edata; ++p_data, ++p_idata) {
    *p_data = *p_idata;
  }

  for (uint32_t *p_bss = (uint32_t *)&_sbss; p_bss < (uint32_t *)&_ebss;
       ++p_bss) {
    *p_bss = 0;
  }

  __libc_init_array();
  main();
}

void Default_Handler(void) {
  while (1)
    ;
}
