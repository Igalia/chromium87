#include "ui/ozone/platform/wayland/agl_shell_desktop_wrapper.h"

#include <agl-shell-desktop-client-protocol.h>

#include "ui/ozone/platform/wayland/host/wayland_connection.h"
#include "ui/ozone/platform/wayland/host/wayland_output_manager.h"
#include "ui/ozone/platform/wayland/host/wayland_output.h"

namespace ui {

AglShellDesktop::AglShellDesktop(WaylandConnection *wconnection, std::string app_id)
  : connection_(wconnection)
  , agl_shell_desktop_(wconnection->ashell_desktop())
  , app_id_(app_id) {}

AglShellDesktop::~AglShellDesktop()
{
  agl_shell_desktop_destroy(agl_shell_desktop_);
}

} // namespace ui
