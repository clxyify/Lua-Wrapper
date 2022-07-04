# Lua-Wrapper

This is a **Lua Wrapper** which was implemented into a C++ Console compatiable with `lua_State*` for without-uintptr_t usage.

Types like `LUA_TUSERDATA` and `LUA_TFUNCTION` might not always work because the vanillas function bridge was never rewritten.

You can wrap a global, push `globals`, but keep in mind that `-1` must be fixed in order to wrap anything, or make it work.

# How-To-Use

To **Wrap** a new global, use the function `WrapGlobal()` with the second argument as the global name. For instance, use print.

The function `ToWrap` creates a thread that wraps a custom global with user inputted global.

Here are a list of globals used for **Roblox** if you are choosing to switch to uintptr_t.

printidentity game Game workspace Workspace Axes BrickColor CFrame Color3 ColorSequence ColorSequenceKeypoint NumberRange NumberSequence NumberSequenceKeypoint PhysicalProperties Ray Rect Region3 Region3int16 TweenInfo UDim UDim2 Vector2 Vector2int16 Vector3 Vector3int16 Enum Faces Instance math warn typeof type print printidentity ypcall Wait wait delay Delay tick  pcall  spawn  Spawn.
