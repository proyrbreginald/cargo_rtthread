#include "main.h"

/* LED Port/Pin definition */
#define LED_G_PORT (GPIO_PORT_C)
#define LED_G_PIN (GPIO_PIN_15)

/**
 * @brief  LED Init
 * @param  None
 * @retval None
 */
static void LED_Init(void)
{
        stc_gpio_init_t stcGpioInit;
        (void)GPIO_StructInit(&stcGpioInit);
        stcGpioInit.u16PinState = PIN_STAT_RST;
        stcGpioInit.u16PinDir = PIN_DIR_OUT;
        (void)GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
}

/**
 * @brief  Main function of GPIO project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
        /* Register write enable for some required peripherals. */
        LL_PERIPH_WE(LL_PERIPH_GPIO);
        /* LED initialize */
        LED_Init();
        /* Register write protected for some required peripherals. */
        LL_PERIPH_WP(LL_PERIPH_GPIO);
        for (;;)
        {
                GPIO_TogglePins(LED_G_PORT, LED_G_PIN);
                DDL_DelayMS(1000u);
        }
}