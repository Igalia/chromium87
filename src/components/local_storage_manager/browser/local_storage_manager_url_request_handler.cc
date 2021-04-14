// Copyright (c) 2020 LG Electronics, Inc.
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

#include "components/local_storage_manager/browser/local_storage_manager_url_request_handler.h"

#include "base/task/post_task.h"
#include "components/local_storage_manager/public/local_storage_manager.h"
#include "content/browser/web_contents/web_contents_impl.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "net/base/net_errors.h"
#include "net/url_request/url_request.h"
#include "services/network/url_loader.h"

namespace content {
LocalStorageManagerUrlRequestHandler::LocalStorageManagerUrlRequestHandler(
    base::WeakPtr<LocalStorageManager> local_storage_manager)
    : local_storage_manager_(local_storage_manager),
      local_storage_manager_valid_(local_storage_manager) {}

void RunOnIOThread(base::OnceClosure callback) {
  base::PostTask(FROM_HERE, {content::BrowserThread::IO}, std::move(callback));
}

void LocalStorageManagerUrlRequestHandler::OnAccessOrigin(
    content::WebContents* web_contents,
    const GURL& origin,
    base::OnceCallback<void()> callback) const {
  if (!local_storage_manager_) {
    std::move(callback).Run();
    return;
  }

  blink::mojom::RendererPreferences* prefs =
      web_contents->GetMutableRendererPrefs();
  local_storage_manager_->OnAccessOrigin(prefs->file_security_origin, origin,
                                         std::move(callback));
}

int LocalStorageManagerUrlRequestHandler::OnBeforeURLRequest(
    net::URLRequest* request,
    net::CompletionOnceCallback& callback,
    GURL* new_url) {
  if (!local_storage_manager_valid_) {
    return net::OK;
  }
  if (!DoesRequestAffectStorage(request)) {
    return net::OK;
  }

  auto callback_on_ui = base::BindOnce(
      &RunOnIOThread,
      base::BindOnce(std::move(callback), static_cast<int>(net::OK)));

  auto* const url_loader = network::URLLoader::ForRequest(*request);
  content::WebContents* web_contents =
      content::WebContentsImpl::FromRenderFrameHostID(
          url_loader->GetProcessId(), url_loader->GetRenderFrameId());

  base::PostTask(
      FROM_HERE, {content::BrowserThread::UI},
      base::BindOnce(&LocalStorageManagerUrlRequestHandler::OnAccessOrigin,
                     this, web_contents, request->url().GetOrigin(),
                     std::move(callback_on_ui)));

  return net::ERR_IO_PENDING;
}

bool LocalStorageManagerUrlRequestHandler::DoesRequestAffectStorage(
    net::URLRequest* request) const {
  return true;
}
}  // namespace content
