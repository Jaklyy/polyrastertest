#include <nds.h>
#include <stdio.h>
#include <fat.h>
#include <filesystem.h>
#include "rastertest_data.h"

// Misc
constexpr int NumEntries = 66;
constexpr u8 NumVerts = 4;
constexpr u8 NumAxis = 3;

// Poly Attributes
constexpr u32 Opaque = (31 << 16);
constexpr u32 Trans = (30 << 16);
constexpr u32 Wireframe = (0 << 16);

// Disp3DCnt
//ph

struct Dataset
{
    s16 Vertices[NumVerts][NumAxis]; // Coordinates of each vertex x,y,z
    u32 PolyAttr; // Polygons attributes for each test
    u32 Disp3DCnt; // 3D Display Control Register bits to enable for each test
    u8 Colors; // How many colors to read/record from/to the data file: 0-3 = none, r, rg, rgb
};

constexpr Dataset Dataset[NumEntries] =
{
// Category: Fill Rules: Primary =============================

  // Sub Cat: Normal ----------------------------------------

    // Left Pos. X-Major - no fill
    {{{-32, -32, 0}, {32, -32, 0}, {32, 16, 0}, {-512, -512, 0}},
        Opaque | POLY_CULL_NONE,
        0,
        0},
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
        0},
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

bool TestCompletionTracker[NumEntries];

// Colors
constexpr u16 ColorMissing  = 0b000000000011111; // red
constexpr u16 ColorOverdraw = 0b111110000011111; // neon pink
constexpr u16 ColorMatch    = 0b000001111100000; // green
constexpr u16 ColorVoid     = 0b000000000000000; // black

// only increment if the actual tests change, (only do on releases?)
constexpr u16 DataVersion = 1;

// datafile format: 16 bits for version, each scanline has 1 bit for filled, 8 bits for start of span, 8 bits for end of span
// the 16 bits for span start/end are left out if not filled
// wireframe polygons have 32 bits, adding room for storing data for the potential second span.

u32 filebuffer;
u32 pointer;
u8 shift;

void readData(u32* buffer, const u8 bytes)
{
    for (int i = 0; i < bytes; i++)
    {
        if (pointer >= rastertest_data_size) return;

        *buffer <<= 8;
        *buffer |= rastertest_data[pointer];
        pointer++;
    }
}

u16 waitForInput(u16* prevkeys)
{
    while(1)
    {
        scanKeys();
        u16 keys = keysHeld();
        if ((keys & KEY_START && !(*prevkeys & KEY_START)) || (keys & KEY_A && !(*prevkeys & KEY_A)))
            return keys;
        *prevkeys = keys;
        swiWaitForVBlank();
    }
}

//========================================================================================
//=FILE=OPEN==============================================================================
//========================================================================================

bool handleFile(FILE** dat, u16* prevkeys, u8 mode)
{
    // open file to read from
    if (mode != 1)
    {
        u32 version = 0;
        pointer = 0;
        readData(&version, 2);
        if (version != DataVersion)
        {
            printf("Data has non-matching version\nnumber.\n\nPress A or Start to quit.\n");
            waitForInput(prevkeys);
            return 0;
        }
        
        shift = 0;
        filebuffer = 0;
        readData(&filebuffer, 4);
    }
    // create file to write to
    else
    {
        fatInitDefault();
        FILE* test = fopen("rastertest.data","rb");
        if (test != nullptr)
        {
            printf("Datafile already present.\nOverwrite?\n\nA: Yes\nStart: No");
            u16 input = waitForInput(prevkeys);
            if (input & KEY_START)
                return 0;
        }
        fclose(test);
        *dat = fopen("rastertest.data", "wb");
        if (*dat == nullptr)
        {
            printf("Could not make datafile.\n\nPress A or Start to close.");
            waitForInput(prevkeys);
            return 0;
        }
        u8 buffer = DataVersion >> 8;
        fwrite(&buffer, 1, 1, *dat);
        buffer = DataVersion & 0xFF;
        fwrite(&buffer, 1, 1, *dat);
        
        shift = 32;
    }
    return 1;
}

//========================================================================================
//=REWINDING==============================================================================
//========================================================================================

void rewindData(int iteration)
{
    filebuffer = 0;
    shift = 0;
    pointer = 2;
    readData(&filebuffer, 4);
    for (int i = 0; i < iteration; i++)
    {
        for (int j = 0; j < 192; j++)
        {
            while (shift >= 8)
            {
                readData(&filebuffer, 1);
                shift -=8;
            }
            if ((filebuffer & (1 << (31 - shift))) == 0)
                shift++;
            else if (!(Dataset[i].PolyAttr & Opaque))
                shift += 33;
            else
                shift += 17;
        }
    }
}

//========================================================================================
//=DRAWING================================================================================
//========================================================================================

void drawPoly(int iteration)
{
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPolyFmt(Dataset[iteration].PolyAttr);
    glEnable(Dataset[iteration].Disp3DCnt);

    int verts;
    if (Dataset[iteration].Vertices[3][0] != -512)
    {
        verts = 4;
        glBegin(GL_QUAD);
    }
    else
    {
        verts = 3;
        glBegin(GL_TRIANGLE);
    }

    for (int i = 0; i < verts; i++)
    {
        glColor3b(255, 255, 255);
        glVertex3v16(Dataset[iteration].Vertices[i][0], Dataset[iteration].Vertices[i][1], Dataset[iteration].Vertices[i][2]);
    }
    glEnd();
        
	glPopMatrix(1);

	glFlush(0);

    REG_DISPCAPCNT |= DCAP_ENABLE;
    while(REG_DISPCAPCNT & DCAP_ENABLE);

    glDisable(Dataset[iteration].Disp3DCnt);
}

//========================================================================================
//=TESTING================================================================================
//========================================================================================

u8 getSpanPoint()
{
    u8 ret = ((filebuffer >> (24-shift)) & 0xFF);
    shift += 8;
    return ret;
}

bool test(bool wireframe)
{
    bool errorfound = false;

    for (int y = 0; y < 192; y++)
    {
        while (shift >= 8)
        {
            readData(&filebuffer, 1);
            shift -=8;
        }
        if (filebuffer & (1 << (31-shift)))
        {
            // span present
            shift++;
            u8 startspan = getSpanPoint();
            u8 endspan = getSpanPoint();
            bool done = false;
            for (int x = 0; x < 256; x++)
            {
                if (wireframe && x > endspan && !done)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        
                        readData(&filebuffer, 1);
                        shift -=8;
                    }
                    startspan = getSpanPoint();
                    endspan = getSpanPoint();
                    done = true;
                }

                u16 offset = y * 256 + x;
                u16 currcolor = VRAM_A[offset] & 0x7FFF;
                if (currcolor == ColorVoid)
                {
                    if (!(x < startspan || x > endspan))
                    {
                        VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorMissing;
                        errorfound = true;
                    }
                }
                else if (x < startspan || x > endspan)
                {
                    VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorOverdraw;
                    errorfound = true;
                }
                else
                {
                    VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorMatch;
                }
            }
        }
        else
        {
            // no span
            shift++;
            for (int x = 0; x < 256; x++)
            {
                u16 offset = (y * 256) + x;
                u16 currcolor = VRAM_A[offset] & 0x7FFF;
                if (currcolor != ColorVoid)
                {
                    VRAM_A[offset] = ColorOverdraw;
                    errorfound = true;               
                }
            }
        }
    }

    return errorfound;
}

//========================================================================================
//=RECORDING==============================================================================
//========================================================================================

void record(FILE* dat, bool wireframe)
{
    s16 start = -1;
    s16 end = -1;
    s16 start2 = -1;
    s16 end2 = -1;

    for (int y = 0;; y++)
    {
        if (y != 0) // dont write on the first loop
        {
            if (start == -1)
                shift--;
            else
            {
                shift--;
                filebuffer |= (1<<shift);

                if (end == -1) end = 255;
                
                shift -= 8;
                filebuffer |= (start<<shift);

                shift -= 8;
                filebuffer |= (end<<shift);

                if (wireframe)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        u8 tempbuffer = filebuffer >> 24;
                        fwrite(&tempbuffer, 1, 1, dat);
                        filebuffer <<= 8;
                        shift += 8;
                    }

                    if (start2 == -1)
                    {
                        shift -= 16;
                    }
                    else
                    {
                        if (end2 == -1) end2 = 255;

                        shift -=8;
                        filebuffer |= (start2<<shift);
                        shift -= 8;
                        filebuffer |= (end2<<shift);
                    }
                }
            }

            while (shift <= 24)
            {
                u8 tempbuffer = filebuffer >> 24;
                fwrite(&tempbuffer, 1, 1, dat);
                filebuffer <<= 8;
                shift += 8;
            }
        }
        
        if (y == 192) //dont check on final loop
            break;

        start = -1;
        end = -1;
        start2 = -1;
        end2 = -1;
        int x = 0;
        for (int i = 0; i <= wireframe; i++)
        {
            bool prevpixel = 0;
            for (; x < 256; x++)
            {
                if ((VRAM_A[y*256+x] & 0x7FFF) != ColorVoid)
                {
                    if (prevpixel == 0)
                    {   
                        if (!i)
                            start = x;
                        else
                            start2 = x;
                        prevpixel = 1;
                    }
                }
                else if (prevpixel == 1)
                {
                    if (!i)
                        end = x-1;
                    else
                        end2 = x-1;
                    x++;
                    break;
                }
            }
        }
    }     
}

//========================================================================================
//=MAIN===================================================================================
//========================================================================================

int main()
{
	consoleDemoInit();

    videoSetMode(MODE_0_3D);

    glInit();

    glClearColor(0,0,0,31);
    glClearPolyID(63);
    glClearDepth(GL_MAX_DEPTH);

    glSetOutlineColor(0, 0b111111111111111);

    glViewport(0,0,255,191);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof32(128, -127,
               96, -95,
               0, GL_MAX_DEPTH);
    gluLookAt(0.0, 0.0, -1.0,
              0.0, 0.0,  0.0,
              0.0, 1.0,  0.0);

    int iteration = 0;
    u16 prevkeys;
    
	scanKeys();
    u8 mode;

    {
        u16 keys = keysHeld();

        if (keys & KEY_START)
            mode = 1; // generate data file
        else if (keys & KEY_SELECT)
            mode = 2; // test one-by-one
        else
            mode = 0; // default test mode
        prevkeys = keys;
    }

    FILE* dat;
    if (!handleFile(&dat, &prevkeys, mode))
    {
        return 0;
    }

    vramSetBankA(VRAM_A_LCD);
    REG_DISPCAPCNT = DCAP_MODE(DCAP_MODE_A)
                    | DCAP_SRC_A(DCAP_SRC_A_3DONLY)
                    | DCAP_SIZE(DCAP_SIZE_256x192)
                    | DCAP_OFFSET(0)
                    | DCAP_BANK(DCAP_BANK_VRAM_A);

    bool showresults = 0;
    int numcomplete = 0;
    int numpass = 0;

//========================================================================================
//=MAIN LOOP==============================================================================
//========================================================================================

    while (1)
    {
        // poll input
		scanKeys();
        u16 keys = keysHeld();

        // check if done
        if (iteration >= NumEntries)
        {
            if (mode == 1)
            {
                // make sure nothing got left behind in the buffer
                if (shift < 32)
                {
                    u8 tempbuffer = (filebuffer >> 24);
                    fwrite(&tempbuffer, 1, 1, dat);
                }
                consoleClear();
                printf("Recording Done.\n\nNew datafile present in rom\ndirectory.\n\nPress A or Start to quit.\n");
                fclose(dat);
                waitForInput(&prevkeys);
                return 0;
            }
            else
            {
                mode = 3; // finished mode
                iteration--;
                rewindData(iteration);
            }
        }

        // main chunk
        if (!showresults)
        {
            swiWaitForVBlank(); // forces timings to align
            drawPoly(iteration);
            drawPoly(iteration); //lazy 'temp' hack.

            if (mode != 1) // not recording new data file
            {
                showresults = (mode >= 2);
                bool errorfound;

                showresults |= errorfound = test(!(Dataset[iteration].PolyAttr & Opaque));

                if (!TestCompletionTracker[iteration])
                {
                    TestCompletionTracker[iteration] = true;
                    numcomplete++;
                    if (!errorfound) numpass++;
                }

                if (showresults) videoSetMode(MODE_FB0);
                else iteration++;

                consoleClear();
                if (mode == 3)
                    printf("Testing complete!\n\n");
                printf("Tests Passed: %i/%i\n\n", numpass, numcomplete);
                if (mode != 0)
                {
                    printf("Press A to view next test\nPress B to view previous test\nPress Start to close.\n\n");
                    printf("Viewing Test %i...\n\n", iteration+1);
                }
                else
                {
                    printf("Testing %i...\n\n", iteration+1);
                }
                printf("Green: Matching Pixel.\nRed: Missing Pixel.\nPink: Overdrawn Pixel.\n");
            }
            else // recording new data file
            {
                consoleClear();
                printf("Recording %i...\n", iteration+1);

                record(dat, !(Dataset[iteration].PolyAttr & Opaque));
                iteration++;
            }
        }
        else // if showing results
        {
            if (keys & KEY_A && !(prevkeys & KEY_A))
            {
                showresults = false;
                videoSetMode(MODE_0_3D);
                iteration++;
            }

            if ((mode >= 2) && ((keys & KEY_B) && !(prevkeys & KEY_B)))
            {
                showresults = false;
                videoSetMode(MODE_0_3D);
                iteration--;
                if (iteration < 0)
                    iteration = 0;
                rewindData(iteration);
            }
        }

        // if not recording allow you to cancel at any time.
        if ((mode != 1) && ((keys & KEY_START) && !(prevkeys & KEY_START)))
        {
            return 0;
        }
        prevkeys = keys;
        if (showresults) swiWaitForVBlank();
    }

    if(dat != nullptr) fclose(dat);
    return 0;
}