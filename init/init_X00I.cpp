/*
   Copyright (c) 2017, The CyanogenMod Project
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "log.h"
#include "property_service.h"
#include "util.h"
#include "vendor_init.h"

#define DRV_INFO "/sys/devices/platform/fp_drv/fp_drv_info"

static void fp_prop()
{
    int fd = open(DRV_INFO, 0);
    if (fd <= 0) {
        ERROR("Cannot open: %s", DRV_INFO);
    }

    char fp_drv[50];
    memset(fp_drv, 0, sizeof(fp_drv));
    int result = read(fd, fp_drv, sizeof(fp_drv));

    if (strcmp(fp_drv, "focal_fp") == 0) {
        property_set("persist.sys.fp.goodix", "0");
    } else if (strcmp(fp_drv, "goodix_fp") == 0) {
        property_set("persist.sys.fp.goodix", "1");
    } else if (strcmp(fp_drv, "silead_fp_dev") == 0) {
        ERROR("%s: Silead fpsvcd fingerprint sensor is unsupported", __func__);
    } else {
        ERROR("%s: Fingerprint sensor is unsupported", __func__);
    }
    close(fd);
}

void vendor_load_properties()
{
    fp_prop();
}

