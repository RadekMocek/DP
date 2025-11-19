#pragma once

inline constexpr ImVec2 ImVec2Plus(ImVec2 v1, ImVec2 v2) { return ImVec2(v1.x + v2.x, v1.y + v2.y); }

inline constexpr ImVec2 ImVec2PlusC(ImVec2 v1, float c) { return ImVec2(v1.x + c, v1.y + c); }

//inline constexpr ImVec2 ImVec2Round(ImVec2 v1) { return ImVec2(round(v1.x), round(v1.y)); }

inline constexpr bool InRangeInclFloat(float min, float val, float max) { return (min <= val) && (val <= max); }
