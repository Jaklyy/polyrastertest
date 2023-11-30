


// Misc
constexpr u8 NumVerts = 4;
constexpr u8 NumAxis = 3;
constexpr char Version[] = "1.0.2";

// Poly Attributes
constexpr u32 Opaque = (31 << 16);
constexpr u32 Wireframe = (0 << 16);
constexpr u32 Trans(u8 Opacity)
{
    return Opacity << 16;
}
constexpr u32 PolyID(u8 ID)
{
    return ID << 24;
}

// Disp3DCnt
//ph

// Colors
constexpr u16 ColorStock    = 0b111111111111111; // white
constexpr u16 ColorMissing  = 0b000000000011111; // red
constexpr u16 ColorOverdraw = 0b111110000011111; // neon pink
constexpr u16 ColorMatch    = 0b000001111100000; // green
constexpr u16 ColorWrongTex = 0b111110000000000; // blue
constexpr u16 ColorVoid     = 0b000000000000000; // black

// only increment if the actual tests change, (only do on releases?)
constexpr u16 DataVersion = 2;

struct TestData
{
    s16 Vertices[NumVerts][NumAxis]; // Coordinates of each vertex x,y,z
    u32 PolyAttr = Opaque | POLY_CULL_NONE; // Polygons attributes for each test
    u16 VertexColors[4] = {ColorStock, ColorStock, ColorStock, ColorStock}; // colors for each vertex
    u32 Disp3DCnt = 0; // 3D Display Control Register bits to enable for each test
    u32 Viewport = (0<<0) + (0<<8) + (255<<16) + (191<<24); // Viewport to use
    m4x4 Projection = {131586, 0, 0, 0, // Matrix to use for projection
                       0, -175677, 0, 0,
                       0, 0, -1024, 0,
                       16, 21, -4096, 4096};
    u16 OutlineColors[8] = {ColorStock}; // specify colors for edgemarking, 0 defaults to white, and 1-7 black
    u8 RearID = 63;
    u16 RearDepth = GL_MAX_DEPTH;
    u8 ColorMode = 0; // How many colors to read/record from/to the data file: 0-3 = none, r, rg, rgb
    u16 ExtendedTestData = 0; // Determines which and whether to use an extended test mode. 0 = none, if greater use the value - 1 to determine which exttestdata to use.
};

struct Polygon
{
    s16 Vertices[NumVerts][NumAxis];
    u32 PolyAttr = Opaque | POLY_CULL_NONE;
    u16 VertexColors[4] = {ColorStock, ColorStock, ColorStock, ColorStock};
};

struct ExtTestData
{
    u32 NumPolygons = 1;
    Polygon Polygons[1];
};

constexpr TestData Tests[] =
{
// Category: Fill Rules: Primary =============================

  // Sub Cat: Normal ----------------------------------------
        //{.Vertices = {{-32}}}
    // Left Pos. X-Major - no fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}}},
    // Left Pos. Diagonal - fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 32}, {-512}}},
    // Left Pos. Y-Major - fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 48}, {-512}}},
    // Left Neg. X-Major - fill
        {.Vertices = {{-32, 32}, {32, 32}, {32, -16}, {-512}}},
    // Left Neg. Diagonal - fill
        {.Vertices = {{-32, 32}, {32, 32}, {32, -32}, {-512}}},
    // Left Neg. Y-Major - fill
        {.Vertices = {{-32, 32}, {32, 32}, {32, -48}, {-512}}},
    // Right Pos. X-Major - fill
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 16}, {-512}}},
    // Right Pos. Diagonal - no fill
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}}},
    // Right Pos. Y-Major - no fill
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 48}, {-512}}},
    // Right Neg. X-Major - no fill
        {.Vertices = {{32, 32}, {-32, 32}, {-32, -16}, {-512}}},
    // Right Neg. Diagonal - no fill
        {.Vertices = {{32, 32}, {-32, 32}, {-32, -32}, {-512}}},
    // Right Neg. Y-Major - no fill
        {.Vertices = {{32, 32}, {-32, 32}, {-32, -48}, {-512}}},

  // Sub Cat: Swapped ---------------------------------------

    // Fill Rules for swapped polygons *generally* follow the same rules as unswapped polygons
    // Key word being generally. You might notice that vertical right slopes aren't being filled. More on that later.

    // Left X-Major - top = fill, bot = no fill
        {.Vertices = {{0, -32}, {0, 32}, {48, 32}, {-32, -16}}},
    // Left Y-Major - fill
        {.Vertices = {{0, -48}, {0, 32}, {16, 32}, {-16, -16}}},
    // Left Diagonal - fill
        {.Vertices = {{0, -16}, {0, 32}, {16, 32}, {-16, 0}}},
    // Right X-Major - top = fill, bot = no fill
        {.Vertices = {{0, -32}, {-1, 32}, {-48, 32}, {32, -16}}},
    // Right Y-Major - no fill
        {.Vertices = {{0, -48}, {-1, 32}, {-16, 32}, {16, -16}}},
    // Right Diagonal - no fill
        {.Vertices = {{0, -16}, {-1, 32}, {-16, 32}, {16, 0}}},

  // Sub Cat: Override---------------------------------------
    
    // There are a few things that can force a polygon to fill all edges.

    // Transparency + Blend - Fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // Transparency + NO BLEND - no fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE},
    // Wireframe - Fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .PolyAttr = Wireframe | POLY_CULL_NONE},
    // Anti-Aliasing - Fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .Disp3DCnt = GL_ANTIALIAS},
    // Edge Marking - Fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .Disp3DCnt = GL_OUTLINE},

// Category: Fill Rules: Unusual =============================

  // Sub Cat: Line Polygon Exception ------------------------

    // Note: My current theory is that this is an explicit fill rule
    // There may be alternative explanations, but this seems to check
    // out with all the other weird behavior this gpu has thrown out.

    // simple line polygon - fill
        {.Vertices = {{-10, -5}, {-10, -5}, {10, 5}, {-512}}},
    // not quite a line polygon - no fill
        {.Vertices = {{-11, -6}, {-10, -5}, {10, 5}, {-512}}},
    // if you can see this you're doing something wrong - no fill
        {.Vertices = {{-2, -1}, {0, 0}, {2, 1}, {-512}}},
    // cursed line polygon 1 - fill, but like, only the line part
        {.Vertices = {{47, 8}, {-46, -27}, {47, 27}, {-46, -27}}},
    // cursed line polygon 2 - see above
        {.Vertices = {{47, 8}, {-46, -27}, {0, 0}, {-46, -27}}},
    // cursed line polygon 3 - fill
        {.Vertices = {{48, 0}, {0, -27}, {-40, -8}, {0, -27}}},

  // Sub Cat: Swapped Vertical Left Glitch ------------------

    // instead of filling the right side when the right side is vertical
    // ...when swapped they uh- check the left side--
    // oops

    // half filled. oh dear.
        {.Vertices = {{-110, -12}, {-110, 24}, {0, 24}, {-140, 0}}},
    // is the slope half filled or half unfilled?
        {.Vertices = {{50, -30}, {-30, 50}, {0, 50}, {0, -20}}},
    // x major slopes are never filled by this glitch, though. - no fill
        {.Vertices = {{50, -30}, {-20, 20}, {0, 20}, {0, -20}}},

  // Sub Cat: Trapezoids ------------------------------------

    // this is a fill rule ...for some reason?
        {.Vertices = {{-25, 10}, {25, 10}, {50, -10}, {-50, -10}}},
    // it applies to clipped vertices too!
        {.Vertices = {{-50, 90}, {50, 90}, {0, 110}, {-512, 0}}},
    // only x major slopes though
        {.Vertices = {{-25, 10}, {25, 10}, {35, -10}, {-45, -10}}},
    // does not work when both the bottom of both slopes have the same x coord
        {.Vertices = {{0, 10}, {0, 10}, {50, -10}, {-50, -10}}},
    // even when their y coord is different
        {.Vertices = {{0, 5}, {0, 10}, {50, -10}, {-50, -10}}},

  // Sub Cat: The Curse of Edge Marking ---------------------

    // Edge Marking + overlapping edges - I-- what?
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .PolyAttr = Opaque | POLY_CULL_NONE | PolyID(1),
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000001111100000},
        .ColorMode = 2,
        .ExtendedTestData = 1},
    // Mirrored horizontally? - 
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 16}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000001111100000},
        .ColorMode = 2,
        .ExtendedTestData = 5},
    // oook, what if the fill rules are swapped? - No
        {.Vertices = {{-32, 32}, {32, 32}, {32, -16}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000001111100000},
        .ColorMode = 2,
        .ExtendedTestData = 2},
    // what if they're both supposed to fill? - No
        {.Vertices = {{-32, 32}, {32, 32}, {32, -16}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000001111100000},
        .ColorMode = 2,
        .ExtendedTestData = 3},
    // what about neither? - No
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000001111100000},
        .ColorMode = 2,
        .ExtendedTestData = 4},
    // Bottom? - Yes
        {.Vertices = {{-32, -32}, {32, -32}, {32, -64}, {-32, -64}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000001111100000},
        .ColorMode = 2,
        .ExtendedTestData = 6},
    // Top? - No...?
        {.Vertices = {{-32, 32}, {32, 32}, {32, 64}, {-32, 64}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000001111100000},
        .ColorMode = 2,
        .ExtendedTestData = 6},

// Category: Vertical Right Edge Shift =======================

    // vertical right edges are shifted left by one pixel

    // square
        {.Vertices = {{-32, -32}, {-32, 32}, {32, 32}, {32, -32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // vertical 0 wide line polygon, right edges are *not* shifted left
        {.Vertices = {{0, -32}, {0, 32}, {0, 32}, {0, -32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // vertical 1 wide line polygon, right edges are shifted left
        {.Vertices = {{0, -32}, {0, 32}, {1, 32}, {1, -32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // but not when touching the edge of the screen
    // todo: test if it is shifted left when drawn oob? cause im pretty sure it does matter
        {.Vertices = {{-128, -32}, {-128, 32}, {-127, 32}, {-127, -32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // swapped polygon 1
        {.Vertices = {{-32, -32}, {0, -32}, {0, 32}, {32, 32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // swapped polygon 1 reversed
        {.Vertices = {{32, -32}, {0, -32}, {0, 32}, {-32, 32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // idk what this one even is
        {.Vertices = {{-32, -32}, {-32, 32}, {32, 0}, {-32, 0}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // still dont know
        {.Vertices = {{32, -32}, {32, 32}, {-32, 0}, {32, 0}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},
    // Do note: it isn't always the case that a 0 wide span wont be shifted left.
        {.Vertices = {{72, 45}, {-63, 65}, {65, 65}, {65, -63}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},

// Category: Anti-Aliasing ===================================

  //Sub Cat: General Anti-Aliasing---------------------------

    // Todo

  // Sub Cat: Swapped Vertical Edge Glitch ------------------

    // yeah they also messed this up, im guessing they invert the aa alpha for swapped polygons to make them work properly?
    // ...even though vertical edges shouldn't be

    // swapped polygons are very glitchy, it turns out
        {.Vertices = {{-32, -32}, {0, -32}, {0, 32}, {32, 32}},
        .Disp3DCnt = GL_ANTIALIAS},
    // see above
        {.Vertices = {{32, -32}, {0, -32}, {0, 32}, {-32, 32}},
        .Disp3DCnt = GL_ANTIALIAS},
    // edge case within an edge case combined with an edge case
        {.Vertices = {{-110, -12}, {-110, 24}, {0, 24}, {-140, 0}},
        .Disp3DCnt = GL_ANTIALIAS},

// Category: Edge Marking ====================================

    // Basic Square
        {.Vertices = {{-32, -32}, {32, -32}, {32, 32}, {-32, 32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000000000011111},
        .ColorMode = 2},
    // Basic Triangle
        {.Vertices = {{-32, -32}, {32, -32}, {0, 16}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000000000011111},
        .ColorMode = 2},

// Category: Fog =============================================

    // Todo

// Category: Depth ===========================================

    // Todo

// Category: Clipping ========================================

  // Sub Cat: Texture Interpolation in Clipping -------------

    // todo

  // Sub Cat: Coord Interpolation in Clipping ---------------

    // todo

  // Sub Cat: Horizontal Line Polygons and Clipping ---------

    // todo: need to test if this applies with z clipping as well... in theory it should...?

    // Horizontal line polygons always render 1-4,
        {.Vertices = {{-32, 0}, {0, 0}, {48, 0}, {32, 0}}},
    // 1-2,
        {.Vertices = {{-32, 0}, {32, 0}, {48, 0}, {0, 0}}},
    // or 2-4. 3 is never rendered
        {.Vertices = {{0, 0}, {-32, 0}, {48, 0}, {32, 0}}},
    // Until the first vertex gets clipped.... (1-2)
        {.Vertices = {{-128, 0}, {-32, 0}, {32, 0}, {48, 0}}},
    // Then things start to get interesting... (2-3)
        {.Vertices = {{-128, 0}, {-128, 0}, {32, 0}, {48, 0}}},
    // 2-3
        {.Vertices = {{-128, 0}, {-128, 0}, {32, 0}, {48, 0}}},
    // 3-4
        {.Vertices = {{-128, 0}, {-128, 0}, {-128, 0}, {48, 0}}},
    // 4th vertex being clipped might complicate things, might not, probably depends on implementation of clipping (1-2)
        {.Vertices = {{-128, 0}, {-32, 0}, {32, 0}, {-128, 0}}},
    //  2-3
        {.Vertices = {{-128, 0}, {-128, 0}, {32, 0}, {-128, 0}}},
        
// Catgory: Misc =============================================
 
    // left side has precedence over right side
    // Just an innocent square c:
        {.Vertices = {{-32, -32}, {-32, 32}, {32, 33}, {32, -32}}},
    // Evil square
        {.Vertices = {{-32, -32}, {-32, 33}, {32, 32}, {32, -32}}},
    // pointer never goes backwards
        {.Vertices = {{-30, -14}, {20, 15}, {52, 15}, {-51, 10}}},
    //these slopes are identical, but render differently due to rounding.
        {.Vertices = {{-64, 0}, {64, -41}, {64, 41}, {-512, 0}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND},

  // Sub Cat: Second Vertex is Weird ------------------------

    // Second vertex behaves differently vs others for w/e reason.

    // should behave normally
        {.Vertices = {{-32, -32}, {-1, -1}, {32, 32}, {32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE},
    // should behave normally ...or not?
        {.Vertices = {{-32, -32}, {0, 0}, {32, 32}, {32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE},
    // should glitch out, behaving as if it was swapped
        {.Vertices = {{-32, -32}, {1, -1}, {32, 32}, {32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE},
    // however only the second vertex should cause this behavior
        {.Vertices = {{1, -1}, {32, 32}, {32, -32}, {-32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE},
    // should also behave normally
        {.Vertices = {{-32, -32}, {-32, -32}, {32, 32}, {32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE},
    // not sure if this one would behave weirdly tbh? idk im just gonna throw it in for the heck of it. might get removed.
        {.Vertices = {{-2, -1}, {0, 0}, {-2, -1}, {2, 1}},
        .PolyAttr = Wireframe | POLY_CULL_NONE},
};

constexpr ExtTestData ExtendedTests[] =
{
    // ext 1
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-32, -30, -16}, {-32, -32, -16}, {32, 16, -16}, {32, 18, -16}},
        .PolyAttr = Opaque | POLY_CULL_NONE | PolyID(2),
        .VertexColors{ColorMissing, ColorMissing, ColorMissing, ColorMissing}}}},
    // ext 2
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-32, 30, -16}, {-32, 32, -16}, {32, -16, -16}, {32, -18, -16}},
        .VertexColors{ColorMissing, ColorMissing, ColorMissing, ColorMissing}}}},
    // ext 3
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{32, 30, -16}, {32, 32, -16}, {-32, -16, -16}, {-32, -18, -16}},
        .VertexColors{ColorMissing, ColorMissing, ColorMissing, ColorMissing}}}},
    // ext 4
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-31, -30, -16}, {-31, -32, -16}, {33, 32, -16}, {33, 34, -16}},
        .VertexColors{ColorMissing, ColorMissing, ColorMissing, ColorMissing}}}},
    // ext 5
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{32, -30, -16}, {32, -32, -16}, {-32, 16, -16}, {-32, 18, -16}},
        .VertexColors{ColorMissing, ColorMissing, ColorMissing, ColorMissing}}}},
    // ext 6
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-32, -34, -16}, {32, -32, -16}, {32, 32, -16}, {-32, 34, -16}},
        .VertexColors{ColorMissing, ColorMissing, ColorMissing, ColorMissing}}}},
    // ext 7
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-32, -32, -16}, {32, -32, -16}, {32, 32, -16}, {-32, 32, -16}},
        .VertexColors{ColorMissing, ColorMissing, ColorMissing, ColorMissing}}}},
};

constexpr int NumEntries = sizeof(Tests) / sizeof(Tests[0]);
