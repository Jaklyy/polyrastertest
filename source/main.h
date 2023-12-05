


// Misc
constexpr u8 NumVerts = 4;
constexpr u8 NumAxis = 3;
constexpr char Version[] = "1.0.2-b";

// only increment if the actual tests change, (only do on releases?)
// TODO: replace with an automatically calculated hash of all the test declarations?
constexpr u16 DataVersion = 2;

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

// Only add to the end to avoid breaking configs (whenever i decide to start saving them)
enum Tags {
    Niche = 1,
    UltraNiche,
    FillRules,
    FR_Normal,
    FR_Swapped,
    FR_Override,
    FR_Unusual,
    FR_Line,
    FR_SwapVertL,
    FR_Trapezoid,
    FR_EdgeMarking,
    VertRightShift,
    AntiAliasing,
    AA_SwapVert,
    Edgemarking,
    Fog,
    Depth,
    Clipping,
    Cl_TextInterp,
    Cl_CoordInterp,
    Cl_HorizLine,
    UpperLimits,
    UL_ScanlineAbort,
    Misc,
    Mi_SecVertex,
    Tag_Wireframe,
    Translucency,
    DSi,
    ThreeDS, // yes i have to spell out 3 or else the compiler cries about it
};

struct TestData
{
    s16 Vertices[NumVerts][NumAxis]; // Coordinates of each vertex x,y,z
    u32 PolyAttr = Opaque | POLY_CULL_NONE; // Polygons attributes for each test
    u16 VertexColors[4] = {White, White, White, White}; // colors for each vertex
    u16 Disp3DCnt = 0; // 3D Display Control Register bits to enable for each test (reg is technically 32 bit but half of it is unused)
    u8 Flush = 0;
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
    u8 Tags[8] = {0,0,0,0,0,0,0}; // for tracking shiz
};

struct Polygon
{
    s16 Vertices[NumVerts][NumAxis];
    u32 PolyAttr = Opaque | POLY_CULL_NONE;
    u16 VertexColors[4] = {White, White, White, White};
    u16 Copies = 1;
};

struct ExtTestData
{
    u16 NumPolygons = 1;
    Polygon Polygons[2];
};


struct Menu
{
    u8 NumEntries = 0;
    char Entries [23][31] = {""};
    u16 Inputs[24]; // id 0 = b input, higher is each entry. additional values of < 256 are for 
    bool Toggles = false;
};

Menu Configure1 =
{
    .NumEntries = 23, 
    .Entries = {"-Niche Tests", " -Ultra Niche Tests", "-Fill Rules", " -Normal", " -Swapped", " -Overrides", " -Unusual", " -Line",
    " -Swapped Vertical Left", " -Trapezoid", " -Edge Marking Fill Quirk", "-Vertical Right Shift", "-Anti-Aliasing", " -Swapped Vertical",
    "-Edge Marking", "-Wireframe", "-Translucency", "-Clipping", " -Horizontal Lines", "-Upper Limits", " -Scanline Abort", "-Misc",
    " -Second Vertex Bug"},
    .Inputs {256, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 26, 27, 18, 21, 22, 23, 24, 25},
    .Toggles = true
};

Menu MainMenu =
{
    .NumEntries = 3, 
    .Entries = {"Test", "Manual Test", "Record", "Configure"},
    .Inputs {261, 257, 258, 259, 260}
};
