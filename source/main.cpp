#include <nds.h>
#include <stdio.h>
#include <fat.h>
#include <filesystem.h>


// Misc
constexpr int NumEntries = 29;
constexpr u8 NumVerts = 4;
constexpr u8 NumAxis = 2;

// Poly Attributes
constexpr u32 Opaque = (31 << 16);
constexpr u32 Wireframe = (0 << 16);

// DISP3DCNT
//ph

struct Dataset
{
    s16 Vertices[NumVerts][NumAxis];
    u32 PolyAttr;
    u32 DISP3DCNT;
};

constexpr Dataset Dataset[NumEntries] =
{
// Category: Fill Rules: Common ==============================

    // Left Pos. X-Major
    {{{-32, -32}, {32, -32}, {32, 16}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Left Pos. Diagonal
    {{{-32, -32}, {32, -32}, {32, 32}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Left Pos. Y-Major
    {{{-32, -32}, {32, -32}, {32, 48}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Left Neg. X-Major
    {{{-32, 32}, {32, 32}, {32, -16}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Left Neg. Diagonal
    {{{-32, 32}, {32, 32}, {32, -32}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Left Neg. Y-Major
    {{{-32, 32}, {32, 32}, {32, -48}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Right Pos. X-Major
    {{{32, -32}, {-32, -32}, {-32, 16}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Right Pos. Diagonal
    {{{32, -32}, {-32, -32}, {-32, 32}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Right Pos. Y-Major
    {{{32, -32}, {-32, -32}, {-32, 48}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Right Neg. X-Major
    {{{32, 32}, {-32, 32}, {-32, -16}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Right Neg. Diagonal
    {{{32, 32}, {-32, 32}, {-32, -32}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},
    // Right Neg. Y-Major
    {{{32, 32}, {-32, 32}, {-32, -48}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        0},

// Category: Fill Rules: Global ==============================

    // Transparency + Blend
    {{{-32, -32}, {32, -32}, {32, 16}, {-512, -512}},
        (30 << 16) | POLY_CULL_NONE,
        GL_BLEND},
    // Transparency + NO BLEND
    {{{-32, -32}, {32, -32}, {32, 16}, {-512, -512}},
        (30 << 16) | POLY_CULL_NONE,
        0},
    // Wireframe
    {{{-32, -32}, {32, -32}, {32, 16}, {-512, -512}},
        Wireframe | POLY_CULL_NONE,
        0},
    // Anti-Aliasing
    {{{-32, -32}, {32, -32}, {32, 16}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        (GL_ANTIALIAS)},
    // Edge Marking
    {{{-32, -32}, {32, -32}, {32, 16}, {-512, -512}},
        Opaque | POLY_CULL_NONE,
        (GL_OUTLINE)},

// Category: Fill Rules: Unusual =============================

  // Sub Cat: Line Polygon Exception ------------------------

    // simple line polygon
    {{{-10, -5}, {-10, -5}, {10, 5}, {-512, 0}},
        Opaque | POLY_CULL_NONE,
        0},
    // not quite a line polygon
    {{{-11, -6}, {-10, -5}, {10, 5}, {-512, 0}},
        Opaque | POLY_CULL_NONE,
        0},
    // if you can see this you're doing something wrong
    {{{-2, -1}, {0, 0}, {2, 1}, {-512, 0}},
        Opaque | POLY_CULL_NONE,
        0},
    // cursed line polygon 1
    {{{47, 8}, {-46, -27}, {47, 27}, {-46, -27}},
        Opaque | POLY_CULL_NONE,
        0},

  // Sub Cat: Swapped Vertical Left Glitch ------------------

    // checking the WRONG SIDE!!!
    {{{-110, -12}, {-110, 24}, {0, 24}, {-140, 0}},
        Opaque | POLY_CULL_NONE,
        0},
    // cursed
    {{{50, -30}, {-30, 50}, {0, 50}, {0, -20}},
        Opaque | POLY_CULL_NONE,
        0},
    // x major slopes are never filled by this glitch, though.
    {{{50, -30}, {-20, 20}, {0, 20}, {0, -20}},
        Opaque | POLY_CULL_NONE,
        0},

  // Sub Cat: Trapezoids ------------------------------------

    // this is a fill rule ...for some reason?
    {{{-25, 10}, {25, 10}, {50, -10}, {-50, -10}},
        Opaque | POLY_CULL_NONE,
        0},
    // it applies to clipped vertices too!
    {{{-50, 90}, {50, 90}, {0, 110}, {-512, 0}},
        Opaque | POLY_CULL_NONE,
        0},
    // only x major slopes though
    {{{-25, 10}, {25, 10}, {35, -10}, {-45, -10}},
        Opaque | POLY_CULL_NONE,
        0},

// Category: Fill Rule Adjacent ==============================

    // left side has precedence over right side
    {{{-32, -32}, {-32, 32}, {32, 33}, {32, -32}},
        Opaque | POLY_CULL_NONE,
        0},
    // pointer never goes backwards
    {{{-30, -14}, {20, 15}, {52, 15}, {-51, 10}},
        Opaque | POLY_CULL_NONE,
        0},
};

// Colors
constexpr u16 ColorMissing  = 0b000000000011111; // red
constexpr u16 ColorOverdraw = 0b111110000011111; // pink
constexpr u16 ColorMatch    = 0b000001111100000; // green
constexpr u16 ColorVoid     = 0b000000000000000;

// only increment if the actual tests change
constexpr u16 DataVersion = 0;

// datafile format: 16 bits for version, each scanline has 1 bit for filled, 8 bits for start of span, 8 bits for end of span
// the 16 bits for span start/end are left out if not filled
// todo: support wireframe polygons

u32 filebuffer;
u8 shift = 0;

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
        fatInitDefault();
        *dat = fopen("rastertest.data", "rb");
    
        if (*dat == nullptr)
        {
            nitroFSInit(NULL);
            *dat = fopen("rastertest.data", "rb");
            if (*dat == nullptr)
            {
                printf("Unable to read builtin data. Welp.\n\n Press A or Start to exit");
                waitForInput(prevkeys);
                return 0;
            }
        }
        fseek(*dat, 0, SEEK_SET);

        u16 version;
        fread(&version, 2, 1, *dat);
        if (version != DataVersion)
        {
            printf("Datafile is of version %i, expected version is version %i\nPlease provide an appropriate date file\nIf you would like to proceed with builtin data please press A\nTo quit, press Start.\n", version, DataVersion);
        
            u16 input = waitForInput(prevkeys);
            if (input & KEY_START)
                return 0;
            else if (input & KEY_A)
            {
                consoleClear();
                fclose(*dat);
                nitroFSInit(NULL);
                *dat = fopen("rastertest.data", "rb");
                if (*dat == nullptr)
                {
                    printf("Unable to read builtin data. Welp.\n\n Press A or Start to exit");
                    waitForInput(prevkeys);
                    return 0;
                }
            }
        }
        
        fread(&filebuffer, 4, 1, *dat);
        return 1;
    }
    // create file to write to
    else
    {
        fatInitDefault();
        *dat = fopen("rastertest.data","rb");
        if (*dat != nullptr)
        {
            printf("Datafile already present. Overwrite?\n\nA: Yes\nStart: No");
            u16 input = waitForInput(prevkeys);
            if (input & KEY_START)
                return 0;
        }
        *dat = fopen("rastertest.data", "wb");
        if (*dat == nullptr)
        {
            printf("Could not make datafile.\n\nPress A or Start to close.");
            waitForInput(prevkeys);
            return 0;
        }
        fwrite(&DataVersion, 2, 1, *dat);
        shift = 32;
    }
    return 1;
}

//========================================================================================
//=REWINDING==============================================================================
//========================================================================================

void rewindData(FILE* dat, int iteration)
{
    u8 tempbuffer;
    fseek(dat, 2, SEEK_SET); // seek to after version data
    fread(&filebuffer, 4, 1, dat); // reinit filebuffer
    shift = 0; // reset shift
    for (int i = 0; i < iteration; i++)
    {
        for (int j = 0; j < 192; j++)
        {
            while (shift >= 8)
            {
                fread(&tempbuffer, 1, 1, dat);
                filebuffer <<= 8;
                filebuffer |= tempbuffer;
                shift -= 8;
            }
            if ((filebuffer & (1 << (31 - shift))) == 0)
                shift++;
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
    glEnable(Dataset[iteration].DISP3DCNT);

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
        glVertex3v16(Dataset[iteration].Vertices[i][0], Dataset[iteration].Vertices[i][1], 0);
    }
    glEnd();
        
	glPopMatrix(1);

	glFlush(0);

    REG_DISPCAPCNT |= DCAP_ENABLE;
    while(REG_DISPCAPCNT & DCAP_ENABLE);

    glDisable(Dataset[iteration].DISP3DCNT);
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

bool test(FILE* dat)
{
    u8 tempbuffer;
    bool errorfound = false;

    for (int y = 0; y < 192; y++)
    {
        if (dat != nullptr)
        {
            while (shift >= 8)
            {
                fread(&tempbuffer, 1, 1, dat);
                filebuffer <<= 8;
                filebuffer |= tempbuffer;
                shift -= 8;
            }
        }
        if (filebuffer & (1 << (31-shift)))
        {
            // span present
            shift++;
            u8 startspan = getSpanPoint();
            u8 endspan = getSpanPoint();
            for (int x = 0; x < 256; x++)
            {
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

void record(FILE* dat)
{
    s16 start = -1;
    s16 end = -1;

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
        bool prevpixel = 0;
        for (int x = 0; x < 256; x++)
        {
            if ((VRAM_A[y*256+x] & 0x7FFF) != ColorVoid)
            {
                if (prevpixel == 0)
                {
                start = x;
                prevpixel = 1;
                }
            }
            else if (prevpixel == 1)
            {
                end = x-1;
                break;
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
    handleFile(&dat, &prevkeys, mode);

    vramSetBankA(VRAM_A_LCD);
    REG_DISPCAPCNT = DCAP_MODE(DCAP_MODE_A)
                    | DCAP_SRC_A(DCAP_SRC_A_3DONLY)
                    | DCAP_SIZE(DCAP_SIZE_256x192)
                    | DCAP_OFFSET(0)
                    | DCAP_BANK(DCAP_BANK_VRAM_A);

    bool errorfound = false;
    int passcounter = NumEntries;
    int highestiteration = 0;
//========================================================================================
//=MAIN LOOP==============================================================================
//========================================================================================

    while (1)
    {
		scanKeys();

        u16 keys = keysHeld();

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
                printf("Recording Done.\n\nNew datafile present in rom\n directory.\n\nPress A or Start to quit.\n");
                fclose(dat);
                waitForInput(&prevkeys);
                return 0;
            }
            else
            {
                mode = 3; // finished mode
                iteration--;
                rewindData(dat, iteration);
            }
        }

        if (!errorfound)
        {
            swiWaitForVBlank(); // forces timings to align
            drawPoly(iteration);
            drawPoly(iteration); //lazy 'temp' hack.

            if (mode != 1) // not recording new data file
            {
                consoleClear();
                if (mode == 3)
                    printf("Testing complete!\n\nTests Passed: %i/%i\n\n", passcounter, NumEntries);
                if (mode != 0)
                {
                    printf("Press A to view next test\nPress B to view previous test\nPress Start to close.\n\n");
                    printf("Viewing Test %i...\n", iteration+1);
                }
                else
                {
                    printf("Testing %i...\n", iteration+1);
                }
                errorfound = test(dat);
            }
            else // recording new data file
            {
                consoleClear();
                printf("Recording %i...\n", iteration+1);
                record(dat);
            }

            if (mode >= 2)
                errorfound = true;
            
            if (errorfound)
            {
                videoSetMode(MODE_FB0);
                if (iteration >= highestiteration)
                    passcounter--;
            }
            else
            {
                iteration++;
                highestiteration++;
                if (highestiteration == NumEntries) highestiteration++;
            }
        }
        else
        {
            if (keys & KEY_A && !(prevkeys & KEY_A))
            {
                errorfound = false;
                videoSetMode(MODE_0_3D);
                iteration++;
                if (iteration > highestiteration) highestiteration++;
                if (highestiteration == NumEntries) highestiteration++;
            }

            if ((mode >= 2) && ((keys & KEY_B) && !(prevkeys & KEY_B)))
            {
                errorfound = false;
                videoSetMode(MODE_0_3D);
                iteration--;
                if (iteration < 0)
                    iteration = 0;
                rewindData(dat, iteration);
            }
        }
        if ((mode != 1) && ((keys & KEY_START) && !(prevkeys & KEY_START)))
        {
            fclose(dat);
            return 0;
        }
        prevkeys = keys;
        if (errorfound) swiWaitForVBlank();
    }

    if(dat != nullptr) fclose(dat);
    return 0;
}