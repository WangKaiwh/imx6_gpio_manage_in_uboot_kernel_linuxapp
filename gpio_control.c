
/*
 * <c> copyright ShenZhen Yuwei Ltd.
 * Author: King 2016.4.27
 */

#define __BOOTER_CODE 1
#define __LINUX_KERNEL 0
#define __LINUX_APP   0

#define __debug__   1

# if __BOOTER_CODE
#include <common.h>
#include <asm-arm/arch-mx6/iomux-v3.h>
#include <asm-arm/arch-mx6/gpio.h>
#include <asm-arm/arch-mx6/mx6dl_pins.h>
#include <asm/io.h>
#include "../libra/libra.h"
//
# elif __LINUX_KERNEL
//
# else // linux app
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long long iomux_v3_cfg_t;
# endif

#include "ywwh_gpio_control.h"

#if __BOOTER_CODE
struct gpio_desc_body desc_list[1] = {
    /**
     *  hardware
     */
    // uart
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(6, 17), MX6DL_PAD_SD3_DAT7__UART1_TXD, "UART1_TXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(6, 18), MX6DL_PAD_SD3_DAT6__UART1_RXD, "UART1_RXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(7, 1), MX6DL_PAD_SD3_DAT4__UART2_RXD, "UART2_RXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(7, 0), MX6DL_PAD_SD3_DAT5__UART2_TXD, "UART2_TXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(7, 2), MX6DL_PAD_SD3_CMD__UART2_CTS, "UART2_CTS"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(7, 3), MX6DL_PAD_SD3_CLK__UART2_RTS, "UART2_RTS"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(3, 24), MX6DL_PAD_EIM_D24__UART3_TXD, "UART3_TXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(3, 25), MX6DL_PAD_EIM_D25__UART3_RXD, "UART3_RXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 7), MX6DL_PAD_KEY_ROW0__UART4_RXD, "UART4_RXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 6), MX6DL_PAD_KEY_COL0__UART4_TXD, "UART4_TXD"},

    // i2c
    {gpio_dynamic, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 26), MX6DL_PAD_CSI0_DAT8__I2C1_SDA, "I2C1_SDA"},
    {gpio_dynamic, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 27), MX6DL_PAD_CSI0_DAT9__I2C1_SCL, "I2C1_SCL"},
    {gpio_dynamic, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 13), MX6DL_PAD_KEY_ROW3__I2C2_SDA, "I2C2_SDA"},
    {gpio_dynamic, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 30), MX6DL_PAD_EIM_EB2__I2C2_SCL, "I2C2_SCL"},
    {gpio_dynamic, val_hardware, 0, "BOOTER", IMX_GPIO_NR(1, 3), MX6DL_PAD_GPIO_3__I2C3_SCL, "I2C3_SCL"},
    {gpio_dynamic, val_hardware, 0, "BOOTER", IMX_GPIO_NR(1, 6), MX6DL_PAD_GPIO_6__I2C3_SDA, "I2C3_SDA"},

    // spi
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 6), MX6DL_PAD_KEY_COL0__ECSPI1_SCLK, "ECSPI1_SCLK"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 8), MX6DL_PAD_KEY_COL1__ECSPI1_MISO, "ECSPI1_MISO"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 7), MX6DL_PAD_KEY_ROW0__ECSPI1_MOSI, "ECSPI1_MOSI"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 9), MX6DL_PAD_KEY_ROW1__ECSPI1_SS0, "ECSPI1_SS0"},

    // emmc <sdio4>
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(7, 10), MX6DL_PAD_SD4_CLK__USDHC4_CLK, "USDHC4_CLK"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(7, 9), MX6DL_PAD_SD4_CMD__USDHC4_CMD, "USDHC4_CMD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 8), MX6DL_PAD_SD4_DAT0__USDHC4_DAT0, "USDHC4_DAT0"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 9), MX6DL_PAD_SD4_DAT1__USDHC4_DAT1, "USDHC4_DAT1"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 10), MX6DL_PAD_SD4_DAT2__USDHC4_DAT2, "USDHC4_DAT2"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 11), MX6DL_PAD_SD4_DAT3__USDHC4_DAT3, "USDHC4_DAT3"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 12), MX6DL_PAD_SD4_DAT4__USDHC4_DAT4, "USDHC4_DAT4"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 13), MX6DL_PAD_SD4_DAT5__USDHC4_DAT5, "USDHC4_DAT5"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 14), MX6DL_PAD_SD4_DAT6__USDHC4_DAT6, "USDHC4_DAT6"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(2, 15), MX6DL_PAD_SD4_DAT7__USDHC4_DAT7, "USDHC4_DAT7"},

    // sdio2
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 10), MX6DL_PAD_SD2_CLK__USDHC2_CLK, "USDHC2_CLK"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 11), MX6DL_PAD_SD2_CMD__USDHC2_CMD, "USDHC2_CMD"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 15), MX6DL_PAD_SD2_DAT0__USDHC2_DAT0, "USDHC2_DAT0"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 14), MX6DL_PAD_SD2_DAT1__USDHC2_DAT1, "USDHC2_DAT1"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 13), MX6DL_PAD_SD2_DAT2__USDHC2_DAT2, "USDHC2_DAT2"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 12), MX6DL_PAD_SD2_DAT3__USDHC2_DAT3, "USDHC2_DAT3"},

    // sdio1
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 20), MX6DL_PAD_SD1_CLK__USDHC1_CLK, "USDHC1_CLK"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 18), MX6DL_PAD_SD1_CMD__USDHC1_CMD, "USDHC1_CMD"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 16), MX6DL_PAD_SD1_DAT0__USDHC1_DAT0, "USDHC1_DAT0"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 17), MX6DL_PAD_SD1_DAT1__USDHC1_DAT1, "USDHC1_DAT1"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 19), MX6DL_PAD_SD1_DAT2__USDHC1_DAT2, "USDHC1_DAT2"},
    {gpio_dynamic, val_hardware, 1, "BOOTER", IMX_GPIO_NR(1, 21), MX6DL_PAD_SD1_DAT3__USDHC1_DAT3, "USDHC1_DAT3"},

    // audio
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 22), MX6DL_PAD_CSI0_DAT4__AUDMUX_AUD3_TXC, "AUD3_TXC"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 23), MX6DL_PAD_CSI0_DAT5__AUDMUX_AUD3_TXD, "AUD3_TXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 24), MX6DL_PAD_CSI0_DAT6__AUDMUX_AUD3_TXFS, "AUD3_TXFS"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 25), MX6DL_PAD_CSI0_DAT7__AUDMUX_AUD3_RXD, "AUD3_RXD"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 22), MX6DL_PAD_CSI0_DAT4__AUDMUX_AUD3_TXC, "AUD3_TXC"},

    // display
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 16), MX6DL_PAD_DI0_DISP_CLK__IPU1_DI0_DISP_CLK, "IPU1_DI0_CLK"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 18), MX6DL_PAD_DI0_PIN2__IPU1_DI0_PIN2, "IPU1_DI0_PIN2"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 21), MX6DL_PAD_DISP0_DAT0__IPU1_DISP0_DAT_0, "DISP0_DAT_0"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 22), MX6DL_PAD_DISP0_DAT1__IPU1_DISP0_DAT_1, "DISP0_DAT_1"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 23), MX6DL_PAD_DISP0_DAT2__IPU1_DISP0_DAT_2, "DISP0_DAT_2"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 25), MX6DL_PAD_DISP0_DAT4__IPU1_DISP0_DAT_4, "DISP0_DAT_4"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 28), MX6DL_PAD_DISP0_DAT7__IPU1_DISP0_DAT_7, "DISP0_DAT_7"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 29), MX6DL_PAD_DISP0_DAT8__IPU1_DISP0_DAT_8, "DISP0_DAT_8"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 30), MX6DL_PAD_DISP0_DAT9__IPU1_DISP0_DAT_9, "DISP0_DAT_9"},

    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 30), MX6DL_PAD_DISP0_DAT10__IPU1_DISP0_DAT_10, "DISP0_DAT_10"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(4, 31), MX6DL_PAD_DISP0_DAT11__IPU1_DISP0_DAT_11, "DISP0_DAT_11"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 6), MX6DL_PAD_DISP0_DAT12__IPU1_DISP0_DAT_12, "DISP0_DAT_12"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 8), MX6DL_PAD_DISP0_DAT14__IPU1_DISP0_DAT_14, "DISP0_DAT_14"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 9), MX6DL_PAD_DISP0_DAT15__IPU1_DISP0_DAT_15, "DISP0_DAT_15"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 10), MX6DL_PAD_DISP0_DAT16__IPU1_DISP0_DAT_16, "DISP0_DAT_16"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 11), MX6DL_PAD_DISP0_DAT17__IPU1_DISP0_DAT_17, "DISP0_DAT_17"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 12), MX6DL_PAD_DISP0_DAT18__IPU1_DISP0_DAT_18, "DISP0_DAT_18"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 13), MX6DL_PAD_DISP0_DAT19__IPU1_DISP0_DAT_19, "DISP0_DAT_19"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 14), MX6DL_PAD_DISP0_DAT20__IPU1_DISP0_DAT_20, "DISP0_DAT_20"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 15), MX6DL_PAD_DISP0_DAT21__IPU1_DISP0_DAT_21, "DISP0_DAT_21"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 22), MX6DL_PAD_DISP0_DAT22__IPU1_DISP0_DAT_22, "DISP0_DAT_22"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(5, 17), MX6DL_PAD_DISP0_DAT23__IPU1_DISP0_DAT_23, "DISP0_DAT_23"},

    // USB
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(1, 1), MX6DL_PAD_GPIO_1__USBOTG_ID, "USBOTG_ID"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(3, 21), MX6DL_PAD_EIM_D21__USBOH3_USBOTG_OC, "USBOTG_OC"},
    {gpio_init, val_hardware, 0, "BOOTER", IMX_GPIO_NR(3, 30), MX6DL_PAD_EIM_D30__USBOH3_USBH1_OC, "USBH1_OC"},

    /*
     * gpio
     */
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 29), MX6DL_PAD_DISP0_DAT8__GPIO_4_29, "SD POW"}, // enable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 18), MX6DL_PAD_DI0_PIN2__GPIO_4_18, "FM POW"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 16), MX6DL_PAD_DI0_DISP_CLK__GPIO_4_16, "FM Control, reserved"},
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 21), MX6DL_PAD_DISP0_DAT0__GPIO_4_21, "MIC SW1"}, //
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 22), MX6DL_PAD_DISP0_DAT1__GPIO_4_22, "MIC SW2"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 17), MX6DL_PAD_DI0_PIN15__GPIO_4_17, "BT POW"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 19), MX6DL_PAD_DI0_PIN3__GPIO_4_19, "BT RESET"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 23), MX6DL_PAD_DISP0_DAT2__GPIO_4_23, "GSM RESET"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 25), MX6DL_PAD_DISP0_DAT4__GPIO_4_25, "GSM SLEEP"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 29), MX6DL_PAD_DISP0_DAT8__GPIO_4_29, "SD POW"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(1, 8), MX6DL_PAD_GPIO_8__GPIO_1_8, "USB HUB POW"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(1, 4), MX6DL_PAD_GPIO_4__GPIO_1_4, "UPC POW"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(1, 2), MX6DL_PAD_GPIO_2__GPIO_1_2, "CAMERA POW"}, // disable
    {gpio_dynamic, val_low, 0, "BOOTER", IMX_GPIO_NR(4, 24), MX6DL_PAD_DISP0_DAT3__GPIO_4_24, "TVP5158 POW"}, // disable

    {0},
};
#endif

static u32 crc32table[256];

// make a crc32 table
static void i_make_table32(u32 aPoly) {
    u32 nData, nAccum, i, j;
    for ( i = 0; i < 256; ++i ) {
        nData = i << 24, nAccum = 0;
        for ( j = 0; j < 8; ++j ) {
            if ( ( nData ^ nAccum ) & 0x80000000 )
                nAccum = ( nAccum << 1 ) ^ aPoly;
            else
                nAccum <<= 1;
            nData <<= 1;
        }
        crc32table[i] = nAccum;
    }
}

// calculate crc32
static u32 i_calculate_crc32(const u32 *aData, u32 aSize) {
    u32 nAccum = 0, i;
    static u32 init;
    // 0x04C11DB7 is the standard
    if ( !init ) i_make_table32(0x04C11DB7), ++init;
    for ( i = 0; i < aSize; ++i ) {
        u32 temp = *aData++;
        nAccum = ( nAccum << 8 ) ^ crc32table[(( nAccum >> 24 ) ^ temp) & 0xff];
        nAccum = ( nAccum << 8 ) ^ crc32table[(( nAccum >> 24 ) ^ (temp >> 8)) & 0xff];
        nAccum = ( nAccum << 8 ) ^ crc32table[(( nAccum >> 24 ) ^ (temp >> 16)) & 0xff];
        nAccum = ( nAccum << 8 ) ^ crc32table[( nAccum ^ temp) >> 24];
    }
    return nAccum;
}

#if !__LINUX_APP
long mxc_iomux_really_work(iomux_v3_cfg_t pad)
{
    u32 mux_ctrl_ofs = (pad & MUX_CTRL_OFS_MASK) >> MUX_CTRL_OFS_SHIFT;
    u32 mux_mode = (pad & MUX_MODE_MASK) >> MUX_MODE_SHIFT;
    u32 sel_input_ofs = (pad & MUX_SEL_INPUT_OFS_MASK) >> MUX_SEL_INPUT_OFS_SHIFT;
    u32 sel_input = (pad & MUX_SEL_INPUT_MASK) >> MUX_SEL_INPUT_SHIFT;
    u32 pad_ctrl_ofs = (pad & MUX_PAD_CTRL_OFS_MASK) >> MUX_PAD_CTRL_OFS_SHIFT;
    u32 pad_ctrl = (pad & MUX_PAD_CTRL_MASK) >> MUX_PAD_CTRL_SHIFT;
    void *base = (void *)IOMUXC_BASE_ADDR ;

    if (mux_ctrl_ofs)
        __raw_writel(mux_mode, base + mux_ctrl_ofs);

    if (sel_input_ofs)
        __raw_writel(sel_input, base + sel_input_ofs);

    if (!(pad_ctrl & NO_PAD_CTRL) && pad_ctrl_ofs)
        __raw_writel(pad_ctrl, base + pad_ctrl_ofs);
    return e_ok;
}
#else // linux app
long mxc_iomux_really_work(iomux_v3_cfg_t pad)
{
    return e_ok;
}
#endif

long mxc_iomux_v3_setup_pad(struct gpio_desc_body *desc, int permission)
{
    long ret = e_ok;
    if (!desc || (permission < per_user || permission > per_root)) {
        printf("mxc_iomux_v3_setup_pad parameter error!\n");
        ret = -e_invalid_parameters;
        goto out;
    }

    switch (permission) {
    case per_user:
        if (desc->type != gpio_dynamic) {
            printf("ERROR xxxxxxxxxxxxxxxxxx, user space can't "
                   "pad gpio_init type io\n");
            ret = -e_no_permission;
            goto out;
        }
        break;
    case per_kernel:
        if (desc->type != gpio_dynamic) {
            printf("ERROR xxxxxxxxxxxxxxxxx, in file  use \n");
            ret = -e_no_permission;
            goto out;
        }
        break;
    case per_root:
        {
            static int is_first_time;
            if (is_first_time == 0)
                is_first_time++;
            else {
                printf("ERROR per_root permission not allowed!\n");
                ret = -e_no_permission;
                goto out;
            }
        }
        break;
    }

    if (desc->if_pad_cfg == 0)
        mxc_iomux_really_work(desc->pad_cfg);

out:
    return ret;
}

#if __BOOTER_CODE

long write_gpio_table_to_ddr(void)
{
    struct gpio_desc_skeleton *skep =
        (struct gpio_desc_skeleton *)GPIO_TABLE_ADDR;
    memset(skep, 0, GPIO_TABLE_MAP_SIZE);
    skep->head_flag = 0x524c1234;
    skep->version = 0x1;
    skep->num = ARRAY_SIZE(desc_list);
    memcpy(skep->body, desc_list, sizeof(desc_list));
    skep->checksum =
        i_calculate_crc32((u32 *)skep,
        (sizeof(u32)*4 + sizeof(struct gpio_desc_body)*skep->num)>>2);

    #if __debug__
    printf("struct gpio_desc_skeleton size = %lu\n",
        sizeof(struct gpio_desc_skeleton));
    printf("struct gpio_desc_body size = %lu\n",
        sizeof(struct gpio_desc_body));
    printf("checksum = 0x%x\n", skep->checksum);
    int i, j;
    for (i=1; i<DESC_BODY_NUM; i++) {
        for (j=0; j<sizeof(skep->body[i]); j++)
            if (*((char *)&skep->body[i] + j) != 0)
                printf("%d\n", i);
    }
    #endif

    return e_ok;
}

long ywwh_gpio_init(void)
{
    int permission = per_root;
    int i;

    for (i=0; i<ARRAY_SIZE(desc_list); i++) {
        mxc_iomux_v3_setup_pad(&desc_list[i], permission);
    }

    return e_ok;
}

long ywwh_gpio_manage_func(void)
{
    ywwh_gpio_init();
    write_gpio_table_to_ddr();
    return e_ok;
}

#else // kernel && app

#if __LINUX_APP

static long i_smmap_open(int *pfd, struct gpio_desc_skeleton **sm) {
    printf("open!\n");
    *pfd = open("/dev/mem", O_RDWR|O_SYNC); /* always exist, did not check */
    printf("open1!\n");
    *sm = mmap(NULL, GPIO_TABLE_MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, *pfd, GPIO_TABLE_ADDR);
    printf("open2!\n");
    if (*sm == MAP_FAILED) return -e_no_permission;
    return e_ok;
}

static void i_smmap_close(int fd, struct gpio_desc_skeleton *sm) {
    munmap(sm, GPIO_TABLE_MAP_SIZE);
    close(fd);
}
#endif

static struct gpio_desc_skeleton *descp;
int mfd;

long get_gpio_tbale_from_ddr(void) {
    long ret = e_ok;
    #if __LINUX_KERNEL
    descp = ioremap(GPIO_TABLE_ADDR, _32K);
    if (!descp)
        ret = -e_unbelievable;
    #else // linux app
    if ((ret = i_smmap_open(&mfd, &descp)) < 0)
        goto out;
    #endif

out:
    return ret;
}

long is_gpio_table_valid(void)
{
    if (descp->checksum == i_calculate_crc32((u32 *)descp,
        (GPIO_TABLE_MAP_SIZE - 4) >> 2))
        return 1;
    else {
        printf("headflag = 0x%x\n", descp->head_flag);
        printf("num = %u\n", descp->num);
        return 0;
    }
}

long get_gpio_index_from_table(int gpio_nr, int *index)
{
    long ret = e_ok;
    int i;
    if (!index) {
        ret = -e_invalid_parameters;
        goto out;
    }
    for (i=0; i<descp->num; i++) {
        if (gpio_nr == descp->body[i].gpio_nr)
            break;
    }
    if (i != descp->num)
        *index = i;
    else
        ret = -e_object_not_exist;
out:

    return ret;
}
#endif

//----------------------------------------------------------------------
// -- test --
#if __LINUX_APP

#define IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))

int main()
{
    long ret;
    printf("struct gpio_desc_skeleton size = %lu\n",
        sizeof(struct gpio_desc_skeleton));
    printf("struct gpio_desc_body size = %lu\n",
        sizeof(struct gpio_desc_body));

    if ((ret = get_gpio_tbale_from_ddr()) < 0) {
        printf("get_gpio_tbale_from_ddr failed: %ld!\n", ret);
        return -1;
    }

    if (is_gpio_table_valid())
        printf("crc ok!\n");
    else {
        printf("crc error!\n");
        return -1;
    }

    printf("ok??\n");

    int index;
    if ((ret = get_gpio_index_from_table(IMX_GPIO_NR(4, 18), &index)) < 0) {
        printf("get_gpio_index_from_table failed: %ld!\n", ret);
        return -1;
    }

    printf("ok22??\n");

    if ((ret = mxc_iomux_v3_setup_pad(&descp->body[index], per_root)) < 0) {
        printf("mxc_iomux_v3_setup_pad failed: %ld!\n", ret);
        return -1;
    }

    return 0;
}
#endif





