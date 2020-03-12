#ifndef UI_OZONE_PLATFORM_WAYLAND_AGL_SHELL_DESKTOP_WRAPPER_H_
#define UI_OZONE_PLATFORM_WAYLAND_AGL_SHELL_DESKTOP_WRAPPER_H_

#include <cstdint>
#include <string>

struct agl_shell_desktop;

namespace ui {

class WaylandConnection;

class AglShellDesktop {
public:
  AglShellDesktop(WaylandConnection *connection, std::string app_id);
  ~AglShellDesktop();

  AglShellDesktop(const AglShellDesktop&) = delete;
  AglShellDesktop& operator=(const AglShellDesktop&) = delete;

private:
  WaylandConnection *connection_;
  struct agl_shell_desktop *agl_shell_desktop_;
  std::string app_id_;
};

}  // namespace ui

#endif  // UI_OZONE_PLATFORM_WAYLAND_AGL_SHELL_DESKTOP_WRAPPER_H_
