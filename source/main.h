


// Misc
constexpr u8 NumVerts = 4;
constexpr u8 NumAxis = 3;
constexpr char Version[] = "1.0.2-b";

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
constexpr u16 White  = 0b111111111111111;
constexpr u16 Black  = 0b000000000000000;
constexpr u16 Red    = 0b000000000011111;
constexpr u16 Yellow = 0b000001111111111;
constexpr u16 Green  = 0b000001111100000;
constexpr u16 Cyan   = 0b111111111100000;
constexpr u16 Blue   = 0b111110000000000;
constexpr u16 Pink   = 0b111110000011111;
constexpr u16 ColorStock = White;
constexpr u16 ColorMissing = Red;
constexpr u16 ColorOverdraw = Pink;
constexpr u16 ColorMatch = Green;
constexpr u16 ColorWrongTex = Blue;
constexpr u16 ColorVoid = Black;


// only increment if the actual tests change, (only do on releases?)
constexpr u16 DataVersion = 2;

struct TestData
{
    s16 Vertices[NumVerts][NumAxis]; // Coordinates of each vertex x,y,z
    u32 PolyAttr = Opaque | POLY_CULL_NONE; // Polygons attributes for each test
    u16 VertexColors[4] = {White, White, White, White}; // colors for each vertex
    u32 Disp3DCnt = 0; // 3D Display Control Register bits to enable for each test
    u32 Viewport = (0<<0) + (0<<8) + (255<<16) + (191<<24); // Viewport to use
    m4x4 Projection = {131586, 0, 0, 0, // Matrix to use for projection
                       0, -175677, 0, 0,
                       0, 0, -1024, 0,
                       16, 21, -4096, 4096};
    u16 OutlineColors[8] = {White}; // specify colors for edgemarking, 0 defaults to white, and 1-7 black
    u8 RearID = 63;
    u16 RearDepth = GL_MAX_DEPTH;
    u8 ColorMode = 0; // How many colors to read/record from/to the data file: 0-3 = none, r, rg, rgb
    u16 ExtendedTestData = 0; // Determines which and whether to use an extended test mode. 0 = none, if greater use the value - 1 to determine which exttestdata to use.
};

struct Polygon
{
    s16 Vertices[NumVerts][NumAxis];
    u32 PolyAttr = Opaque | POLY_CULL_NONE;
    u16 VertexColors[4] = {White, White, White, White};
};

struct ExtTestData
{
    u32 NumPolygons = 1;
    u32 TimesPoly1 = 1;
    Polygon Polygons[2];
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

    // Edgemarking (only) + overlapping edges + same id = no fill????
    // right ymajor/vert (overriden by left ymajor/vert)
    // bottom xmajor/flat (overriden by top xmajor/flat)

    // I hate fill rules now (does this even count as a fill rule?)
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 1},
    // Does not apply when poly ids are different
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .PolyAttr = Opaque | POLY_CULL_NONE | PolyID(1), 
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 1},
    // Also doesn't apply with aa, ofc
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .Disp3DCnt = GL_OUTLINE | GL_ANTIALIAS,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 1},
    // What about translucency? - no
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 1},
    // Wireframe? - yes, for some reason?
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .PolyAttr =  Wireframe | POLY_CULL_NONE,
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 5},
    // How about when over the Rear Plane? - no, but that makes sense
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .PolyAttr =  Opaque | POLY_CULL_NONE | PolyID(63),
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3},
    // also applies to verticals babyy
        {.Vertices = {{-32, -32}, {-32, 32}, {0, 32}, {0, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 2},
    // bottom xmajor
        {.Vertices = {{-32, -32}, {-32, 0}, {32, -32}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 3},
    // bottom flat
        {.Vertices = {{-32, -32}, {-32, 0}, {32, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 4},
    // note that it's specifically the center of the polygon, and not the slopes that this applies to in this case.
        {.Vertices = {{-32, -32}, {-28, 0}, {28, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 4},
    // the rules dont seem to combine, though (weird phrasing i know)
        {.Vertices = {{-32, -32}, {-32, 32}, {0, 32}, {0, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 4},
    // Anyway now for some weird stuff:
        {.Vertices = {{-32, -2}, {-32, 0}, {32, 0}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 6},
    // 
        {.Vertices = {{-32, 2}, {-32, 0}, {32, 0}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 7},
    //
        {.Vertices = {{-32, -32}, {-32, 0}, {32, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 8},
    //
        {.Vertices = {{-32, -32}, {-32, -2}, {32, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 9},
    //
        {.Vertices = {{-2, -32}, {0, -32}, {0, 32}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 10},
    //
        {.Vertices = {{0, -32}, {2, -32}, {0, 32}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 11},
    //
        {.Vertices = {{-32, -32}, {0, -32}, {0, 32}, {-32, 32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 12},
    //
        {.Vertices = {{-32, -32}, {2, -32}, {0, 32}, {-32, 32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 13},
    // does not apply if the edge becomes properly edge marked
        {.Vertices = {{-32, -32}, {32, -32}, {32, 0}, {-32, 0}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 14},
    // line polygons (horizontal)
        {.Vertices = {{-32, -32}, {-32, 0}, {32, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 15},
    // line poly (vert)
        {.Vertices = {{-32, -32}, {-32, 32}, {0, 32}, {0, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 16},
    // more curse
        {.Vertices = {{-32, -32}, {-32, 32}, {0, 32}, {0, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 16},

        
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

// Category: Upper Limits =====================================

  // Sub Cat: Scanline Pixel Limit(?)

    // Seems like you can only render so many pixels in a scanline before the far plane peeks through?
    // Not 100% sure what exactly is happening here.
    // We're not even close to the polygon/vertex limit, so that's not it.

    // Look at this
        {.Vertices = {{-256, -256}, {-256, 256}, {256, 256}, {256, -256}},
        .ExtendedTestData = 17},
    // Why is there a line forming there, it does not care about size, just number of polygons
        {.Vertices = {{-256, -256}, {-256, 256}, {256, 256}, {256, -256}},
        .ExtendedTestData = 18},
    // Parial Line, Mid Scanline
        {.Vertices = {{-256, -256}, {-256, 256}, {256, 256}, {256, -256}},
        .ExtendedTestData = 19},
    // Here it is with a triangle
        {.Vertices = {{97, -25}, {72, 25}, {122, 25}, {-512}},
        .ExtendedTestData = 20},

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
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{32, -32, -16}, {32, 32, -16}, {-32, 32, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 2
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-1, -32, -16}, {-1, 32, -16}, {32, 32, -16}, {32, -32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 3
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{32, 0}, {-32, 0}, {32, -32}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 4
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 32, -16}, {-32, -1, -16}, {32, -1, -16}, {32, 32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 5
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{32, -32, -16}, {32, 32, -16}, {-32, 32, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 6
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 32, -16}, {-32, -1, -16}, {32, -1, -16}, {32, 32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 7
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 32, -16}, {-32, 2, -16}, {32, 0, -16}, {32, 32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 8
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, -1, -16}, {-32, 1, -16}, {32, -1, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 9
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 0, -16}, {-32, -2, -16}, {32, 0, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 10
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-1, -32, -16}, {-1, 32, -16}, {32, 32, -16}, {32, -32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 11
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{2, -32, -16}, {0, 32, -16}, {32, 32, -16}, {32, -32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 12
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-1, -32, -16}, {-1, 32, -16}, {1, 32, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 13
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{2, -32, -16}, {0, 32, -16}, {2, 32, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 14
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 0, -8}, {32, 0, -8}, {32, 32, -8}, {-32, 32, -8}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{-32, -1, -16}, {32, -1, -16}, {32, 32, -16}, {-32, 32, -16}},
            .PolyAttr = Opaque | POLY_CULL_NONE | PolyID(1),
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 15
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, -1, -16}, {32, -1, -16}, {32, -1, -16}, {-32, -1, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 16
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-1, -32, -16}, {-1, -32, -16}, {-1, 32, -16}, {-1, 32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    //ext 17
        {.NumPolygons = 1,
        .TimesPoly1 = 94,
        .Polygons = {{.Vertices = {{-80, -5}, {-80, 5}, {80, 5}, {80, -5}},
            .VertexColors{Red, Red, Red, Red}}}},
    //ext 18
        {.NumPolygons = 1,
        .TimesPoly1 = 501,
        .Polygons = {{.Vertices = {{-80, -5}, {-80, 5}, {0, 5}, {0, -5}},
            .VertexColors{Red, Red, Red, Red}}}},
    //ext 19
        {.NumPolygons = 1,
        .TimesPoly1 = 448,
        .Polygons = {{.Vertices = {{-124, -5}, {-124, 5}, {-100, 5}, {-100, -5}},
            .VertexColors{Red, Red, Red, Red}}}},
    //ext 20
        {.NumPolygons = 1,
        .TimesPoly1 = 2048,
        .Polygons = {{.Vertices = {{-124, -5}, {-124, 5}, {-100, 5}, {-100, -5}},
            .VertexColors{Red, Red, Red, Red}}}},
};

constexpr int NumEntries = sizeof(Tests) / sizeof(Tests[0]);
