


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

enum {
    test_FillRules = 0

};

// only increment if the actual tests change, (only do on releases?)
// TODO: replace with an automatically calculated hash of all the test declarations?
constexpr u16 DataVersion = 2;

struct TestData
{
    u16 Tags = 0;
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
