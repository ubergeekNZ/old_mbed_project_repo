#include "SramInterface.h"

SramInterface::SramInterface()
{
  /* Enable PWR clock */
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  
  /* Enable backup SRAM Clock */
  RCC->AHB1ENR |= RCC_AHB1ENR_BKPSRAMEN;
  
  /* Allow access to backup domain */
  // PWR_BackupAccessCmd(ENABLE);

  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)ENABLE;
  
  /* Enable the Backup SRAM low power Regulator */
  /* This will allow data to stay when using VBat mode */
  // PWR_BackupRegulatorCmd(ENABLE);

  *(__IO uint32_t *) CSR_BRE_BB = (uint32_t)ENABLE;
  
  /* Wait for backup regulator to be ready  */
  while (!(PWR->CSR & (PWR_FLAG_BRR)));
}


void SramInterface::Write8Bits(uint32_t address, uint8_t value)
{
  *(volatile uint8_t *) (BKPSRAM_BASE + (address)) = (value);
}

void SramInterface::Write16Bits(uint32_t address, uint16_t value)
{
  *(volatile uint16_t *) (BKPSRAM_BASE + (address)) = (value);
}

void SramInterface::Write32Bits(uint32_t address, uint32_t value)
{
  *(volatile uint32_t *) (BKPSRAM_BASE + (address)) = (value);
}

void SramInterface::WriteFloat(uint32_t address, float value)
{
  *(volatile float *) (BKPSRAM_BASE + (address)) = (value);
}

uint8_t SramInterface::Read8Bits(uint32_t address)
{
  return *(volatile uint8_t *) (BKPSRAM_BASE + address);
}

uint16_t SramInterface::Read16Bits(uint32_t address)
{
  return *(volatile uint16_t *) (BKPSRAM_BASE + address);
}

uint32_t SramInterface::Read32Bits(uint32_t address)
{
  return *(volatile uint32_t *) (BKPSRAM_BASE + address);
}

float SramInterface::ReadFloat(uint32_t address)
{
  return *(volatile float *) (BKPSRAM_BASE + address);
} 
