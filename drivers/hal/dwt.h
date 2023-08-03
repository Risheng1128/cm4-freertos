/**
 * @file dwt.h
 * @brief This file contains dwt macros
 */

#pragma once
#include <stdint.h>

#define DWT_CTRL    (*(uint32_t *)0xE0001000U) /* DWT Control Register */

/* enable the CYCCNT counter */
#define CYCCNT_COUNTER_EN() do { DWT_CTRL |= (1 << 0); } while (0)
