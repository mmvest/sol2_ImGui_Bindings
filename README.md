# sol2 Lua bindings for Dear ImGui

This repository has been updated from the original fork on 7/24/2024 to commit of Dear ImGui 271910e3495e686a252b4b85369dec0605ba0d20 on the docking branch (version 1.91.0 WIP).


## Notes
- This uses the latest sol2 version (as of July 2020), the repo is located at https://github.com/ThePhD/sol2/.
- These bindings are based on one of the latest version of Dear ImGui Docking Branch. Comment what you don't need or breaks.
- I've hid the U32 related function with a define (SOL_IMGUI_USE_COLOR_U32), if you wish to use these, define that!

## How to Use
```cpp
  // Call this function!
  sol_ImGui::Init(lua); // lua being your sol::state
```

## Documentation
You can find all the supported functions and overloads in meta.lua. This file is set up to provide autocomplete, if the right VSCode plugin is used.

## Major updates

- Language in this README and elsewhere has been updated to reflect the naming conventions of the Dear ImGui project, Namely, calling it "Dear ImGui" instead of "ImGui".
- Update to newer version of Dear ImGui, including removing deprecated functions, adding new functions, and updating parameters.
- Update to use the versions of InputText* from imgui_stdlib.h that allow for std::string as a direct input and automatic resizing. No reason to pass a buffersize from Lua, which manages string sizes itself.
- Creating the meta.lua file for dedicated documentation, intellisence, and static analysis.
- CUSTOM_IMGUI macro and its contents have been removed.
- Built a custom macro to help maintain enumerations. Its designed to make using multi-select easy to update an entire enum in one go.
- Re-ordered enums to match imgui.h