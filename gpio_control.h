
#ifndef __YWWH_GPIO_CONTROL_H_
#define __YWWH_GPIO_CONTROL_H


#if !__BOOTER_CODE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#endif

#define GPIO_TABLE_ADDR 0x4ff00000
//#define GPIO_TABLE_ADDR 0x4FFE8000
#define GPIO_TABLE_MAP_SIZE                    0x00008000

struct gpio_desc_body {
    u8 type;
    u8 default_val;
    u16 if_pad_cfg; // if 0, need pad, if 1 needn't pad
    char who_use[16];
    int gpio_nr;
    iomux_v3_cfg_t pad_cfg;
    char hardware_desc[16];
};

#define DESC_BODY_NUM  (GPIO_TABLE_MAP_SIZE - sizeof(u32)*5)/sizeof(struct gpio_desc_body)

/* the struct is 32K bytes */
struct gpio_desc_skeleton {
    u32 head_flag;
    u32 version;
    u32 num;
    u32 reserved[2];
    struct gpio_desc_body body[DESC_BODY_NUM];
    u32 checksum;
};

/*
 * struct gpio_desc_body::default_val
 *
 *  val_low : output low level
 *  val_high : output high level
 *  val_hardware : use hardware func, not gpio mode.
 */
enum {val_low, val_high, val_hardware};

enum {
    pad_cfg,
    dont_pad_cfg
};

enum {
    per_user,
    per_kernel,
    per_root
};

enum {
    gpio_init,
    gpio_dynamic
};

# if !__BOOTER_CODE

typedef enum {
    e_ok,
    e_invalid_parameters,
    e_insufficient_buffer,
    e_object_not_exist,
    e_insufficient_room,
    e_io_fail,
    e_no_permission,
    e_data_corrupt,
    e_system_busy,
    e_too_many,
    e_not_implement,
    e_not_support,
    e_out_of_ram,
    e_reach_border,
    e_alignment_required,
    e_hardware_required,
    e_unbelievable,
    e_init
}
api_return_code_t;

# endif

long mxc_iomux_v3_setup_pad(struct gpio_desc_body *desc, int permission);

#endif
