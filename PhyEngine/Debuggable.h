//
// Created by Bekir Gulestan on 3/17/24.
//

#pragma once

// class for Debuggable objects (PhyMeshes, PhyObjects, etc.)
class Debuggable {
public:
     enum DebugFlags {
        DRAW_BOUNDING_BOX = 2,
        DRAW_NORMALS = 4,
        DRAW_VERTICES = 8,
        DRAW_TRIANGLES = 16,
        DRAW_ROTATION = 32
    };

    // Set Debug Flags
    static void SetDebugFlag(int flags) {
        m_DebugFlags |= flags;
    }

    // has Flags
    // returns the flags
    static bool HasFlags(DebugFlags flag) {
        return m_DebugFlags & flag;
    }


private:
    // Debug Options
    // 2- Draw Bounding Box
    // 4- Draw Normals
    // 8- Draw Vertices
    // 16- Draw Triangles
    // 32- Draw Rotation
    inline static int m_DebugFlags = 0;
};