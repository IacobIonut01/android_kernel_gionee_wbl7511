#ifndef BUILD_LK
#include <linux/string.h>
#include <linux/gpio.h>
#include <linux/pinctrl/consumer.h>
#endif

#ifdef BUILD_LK
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#include <platform/mt_i2c.h>
#include <platform/upmu_common.h>
#include "ddp_hal.h"
#else
#endif

#include <mach/mt_pm_ldo.h>	/* hwPowerOn */

#include "lcm_drv.h"

static LCM_UTIL_FUNCS lcm_util = {0};
#define SET_RESET_PIN(v)    								(lcm_util.set_reset_pin((v)))
#define UDELAY(n) 											(lcm_util.udelay(n))
#define MDELAY(n) 											(lcm_util.mdelay(n))

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg											lcm_util.dsi_read_reg()
#define read_reg_v2(cmd, buffer, buffer_size)   			lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util) {
	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
};

static void lcm_get_params(LCM_PARAMS *params) {
	memset(params, 0, sizeof(LCM_PARAMS));
	params->type = 2;
	params->dsi.mode = 2;
	params->dsi.data_format.format = 2;
	params->dsi.PS = 2;
	params->dsi.vertical_sync_active = 2;
	params->dsi.vertical_backporch = 5;
	params->dsi.vertical_frontporch = 9;
	params->dsi.horizontal_backporch = 50;
	params->dsi.eint_disable = 68;
	params->dsi.horizontal_frontporch = 130;
	params->physical_width = 122;
	params->dsi.PLL_CLOCK = 218;
	params->width = 720;
	params->height = 1280;
	params->dsi.LANE_NUM = 4;
	params->dsi.vertical_active_line = 1280;
	params->dsi.horizontal_sync_active = 10;
	params->dsi.horizontal_active_pixel = 720;
	params->dsi.cont_clock = 1;
	params->dsi.esd_check_enable = 1;
	params->dsi.customization_esd_check_enable = 1;
};

static void lcm_init(void) {
	mt_set_gpio_out(146, 1);
	MDELAY(1);
	mt_set_gpio_out(146, 0);
	MDELAY(5);
	mt_set_gpio_out(146, 1);
	MDELAY(120);
	dsi_set_cmdq(0x110500, 1, 1);
	MDELAY(120);
	dsi_set_cmdq(0x20531500, 1, 1);
    dsi_set_cmdq(0x551500, 1, 1);
	dsi_set_cmdq(0x511500, 1, 1);
	MDELAY(5);
	dsi_set_cmdq(0x290500, 1, 1);
	MDELAY(20);
};

static void lcm_suspend(void) {
	dsi_set_cmdq(0x280500, 1, 1);
	MDELAY(40);
	dsi_set_cmdq(0x100500, 1, 1);
	MDELAY(120);
};

static void lcm_resume(void){
	lcm_init();
};

static unsigned int lcm_compare_id(void) {
  return 1;
};

static void lcm_init_power(void) {
	mt_set_gpio_mode(146, 0);
	mt_set_gpio_dir(146, 1);
	mt_set_gpio_out(146, 1);
	hwPowerOn(18, 3300, "LCM_DRV");
	mt_set_gpio_mode(77, 0);
	mt_set_gpio_dir(77, 1);
	mt_set_gpio_out(77, 1);
	MDELAY(20);
};

static void lcm_suspend_power(void) {
	mt_set_gpio_out(146, 1);
	MDELAY(5);
	mt_set_gpio_out(146, 0);
	MDELAY(10);
	mt_set_gpio_mode(77, 0);
	mt_set_gpio_dir(77, 1);
	mt_set_gpio_out(77, 0);
	hwPowerDown(18, "LCM_DRV");
};

static void lcm_resume_power(void) {
	lcm_init_power();
};

LCM_DRIVER s6e8aa4_samsung_lcm_drv = {
  .name = "s6e8aa4_samsung",
  .set_util_funcs = lcm_set_util_funcs,
  .get_params = lcm_get_params,
  .init = lcm_init,
  .suspend = lcm_suspend,
  .resume = lcm_resume,
  .compare_id = lcm_compare_id,
  .init_power = lcm_init_power,
  .resume_power	= lcm_resume_power,
  .suspend_power  = lcm_suspend_power,
};