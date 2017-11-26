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

#include <fcntl.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

char const *heapstartsize;
char const *heapgrowthlimit;
char const *heapsize;
char const *heapminfree;
char const *heapmaxfree;
char const *large_cache_height;

static void init_alarm_boot_properties()
{
    int boot_reason;
    FILE *fp;

    fp = fopen("/proc/sys/kernel/boot_reason", "r");
    fscanf(fp, "%d", &boot_reason);
    fclose(fp);

    /*
     * Setup ro.alarm_boot value to true when it is RTC triggered boot up
     * For existing PMIC chips, the following mapping applies
     * for the value of boot_reason:
     *
     * 0 -> unknown
     * 1 -> hard reset
     * 2 -> sudden momentary power loss (SMPL)
     * 3 -> real time clock (RTC)
     * 4 -> DC charger inserted
     * 5 -> USB charger inserted
     * 6 -> PON1 pin toggled (for secondary PMICs)
     * 7 -> CBLPWR_N pin toggled (for external power supply)
     * 8 -> KPDPWR_N pin toggled (power key pressed)
     */
     if (boot_reason == 3) {
        property_set("ro.alarm_boot", "true");
     } else {
        property_set("ro.alarm_boot", "false");
     }
}

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void vendor_load_properties()
{
    std::string project = property_get("ro.boot.platform_boardid");
    property_set("ro.product.name", "WW_Phone");
    if (project == "MSM8937") {
        property_override("ro.build.product", "msm8937_64");
        property_override("ro.build.description", "msm8937_64-user 7.1.1 NMF26F 14.2016.1709.160-20171009 release-keys");
        property_override("ro.build.fingerprint", "asus/WW_Phone/ASUS_X00ID:7.1.1/NMF26F/14.2016.1709.160-20171009:user/release-keys");
        property_override("ro.product.device", "ASUS_X00ID");
        property_override("ro.product.model", "ASUS_X00ID");
        property_set("ro.product.carrier", "US-ASUS_X00ID-WW_Phone");
        property_set("ro.asus.project.name", "ZC554KL");
        property_set("ro.build.csc.version", "WW_ZC554KL_14.2016.1709.160-20171009");
    } else if (project == "MSM8917") {
        property_override("ro.build.product", "msm8937_64");
        property_override("ro.build.description", "msm8937_64-user 7.1.1 NMF26F 14.2016.1709.160-20171009 release-keys");
        property_override("ro.build.fingerprint", "asus/WW_Phone/ASUS_X00ID:7.1.1/NMF26F/14.2016.1709.160-20171009:user/release-keys");
        property_override("ro.product.device", "ASUS_X00ID");
        property_override("ro.product.model", "ASUS_X00ID");
        property_set("ro.product.carrier", "US-ASUS_X00ID-WW_Phone");
        property_set("ro.asus.project.name", "ZC554KL");
        property_set("ro.build.csc.version", "WW_ZC554KL_14.2016.1709.160-20171009");
    }
}
