/*
 * This file is part of the Serial Flash Universal Driver Library.
 *
 * Copyright (c) 2016, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2016-04-23
 */

#include <sfud.h>
#include <stdarg.h>
#include <stdio.h>
#include <n32l40x.h>

typedef struct {
    SPI_Module *spix;
    GPIO_Module *cs_gpiox;
    uint16_t cs_gpio_pin;
} spi_user_data, *spi_user_data_t;

static char log_buf[256];

void sfud_log_debug(const char *file, const long line, const char *format, ...);

static void rcc_configuration(spi_user_data_t spi) {
    if (spi->spix == SPI1) {
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE);
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    }else if (spi->spix == SPI2) {
        /* you can add SPI2 code here */
    }
}

static void gpio_configuration(spi_user_data_t spi) {
    GPIO_InitType GPIO_InitStructure;

    if (spi->spix == SPI1) {
		GPIO_InitStruct(&GPIO_InitStructure);
		
		/* CS: PB2 */
        GPIO_InitStructure.Pin = GPIO_PIN_2;
		GPIO_InitStructure.GPIO_Slew_Rate = GPIO_Slew_Rate_High;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
        GPIO_SetBits(GPIOB, GPIO_PIN_2);
		
		/* SCK:PB3  MISO:PB4  MOSI:PB5 */
        GPIO_InitStructure.Pin = GPIO_PIN_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_SPI1;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
		
		GPIO_InitStructure.Pin = GPIO_PIN_4;
		GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_SPI1;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
		
		GPIO_InitStructure.Pin = GPIO_PIN_5;
		GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI1;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
		
    } else if (spi->spix == SPI2) {
        /* you can add SPI2 code here */
    }
}

static void spi_configuration(spi_user_data_t spi) {
    SPI_InitType SPI_InitStructure;

	SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;  
	SPI_InitStructure.SpiMode = SPI_MODE_MASTER;                      
	SPI_InitStructure.DataLen = SPI_DATA_SIZE_8BITS;	    
	SPI_InitStructure.CLKPOL = SPI_CLKPOL_LOW;			
	SPI_InitStructure.CLKPHA = SPI_CLKPHA_FIRST_EDGE;
	SPI_InitStructure.NSS = SPI_NSS_SOFT;		                    
	SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;	 
	SPI_InitStructure.FirstBit = SPI_FB_MSB;                        
	SPI_InitStructure.CRCPoly = 7;
	SPI_Init(SPI1, &SPI_InitStructure);

    SPI_I2S_DeInit(spi->spix);
    SPI_Init(spi->spix, &SPI_InitStructure);

	SPI_EnableCalculateCrc(spi->spix, DISABLE);
    SPI_Enable(spi->spix, ENABLE);
}

static void spi_lock(const sfud_spi *spi) {
    __disable_irq();
}

static void spi_unlock(const sfud_spi *spi) {
    __enable_irq();
}

/**
 * SPI write data then read data
 */
static sfud_err spi_write_read(const sfud_spi *spi, const uint8_t *write_buf, size_t write_size, uint8_t *read_buf,
        size_t read_size) {
    sfud_err result = SFUD_SUCCESS;
    uint8_t send_data, read_data;
    spi_user_data_t spi_dev = (spi_user_data_t) spi->user_data;

    if (write_size) {
        SFUD_ASSERT(write_buf);
    }
    if (read_size) {
        SFUD_ASSERT(read_buf);
    }

    GPIO_ResetBits(spi_dev->cs_gpiox, spi_dev->cs_gpio_pin);
    for (size_t i = 0, retry_times; i < write_size + read_size; i++) {
        if (i < write_size) {
            send_data = *write_buf++;
        } else {
            send_data = SFUD_DUMMY_DATA;
        }
        retry_times = 1000;
        while (SPI_I2S_GetStatus(spi_dev->spix, SPI_I2S_TE_FLAG) == RESET) {
            SFUD_RETRY_PROCESS(NULL, retry_times, result);
        }
        if (result != SFUD_SUCCESS) {
            goto exit;
        }
        SPI_I2S_TransmitData(spi_dev->spix, send_data);
        retry_times = 1000;
        while (SPI_I2S_GetStatus(spi_dev->spix, SPI_I2S_RNE_FLAG) == RESET) {
            SFUD_RETRY_PROCESS(NULL, retry_times, result);
        }
        if (result != SFUD_SUCCESS) {
            goto exit;
        }
        read_data = SPI_I2S_ReceiveData(spi_dev->spix);
        if (i >= write_size) {
            *read_buf++ = read_data;
        }
    }

exit:
    GPIO_SetBits(spi_dev->cs_gpiox, spi_dev->cs_gpio_pin);

    return result;
}

/* about 100 microsecond delay */
static void retry_delay_100us(void) {
    uint32_t delay = 120;
    while(delay--);
}

static spi_user_data spix = { .spix = SPI1, .cs_gpiox = GPIOB, .cs_gpio_pin = GPIO_PIN_2 };
sfud_err sfud_spi_port_init(sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;

    switch (flash->index) {
    case SFUD_W25Q128_DEVICE_INDEX: {
        rcc_configuration(&spix);
        gpio_configuration(&spix);
        spi_configuration(&spix);
        flash->spi.wr = spi_write_read;
        flash->spi.lock = spi_lock;
        flash->spi.unlock = spi_unlock;
        flash->spi.user_data = &spix;
        /* about 100 microsecond delay */
        flash->retry.delay = retry_delay_100us;
        /* adout 60 seconds timeout */
        flash->retry.times = 60 * 10000;

        break;
    }
    }

    return result;
}

void sfud_printf(const char *format, ...)
{
	;
}

/**
 * This function is print debug info.
 *
 * @param file the file which has call this function
 * @param line the line number which has call this function
 * @param format output format
 * @param ... args
 */
void sfud_log_debug(const char *file, const long line, const char *format, ...) {
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);
    sfud_printf("[SFUD](%s:%ld) ", file, line);
    /* must use vprintf to print */
    vsnprintf(log_buf, sizeof(log_buf), format, args);
    sfud_printf("%s\r\n", log_buf);
    va_end(args);
}

/**
 * This function is print routine info.
 *
 * @param format output format
 * @param ... args
 */
void sfud_log_info(const char *format, ...) {
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);
    sfud_printf("[SFUD]");
    /* must use vprintf to print */
    vsnprintf(log_buf, sizeof(log_buf), format, args);
    sfud_printf("%s\r\n", log_buf);
    va_end(args);
}
