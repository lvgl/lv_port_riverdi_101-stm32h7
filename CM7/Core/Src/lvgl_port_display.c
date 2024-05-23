/*********************
 *      INCLUDES
 *********************/

#include "lvgl_port_display.h"
#include "main.h"
#include "ltdc.h"
#include "dma2d.h"

#define DIRECT_MODE

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void disp_flush (lv_display_t *, const lv_area_t *, uint8_t *);

#ifndef DIRECT_MODE
static void disp_flush_complete (DMA2D_HandleTypeDef*);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_display_t * disp;

#ifdef DIRECT_MODE
#define LVGL_BUFFER_1_ADDR_AT_SDRAM	(0xD0000000)
#define LVGL_BUFFER_2_ADDR_AT_SDRAM	(0xD0400000)
#else
#define LVGL_BUFFER_1_ADDR_AT_SDRAM	(0xD01F4000)
#define LVGL_BUFFER_2_ADDR_AT_SDRAM	(0xD03E8000)
#endif

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lvgl_display_init (void)
{
	/* display initialization */

	disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
#ifdef DIRECT_MODE
	lv_display_set_buffers(disp, (void*) LVGL_BUFFER_1_ADDR_AT_SDRAM, (void*) LVGL_BUFFER_2_ADDR_AT_SDRAM, MY_DISP_HOR_RES * MY_DISP_VER_RES * 2, LV_DISPLAY_RENDER_MODE_DIRECT);
	HAL_LTDC_SetAddress(&hltdc, (uint32_t)LVGL_BUFFER_2_ADDR_AT_SDRAM, 0);	// start with the second buffer: LVGL will render into the first buffer
#else
	lv_display_set_buffers(disp, (void*) LVGL_BUFFER_1_ADDR_AT_SDRAM, (void*) LVGL_BUFFER_2_ADDR_AT_SDRAM, MY_DISP_HOR_RES * MY_DISP_VER_RES * 2, LV_DISPLAY_RENDER_MODE_PARTIAL);

	/* interrupt callback for DMA2D transfer */
	hdma2d.XferCpltCallback = disp_flush_complete;
#endif

	lv_display_set_flush_cb(disp, disp_flush);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void
disp_flush (lv_display_t * display,
            const lv_area_t * area,
            uint8_t * px_map)
{
#ifdef DIRECT_MODE
	if (lv_display_flush_is_last(disp)) {
		SCB_CleanInvalidateDCache();
		// wait for VSYNC to avoid tearing
		while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
		// swap framebuffers (NOTE: LVGL will swap the buffers in the background, so here we can set the LCD framebuffer to the current LVGL buffer, which has been just completed)
		HAL_LTDC_SetAddress(&hltdc, (uint32_t)(lv_display_get_buf_active(disp)->data), 0);
	}
	lv_display_flush_ready(disp);
#else
  lv_coord_t width = lv_area_get_width(area);
  lv_coord_t height = lv_area_get_height(area);

  SCB_CleanInvalidateDCache();

  DMA2D->CR = 0x0U << DMA2D_CR_MODE_Pos;
  DMA2D->FGPFCCR = DMA2D_INPUT_RGB565;
  DMA2D->FGMAR = (uint32_t)px_map;
  DMA2D->FGOR = 0;
  DMA2D->OPFCCR = DMA2D_OUTPUT_RGB565;
  DMA2D->OMAR = hltdc.LayerCfg[0].FBStartAdress + 2 * \
                (area->y1 * MY_DISP_HOR_RES + area->x1);
  DMA2D->OOR = MY_DISP_HOR_RES - width;
  DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos);
  DMA2D->IFCR = 0x3FU;
  DMA2D->CR |= DMA2D_CR_TCIE;
  DMA2D->CR |= DMA2D_CR_START;
#endif
}

#ifndef DIRECT_MODE

static void
disp_flush_complete (DMA2D_HandleTypeDef *hdma2d)
{
  lv_display_flush_ready(disp);
}

#endif
