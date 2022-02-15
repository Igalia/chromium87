// Copyright 2022 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "neva/pal_service/agl/platform_system_delegate_agl.h"

#include "base/files/file_util.h"
#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "base/logging.h"

namespace pal {

namespace agl {

PlatformSystemDelegateAGL::PlatformSystemDelegateAGL() = default;

PlatformSystemDelegateAGL::~PlatformSystemDelegateAGL() = default;

void PlatformSystemDelegateAGL::Initialize() {}

std::string PlatformSystemDelegateAGL::GetCountry() const {
  return std::string("{}");
}

std::string PlatformSystemDelegateAGL::GetDeviceInfoJSON() const {
  return std::string("{}");
}

int PlatformSystemDelegateAGL::GetScreenWidth() const {
  return 0;
}

int PlatformSystemDelegateAGL::GetScreenHeight() const {
  return 0;
}

std::string PlatformSystemDelegateAGL::GetLocale() const {
  return std::string();
}

std::string PlatformSystemDelegateAGL::GetLocaleRegion() const {
  return std::string("US");
}

std::string PlatformSystemDelegateAGL::GetResource(
    const std::string& path) const {
  std::string file_str;
  base::ReadFileToString(base::FilePath(path), &file_str);
  return file_str;
}

bool PlatformSystemDelegateAGL::IsMinimal() const {
  return false;
}

bool PlatformSystemDelegateAGL::GetHightContrast() const {
  return false;
}

}  // namespace agl

}  // namespace pal
