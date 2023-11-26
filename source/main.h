


// Misc
constexpr u8 NumVerts = 4;
constexpr u8 NumAxis = 3;
constexpr char Version[] = "1.0.1";

// Poly Attributes
constexpr u32 Opaque = (31 << 16);
constexpr u32 Trans = (30 << 16);
constexpr u32 Wireframe = (0 << 16);

// Disp3DCnt
//ph

// Colors
constexpr u16 ColorMissing  = 0b000000000011111; // red
constexpr u16 ColorOverdraw = 0b111110000011111; // neon pink
constexpr u16 ColorMatch    = 0b000001111100000; // green
constexpr u16 ColorTextureER= 0b111110000000000; // blue
constexpr u16 ColorVoid     = 0b000000000000000; // black

// only increment if the actual tests change, (only do on releases?)
constexpr u16 DataVersion = 1;

struct Dataset
{
    s16 Vertices[NumVerts][NumAxis]; // Coordinates of each vertex x,y,z
    u32 PolyAttr; // Polygons attributes for each test
    u32 Disp3DCnt; // 3D Display Control Register bits to enable for each test
    u8 ColorMode; // How many colors to read/record from/to the data file: 0-3 = none, r, rg, rgb
};

constexpr Dataset Dataset[] =
{
// Category: Fill Rules: Primary =============================

  // Sub Cat: Normal ----------------------------------------

    // Left Pos. X-Major - no fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 16, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        1},
    // Left Pos. Diagonal - fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 32, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Left Pos. Y-Major - fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 48, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Left Neg. X-Major - fill
    {{{-32, 32, 0}, {32, 32, 0}, {32, -16, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Left Neg. Diagonal - fill
    {{{-32, 32, 0}, {32, 32, 0}, {32, -32, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Left Neg. Y-Major - fill
    {{{-32, 32, 0}, {32, 32, 0}, {32, -48, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Right Pos. X-Major - fill
    {{{32, -32, 0}, {-32, -32, 0}, {-32, 16, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Right Pos. Diagonal - no fill
    {{{32, -32, 0}, {-32, -32, 0}, {-32, 32, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Right Pos. Y-Major - no fill
    {{{32, -32, 0}, {-32, -32, 0}, {-32, 48, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Right Neg. X-Major - no fill
    {{{32, 32, 0}, {-32, 32, 0}, {-32, -16, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Right Neg. Diagonal - no fill
    {{{32, 32, 0}, {-32, 32, 0}, {-32, -32, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // 12. Right Neg. Y-Major - no fill
    {{{32, 32, 0}, {-32, 32, 0}, {-32, -48, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},

  // Sub Cat: Swapped ---------------------------------------

    // Fill Rules for swapped polygons *generally* follow the same rules as unswapped polygons
    // Key word being generally. You might notice that vertical right slopes aren't being filled. More on that later.

    // Left X-Major
    {{{0, -32, 0}, {0, 32, 0}, {48, 32, 0}, {-32, -16, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Left Y-Major
    {{{0, -48, 0}, {0, 32, 0}, {16, 32, 0}, {-16, -16, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Left Diagonal
    {{{0, -16, 0}, {0, 32, 0}, {16, 32, 0}, {-16, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Right X-Major
    {{{0, -32, 0}, {-1, 32, 0}, {-48, 32, 0}, {32, -16, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Right Y-Major
    {{{0, -48, 0}, {-1, 32, 0}, {-16, 32, 0}, {16, -16, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Right Diagonal
    {{{0, -16, 0}, {-1, 32, 0}, {-16, 32, 0}, {16, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},

  // Sub Cat: Override---------------------------------------
    
    // There are a few things that can force a polygon to fill all edges.

    // Transparency + Blend - Fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 16, 0}, {-512, -512, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    // Transparency + NO BLEND - no fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 16, 0}, {-512, -512, 0}},
        Trans | POLY_CULL_NONE,
        0,
        0},
    // Wireframe - Fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 16, 0}, {-512, -512, 0}},
        Wireframe | POLY_CULL_NONE,
        0,
        1},
    // Anti-Aliasing - Fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 16, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        GL_ANTIALIAS,
        0},
    // Edge Marking - Fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 16, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        GL_OUTLINE,
        0},

// Category: Fill Rules: Unusual =============================

  // Sub Cat: Line Polygon Exception ------------------------

    // Note: My current theory is that this is an explicit fill rule
    // There may be alternative explanations, but this seems to check
    // out with all the other weird behavior this gpu has thrown out.

    // simple line polygon - fill
    {{{-10, -5, 0}, {-10, -5, 0}, {10, 5, 0}, {-512, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // not quite a line polygon - no fill
    {{{-11, -6, 0}, {-10, -5, 0}, {10, 5, 0}, {-512, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // if you can see this you're doing something wrong - no fill
    {{{-2, -1, 0}, {0, 0, 0}, {2, 1, 0}, {-512, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // cursed line polygon 1 - fill, but like, only the line part
    {{{47, 8, 0}, {-46, -27, 0}, {47, 27, 0}, {-46, -27, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // cursed line polygon 2 - see above
    {{{47, 8, 0}, {-46, -27, 0}, {0, 0, 0}, {-46, -27, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // cursed line polygon 3 - fill
    {{{48, 0, 0}, {0, -27, 0}, {-40, -8, 0}, {0, -27, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},

  // Sub Cat: Swapped Vertical Left Glitch ------------------

    // instead of filling the right side when the right side is vertical
    // ...when swapped they uh- check the left side--
    // oops

    // half filled. oh dear.
    {{{-110, -12, 0}, {-110, 24, 0}, {0, 24, 0}, {-140, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // is the slope half filled or half unfilled?
    {{{50, -30, 0}, {-30, 50, 0}, {0, 50, 0}, {0, -20, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // x major slopes are never filled by this glitch, though. - no fill
    {{{50, -30, 0}, {-20, 20, 0}, {0, 20, 0}, {0, -20, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},

  // Sub Cat: Trapezoids ------------------------------------

    // this is a fill rule ...for some reason?
    {{{-25, 10, 0}, {25, 10, 0}, {50, -10, 0}, {-50, -10, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // it applies to clipped vertices too!
    {{{-50, 90, 0}, {50, 90, 0}, {0, 110, 0}, {-512, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // only x major slopes though
    {{{-25, 10, 0}, {25, 10, 0}, {35, -10, 0}, {-45, -10, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // does not work when both the bottom of both slopes have the same x coord
    {{{0, 10, 0}, {0, 10, 0}, {50, -10, 0}, {-50, -10, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // even when their y coord is different
    {{{0, 5, 0}, {0, 10, 0}, {50, -10, 0}, {-50, -10, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},

// Category: Vertical Right Edge Shift =======================

    // vertical right edges are shifted left by one pixel

    // square
    {{{-32, -32, 0}, {-32, 32, 0}, {32, 32, 0}, {32, -32, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    // vertical 0 wide line polygon, right edges are *not* shifted left
    {{{0, -32, 0}, {0, 32, 0}, {0, 32, 0}, {0, -32, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    // vertical 1 wide line polygon, right edges are shifted left
    {{{0, -32, 0}, {0, 32, 0}, {1, 32, 0}, {1, -32, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    // but not when touching the edge of the screen
    // todo: test if it is shifted left when drawn oob? cause im pretty sure it does matter
    {{{-128, -32, 0}, {-128, 32, 0}, {-127, 32, 0}, {-127, -32, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    // swapped polygon 1
    {{{-32, -32, 0}, {0, -32, 0}, {0, 32, 0}, {32, 32, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    // swapped polygon 1 reversed
    {{{32, -32, 0}, {0, -32, 0}, {0, 32, 0}, {-32, 32, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    // idk what this one even is
    {{{-32, -32, 0}, {-32, 32, 0}, {32, 0, 0}, {-32, 0, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    // still dont know
    {{{32, -32, 0}, {32, 32, 0}, {-32, 0, 0}, {32, 0, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},
    {{{72, 45, 0}, {-63, 65}, {65, 65, 0}, {65, -63, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},

// Category: Anti-Aliasing ===================================

  // Sub Cat: Swapped Vertical Edge Glitch ------------------

    // yeah they also messed this up, im guessing they invert the aa alpha for swapped polygons to make them work properly?
    // ...even though vertical edges shouldn't be

    // swapped polygons are very glitchy, it turns out
    {{{-32, -32, 0}, {0, -32, 0}, {0, 32, 0}, {32, 32, 0}},
        Opaque | POLY_CULL_NONE,
        GL_ANTIALIAS,
        0},
    // see above
    {{{32, -32, 0}, {0, -32, 0}, {0, 32, 0}, {-32, 32, 0}},
        Opaque | POLY_CULL_NONE,
        GL_ANTIALIAS,
        0},
    // edge case within an edge case combined with an edge case
    {{{-110, -12, 0}, {-110, 24, 0}, {0, 24, 0}, {-140, 0, 0}},
        Opaque | POLY_CULL_NONE,
        GL_ANTIALIAS,
        0},

// Category: Clipping ========================================

  // Sub Cat: Horizontal Line Polygons and Clipping ---------

    // todo: interpolation also behaves wonkily here, implement a way to test for/showcase this?
    // ...maybe wait until interpolation under clipping is better understood, though
    // todo2: also need to test if this applies with z clipping as well... in theory it should...?

    // Horizontal line polygons always render 1-4,
    {{{-32, 0, 0}, {0, 0, 0}, {48, 0, 0}, {32, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // 1-2,
    {{{-32, 0, 0}, {32, 0, 0}, {48, 0, 0}, {0, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // or 2-4. 3 is never rendered
    {{{0, 0, 0}, {-32, 0, 0}, {48, 0, 0}, {32, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Until the first vertex gets clipped.... (1-2)
    {{{-128, 0, 0}, {-32, 0, 0}, {32, 0, 0}, {48, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Then things start to get interesting... (2-3)
    {{{-128, 0, 0}, {-128, 0, 0}, {32, 0, 0}, {48, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // 2-3
    {{{-128, 0, 0}, {-128, 0, 0}, {32, 0, 0}, {48, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // 3-4
    {{{-128, 0, 0}, {-128, 0, 0}, {-128, 0, 0}, {48, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // 4th vertex being clipped might complicate things, might not, probably depends on implementation of clipping (1-2)
    {{{-128, 0, 0}, {-32, 0, 0}, {32, 0, 0}, {-128, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    //  2-3
    {{{-128, 0, 0}, {-128, 0, 0}, {32, 0, 0}, {-128, 0, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
        
// Catgory: Misc =============================================
 
    // left side has precedence over right side
    // Just an innocent square c:
    {{{-32, -32, 0}, {-32, 32, 0}, {32, 33, 0}, {32, -32, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // Evil square
    {{{-32, -32, 0}, {-32, 33, 0}, {32, 32, 0}, {32, -32, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    // pointer never goes backwards
    {{{-30, -14, 0}, {20, 15, 0}, {52, 15, 0}, {-51, 10, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
    //these slopes are identical, but render differently due to rounding.
    {{{-64,0, 0}, {64, -41, 0}, {64, 41, 0}, {-512, 0, 0}},
        Trans | POLY_CULL_NONE,
        GL_BLEND,
        0},

  // Sub Cat: Second Vertex is Weird ------------------------

    // Second vertex behaves differently vs others for w/e reason.

    // should behave normally
    {{{-32, -32, 0}, {-1, -1, 0}, {32, 32, 0}, {32, -31, 0}},
        Wireframe | POLY_CULL_NONE,
        0,
        0},
    // should behave normally ...or not?
    {{{-32, -32, 0}, {0, 0, 0}, {32, 32, 0}, {32, -31, 0}},
        Wireframe | POLY_CULL_NONE,
        0,
        0},
    // should glitch out, behaving as if it was swapped
    {{{-32, -32, 0}, {1, -1, 0}, {32, 32, 0}, {32, -31, 0}},
        Wireframe | POLY_CULL_NONE,
        0,
        0},
    // however only the second vertex should cause this behavior
    {{{1, -1, 0}, {32, 32, 0}, {32, -32, 0}, {-32, -31, 0}},
        Wireframe | POLY_CULL_NONE,
        0,
        0},
    // should also behave normally
    {{{-32, -32, 0}, {-32, -32, 0}, {32, 32, 0}, {32, -31, 0}},
        Wireframe | POLY_CULL_NONE,
        0,
        0},
    // not sure if this one would behave weirdly tbh? idk im just gonna throw it in for the heck of it. might get removed.
    {{{-2, -1, 0}, {0, 0, 0}, {-2, -1, 0}, {2, 1, 0}},
        Wireframe | POLY_CULL_NONE,
        0,
        0},
};

constexpr int NumEntries = sizeof(Dataset) / sizeof(Dataset[0]);
