/*!
    \file    usbd_transc.h
    \brief   USBD transaction

    \version 2020-07-17, V3.0.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef __USB_TRANSC_H
#define __USB_TRANSC_H

#include "usbd_core.h"

/*!
    \brief      USB transaction configure
    \param[in]  transc: pointer to USB device transaction instance
    \param[in]  buf: transfer data buffer
    \param[in]  len: transfer data length
    \param[in]  count: transfer data counter
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_transc_config (usb_transc *transc, uint8_t *buf, uint16_t len, uint16_t count)
{
    transc->xfer_buf = buf;
    transc->xfer_len = len;
    transc->xfer_count = count;
}

/* function declarations */
/* process USB SETUP transaction */
void _usb_setup_transc (usb_dev *udev, uint8_t ep_num);
/* process USB OUT transaction */
void _usb_out0_transc (usb_dev *udev, uint8_t ep_num);
/* process USB IN transaction */
void _usb_in0_transc (usb_dev *udev, uint8_t ep_num);

#endif /* __USB_TRANSC_H */
