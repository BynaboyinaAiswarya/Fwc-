
#include "Fw_global_config.h"   // This defines application-specific characteristics
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "RtosTask.h"

/* Include generic headers required for QORC */
#include "eoss3_hal_gpio.h"
#include "eoss3_hal_rtc.h"
#include "eoss3_hal_timer.h"
#include "eoss3_hal_fpga_usbserial.h"
#include "ql_time.h"
#include "s3x_clock_hal.h"
#include "s3x_clock.h"
#include "s3x_pi.h"
#include "dbg_uart.h"
#include "cli.h"

/* Include GPIO functions for PyHal */
#include "PyHal_GPIO.h"

extern const struct cli_cmd_entry my_main_menu[];

const char *SOFTWARE_VERSION_STR;

extern void qf_hardwareSetup();
static void nvic_init(void);

#define GPIO_OUTPUT_MODE (1)
#define GPIO_INPUT_MODE (0)

int main(void)
{
    uint32_t i=0,j=0,k=0;
    SOFTWARE_VERSION_STR = "qorc-onion-apps/qf_gpio_expression_f";
    
    qf_hardwareSetup();
    nvic_init();

    dbg_str("\n\n");
    dbg_str("##########################\n");
    dbg_str("Quicklogic GPIO Expression Evaluation\n");
    dbg_str("SW Version: ");
    dbg_str(SOFTWARE_VERSION_STR);
    dbg_str("\n");
    dbg_str(__DATE__ " " __TIME__ "\n");
    dbg_str("##########################\n\n");

    dbg_str("\n\nStarting GPIO Expression Evaluation!!\n\n");

    CLI_start_task(my_main_menu);
    HAL_Delay_Init();

    // Define GPIOs for a, b, c, d, and f
    PyHal_GPIO_SetDir(2, GPIO_INPUT_MODE);  // a
    PyHal_GPIO_SetDir(6, GPIO_INPUT_MODE);  // b
    PyHal_GPIO_SetDir(4, GPIO_INPUT_MODE);  // c
    PyHal_GPIO_SetDir(5, GPIO_INPUT_MODE);  // d
    PyHal_GPIO_SetDir(13, GPIO_OUTPUT_MODE); // f (output)

    while(1)
    {
        // Read values of a, b, c, and d from GPIOs
        int a = PyHal_GPIO_Get(2);
        int b = PyHal_GPIO_Get(6);
        int c = PyHal_GPIO_Get(4);
        int d = PyHal_GPIO_Get(5);

        // Calculate f based on the expression f = ab'c'd' + a'bcd + ab'cd
        int f = (a && !b && !c && !d) || (!a && b && c && d) || (a && !b && c && d);

        // Set the GPIO for f
        PyHal_GPIO_Set(13, f);

        HAL_DelayUSec(1000000); // 1 second delay
    }

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
    dbg_str("\n");

    while(1);
}

static void nvic_init(void)
{
    NVIC_SetPriority(Ffe0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(SpiMs_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(CfgDma_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(Uart_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(FbMsg_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
}

//needed for startup_EOSS3b.s asm file
void SystemInit(void)
{

}
