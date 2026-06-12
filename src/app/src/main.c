#include <hc32_ll.h>
#include <main.h>
#include <rtt.h>


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
int main(void)
{
        /* LED initialize */
        LED_Init();

        for (;;)
        {
                GPIO_TogglePins(LED_G_PORT, LED_G_PIN);
                DDL_DelayMS(1000u);
                rtt_write("test\n", 5);
        }
}