# sol2 Lua bindings for Dear ImGui

`sol2_ImGui_Bindings`is a single-header set of Lua bindings for Dear ImGui built on top of sol2.

## What has changed

These are the major differences between `sol_ImGui.h` and the original:
- Added `#include "imgui_stdlib.h"` so Lua can pass `std::string` to `InputText*` without manual buffer sizes.
- The header now expects a C++17 compiler (`std::is_same_v`).
- `Init` used to only supported `sol::state&` in `InitEnums()`/`Init()`. It now supports templates `InitEnums()`, `InitUserTypes()`, and `Init()` to accept `sol::state&` or `sol::state_view&`.
- `BeginChild` now uses `ImGuiChildFlags` (not the old `border: bool` parameter), and I expose `ImGuiChildFlags` to Lua.
- Docking-related pieces are guarded with `#ifdef IMGUI_DOCKING` so the header can still compile against non-docking builds.
- Support for `GetWindowDrawList()` and `ImDrawList` added so Lua can actually draw via the draw list API.
- `Image(textureID, width, height)` is now supported.
- Swapped input text handling from `buf_size` for `InputText*` to now use ImGui's `imgui_stdlib` overloads so Lua doesn't need to guess buffer sizes.
- Removed `CUSTOM_IMGUI` and U32-color helper macros.

## Requirements

- Dear ImGui
- sol2

## How I use it

In C++ I call `sol_ImGui::Init(...)` when I set up Lua:

```cpp
    lua_state = lua_open();

    luaL_openlibs(lua_state);

    sol::state_view sol_state_view(lua_state);

    // Initialize ImGui Lua bindings
    sol_ImGui::Init(sol_state_view);
```

Then in Lua I set something up like:
```lua
if ImGui.Begin("Hello, UiForge!", true, ImGuiWindowFlags.MenuBar) then
  -- Do lua ImGui things here!
end

--end the window
ImGui.End()
```

## Documentation / autocomplete

`meta.lua` is the list of functions that is exposed and it provides intellisense with something to work with when working in lua. It is definitely missing some overloads and function signatures, but works for the most part. Don't require meta.lua in your lua scripts... that'll probably just break everything.

## Unsupported pieces

As a final note, not everything in Dear ImGui is bound here. Some wrappers still say `UNSUPPORTED` in the header and will likely stay that way unless I end up needing them for my personal projects. There are some libraries that provide significantly more comprehensive lua bindings, but these seem to get the job done for me.
