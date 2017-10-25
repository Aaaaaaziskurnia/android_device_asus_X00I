#
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

$(call inherit-product, device/asus/X00I/full_X00I.mk)

# Inherit some common LineageOS stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := lineage_X00I
BOARD_VENDOR := asus

PRODUCT_GMS_CLIENTID_BASE := android-asus

PRODUCT_BUILD_PROP_OVERRIDES += \
   BUILD_FINGERPRINT="asus/WW_Phone/ASUS_X00ID:7.1.1/NMF26F/14.2016.1708.156-20170908:user/release-keys" \
   PRIVATE_BUILD_DESC="msm8937_64-user 7.1.1 NMF26F 14.2016.1708.156-20170908 release-keys"
