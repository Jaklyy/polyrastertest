#include <nds.h>
#include <stdio.h>
#include <fat.h>
#include <filesystem.h>
#include "rastertest_data.h"
#include "main.h"
#include "tests.h"



// Notes on Datafile Format:
// 16 bits for version
// each scene has 2 bits to determine how many colors should be read
// each scanline has 1 bit for filled, 8 bits for start of span, 8 bits for end of span
// the 16 bits for span start/end are left out if not filled
// wireframe polygons have 32 bits, adding room to store data for the potential second span.
// each span is followed by one set of 5/10/15 bits for each pixel representing color, depending on the color read bits

// global variables because im lazy
u32 filebuffer = 0; // life would be so much easier if this were 64 bit but i cba to figure out why changing that keeps breaking
u32 pointer = 0;
u8 shift = 0;
bool filters[256];

//========================================================================================
//=MISC===================================================================================
//========================================================================================

u32 readData(u32 buffer, const u8 bytes)
{
    for (int i = 0; i < bytes; i++)
    {
        if (pointer >= rastertest_data_size) return buffer << 8;

        buffer <<= 8;
        buffer |= rastertest_data[pointer];
        pointer++;
    }
    return buffer;
}

u32 writeBuffer(u32 buffer, const int value, const u8 bits)
{
    buffer <<= bits;
    buffer |= value;
    shift += bits;

    return buffer;
}

void writeFile(FILE* dat)
{
    while (shift >= 8)
    {
        u8 tempbuffer = ((filebuffer >> (shift-8)) & 0xFF);
        fwrite(&tempbuffer, 1, 1, dat);
        shift -= 8;
    }
}

u8 getSpanPoint()
{
    u8 ret = ((filebuffer >> (24-shift)) & 0xFF);
    shift += 8;
    return ret;
}

u16 getColor(const u8 bits, const u16 mask)
{
    u16 ret = ((filebuffer >> ((32-bits)-shift)) & mask);
    shift += bits;
    return ret;
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

bool checkFilters(int iteration)
{
    for (int i = 0; i < 8; i++)
    {
        u8 tag = Tests[iteration].Tags[i];
        if (filters[tag])
            return true;
    }
    return false;
}

//========================================================================================
//=MENU===================================================================================
//========================================================================================

bool menuSelect(u16 selection, Menu** menu, u8* mode, u8* pointer)
{
    switch (selection)
    {
    case 256:
        *menu = &MainMenu;
        *pointer = 0;
        return false;
    case 257:
        *mode = 0;
        return true;
    case 258:
        *mode = 2;
        return true;
    case 259:
        *mode = 1;
        return true;
    case 260:
        *menu = &Configure1;
        *pointer = 0;
        return false;
    case 261:
        return false;
    default:
        filters[selection] = !filters[selection];
        return false;
    }
}

void menu(u16* prevkeys, u8* mode)
{
    Menu* menu = &MainMenu;
    u8 pointer = 0;
    bool updatemenu = true;
    while (1)
    {
        if (updatemenu)
        {
            swiWaitForVBlank();
            consoleClear();
            for (int i = 0; i <= menu->NumEntries-1; i++)
            {
                printf(((pointer == i) ? ">" : " "));
                if (menu->Toggles) printf((filters[menu->Inputs[i+1]] ? "X" : "O"));
                printf(menu->Entries[i]);
                printf("\n");
            }
            updatemenu = false;
        }

        scanKeys();
        u16 keys = keysHeld();

        // todo: find better way to determine what a menu button should do
        if ((keys & KEY_A) && !(*prevkeys & KEY_A))
        {
            if (menuSelect(menu->Inputs[pointer+1], &menu, mode, &pointer)) return;
            updatemenu = true;
        }
        else if ((keys & KEY_B) && !(*prevkeys & KEY_B))
        {
            if (menuSelect(menu->Inputs[0], &menu, mode, &pointer)) return;
            updatemenu = true;
        }
        else if ((keys & KEY_UP) && !(*prevkeys & KEY_UP))
        {
            if (pointer <= 0) pointer = 0;
            else
            {
                pointer--;
                updatemenu = true;
            }
        }
        else if ((keys & KEY_DOWN) && !(*prevkeys & KEY_DOWN))
        {
            if (pointer >= menu->NumEntries-1) pointer = menu->NumEntries-1;
            else
            {
                pointer++;
                updatemenu = true;
            }
        }
        *prevkeys = keys;
        swiWaitForVBlank();
    }
}

//========================================================================================
//=FILE=OPEN==============================================================================
//========================================================================================

bool handleFile(FILE** dat, u16* prevkeys, const u8 mode)
{
    // open file to read from
    if (mode != 1)
    {
        u32 version = 0;
        pointer = 0;
        version = readData(version, 2);
        if (version != DataVersion)
        {
            printf("Data has non-matching version\nnumber.\n\nPress A or Start to quit.\n");
            waitForInput(prevkeys);
            return 0;
        }
        
        shift = 0;
        filebuffer = 0;
        filebuffer = readData(filebuffer, 4);
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
        
        shift = 0;
        filebuffer = 0;
    }
    return 1;
}

//========================================================================================
//=REWINDING==============================================================================
//========================================================================================

template <bool forward>
void rewindData(const int iteration)
{
    int i;
    if (!forward)
    {
        filebuffer = 0;
        shift = 0;
        pointer = 2;
        filebuffer = readData(filebuffer, 4);
        i = 0;
    }
    else
    {
        i = iteration-1;
    }
    for (; i < iteration; i++)
    {
        for (int y = 0; y < 192; y++)
        {
            while (shift >= 8)
            {
                filebuffer = readData(filebuffer, 1);
                shift -=8;
            }
            if (!(filebuffer & (1 << (31-shift)))) shift++;
            else if (Tests[i].ColorMode == 0)
            {
                while (1)
                {
                    shift += 17;
                    while (shift >= 8)
                    {
                        filebuffer = readData(filebuffer, 1);
                        shift -=8;
                    }
                    if ((!(Tests[i].PolyAttr & Opaque)) || (Tests[i].ExtendedTestData > 0))
                    {
                        if (!(filebuffer & (1 << (31-shift))))
                        {
                            shift++;
                            break;
                        }
                    }
                    else break;
                }
            }
            else
            {
                shift++;
                u8 bits = Tests[i].ColorMode * 5;
                while (1)
                {
                    while (shift >= 8)
                    {
                        filebuffer = readData(filebuffer, 1);
                        shift -=8;
                    }
                    u16 start = getSpanPoint();
                    u8 end = getSpanPoint();
                    for (; start <= end; start++)
                    {
                        shift += bits;
                        while (shift >= 8)
                        {
                            filebuffer = readData(filebuffer, 1);
                            shift -=8;
                        }
                    }
                    if ((!(Tests[i].PolyAttr & Opaque)) || (Tests[i].ExtendedTestData > 0))
                    {
                        if (!(filebuffer & (1 << (31-shift))))
                        {
                            shift++;
                            break;
                        }
                        else shift++;
                    }
                    else break;
                }
            }
        }
    }
}

//========================================================================================
//=DRAWING================================================================================
//========================================================================================

void drawPoly(const int iteration)
{
    
    glClearColor(0,0,0,31);
    glClearPolyID(Tests[iteration].RearID);
    glClearDepth(Tests[iteration].RearDepth);

    for (int i = 0; i < 8; i++)
        glSetOutlineColor(i, Tests[iteration].OutlineColors[i]);

    GFX_VIEWPORT = Tests[iteration].Viewport;

    glMatrixMode(GL_PROJECTION);
    glLoadMatrix4x4(&Tests[iteration].Projection);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPolyFmt(Tests[iteration].PolyAttr);
    GFX_CONTROL = Tests[iteration].Disp3DCnt;

    
    int verts;
    if (Tests[iteration].Vertices[3][0] != -512)
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
        GFX_COLOR = Tests[iteration].VertexColors[i];
        glVertex3v16(Tests[iteration].Vertices[i][0], Tests[iteration].Vertices[i][1], Tests[iteration].Vertices[i][2]);
    }

    if (Tests[iteration].ExtendedTestData != 0)
    {
        int lookup = Tests[iteration].ExtendedTestData - 1;

        for (u16 poly = 0; poly < ExtendedTests[lookup].NumPolygons; poly++)
        {
            bool begun = false;
            for (int j = ExtendedTests[lookup].Polygons[poly].Copies; j > 0; j--)
            {
                glPolyFmt(ExtendedTests[lookup].Polygons[poly].PolyAttr);
                int verts;
                if (ExtendedTests[lookup].Polygons[poly].Vertices[3][0] != -512)
                {
                    if (ExtendedTests[lookup].Polygons[poly].Strip)
                    {
                        if (!begun)
                        {
                            glBegin(GL_QUAD_STRIP);
                            begun = true;
                            verts = 4;
                        }
                        else verts = 2;
                    }
                    else
                    {
                        verts = 4;
                        glBegin(GL_QUAD);
                    }
                }
                else
                {
                    if (ExtendedTests[lookup].Polygons[poly].Strip)
                    {
                        if (!begun)
                        {
                            glBegin(GL_TRIANGLE_STRIP);
                            begun = true;
                            verts = 3;
                        }
                        else verts = 1;
                    }
                    else 
                    {
                        verts = 3;
                        glBegin(GL_TRIANGLE);
                    }
                }

                for (int i = 0; i < verts; i++)
                {
                    GFX_COLOR = ExtendedTests[lookup].Polygons[poly].VertexColors[i];
                    glVertex3v16(ExtendedTests[lookup].Polygons[poly].Vertices[i][0], ExtendedTests[lookup].Polygons[poly].Vertices[i][1], ExtendedTests[lookup].Polygons[poly].Vertices[i][2]);
                }
            }
        }
    }

	glFlush(Tests[iteration].Flush);

    REG_DISPCAPCNT |= DCAP_ENABLE;
    while(REG_DISPCAPCNT & DCAP_ENABLE);
}

//========================================================================================
//=TESTING================================================================================
//========================================================================================

bool test(const bool multispan, const u8 colormode)
{
    u16 mask;
    u8 bits;
    switch (colormode)
    {
    case 0:
        break;
    case 1:
        mask = 0x1F;
        bits = 5;
        break;
    case 2:
        mask = 0x3FF;
        bits = 10;
        break;
    default:
        mask = 0x7FFF;
        bits = 15;
        break;
    }

    bool errorfound = false;

    for (int y = 0; y < 192; y++)
    {
        while (shift >= 8)
        {
            filebuffer = readData(filebuffer, 1);
            shift -=8;
        }

        if (filebuffer & (1 << (31-shift)))
        {
            // span present
            shift++;
            u8 startspan = getSpanPoint();
            u8 endspan = getSpanPoint();
            bool done = false;

            for (int x = 0;; x++)
            {
                if (multispan && x > endspan && !done)
                {
                    while (17+shift > 32)
                    {
                        filebuffer = readData(filebuffer, 1);
                        shift -= 8;
                    }
                    
                    if (filebuffer & (1 << (31-shift)))
                    {
                        shift++;
                        startspan = getSpanPoint();
                        endspan = getSpanPoint();
                    }
                    else
                    {
                        shift++;
                        done = true;
                    }
                }

                if (x >= 256) break;
                
                u16 offset = y * 256 + x;
                u16 currcolor = VRAM_A[offset] & 0x7FFF;
                if (x < startspan || x > endspan) // if outside the data's current span
                {
                    VRAM_B[offset] = Black;
                    if (currcolor != ColorVoid) 
                    {
                        VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorOverdraw;
                        errorfound = true;
                    }
                }
                else // if inside the data's current span
                {
                    // find color data, also set reference image.
                    u16 color;
                    if (colormode != 0) // if rendering colors
                    {
                        while (bits+shift > 32)
                        {
                            filebuffer = readData(filebuffer, 1);
                            shift -= 8;
                        }
                        color = getColor(bits, mask);
                        VRAM_B[offset] = color;
                    }
                    else VRAM_B[offset] = White;

                    // test for color
                    if (currcolor == ColorVoid)
                    {
                        VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorMissing;
                        errorfound = true;
                    }
                    else if (colormode != 0) // if rendering colors
                    {
                        if ((currcolor & mask) != color)
                        {
                            VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorWrongTex;
                            errorfound = true;
                        }
                        else VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorMatch;
                    }
                    else VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorMatch;
                }
            }
        }
        else // no span
        {
            shift++;
            for (int x = 0; x < 256; x++)
            {
                u16 offset = y * 256 + x;
                u16 currcolor = VRAM_A[offset] & 0x7FFF;
                VRAM_B[offset] = Black;
                if (currcolor != ColorVoid) 
                {
                    VRAM_A[offset] = (VRAM_A[offset] & ~0x7FFF) | ColorOverdraw;
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

void record(FILE* dat, const bool multispan, const u8 colormode)
{
    u16 mask;
    u8 bits;
    switch (colormode)
    {
    case 0:
        break;
    case 1:
        mask = 0x1F;
        bits = 5;
        break;
    case 2:
        mask = 0x3FF;
        bits = 10;
        break;
    default:
        mask = 0x7FFF;
        bits = 15;
        break;
    }

    u16 colorbuffer[256];
    for (int y = 0; y < 192; y++)
    {
        s16 start;
        s16 end;
        int x = 0;
        for (int i = 0;; i++)
        {
            if (i != 0)
            {
                writeFile(dat);
                if (start == -1)
                {
                    filebuffer = writeBuffer(filebuffer, 0, 1);
                    writeFile(dat);
                    break;
                }
                else
                {
                    if (end == -1)
                    {
                        end = 255;
                        filebuffer = writeBuffer(filebuffer, end, 8);
                        writeFile(dat);
                    }
                    
                    if (colormode != 0)
                    {
                        for (; start <= end; start++)
                        {
                            filebuffer = writeBuffer(filebuffer, colorbuffer[start], bits);
                            writeFile(dat);
                        }
                    }
                }
            }

            if (!multispan && i == 1) break; // only do loop once if not multispan

            start = -1;
            end = -1;
            bool prevpixel = 0;
            for (; x < 256; x++)
            {
                u16 color = VRAM_A[y*256+x] & 0x7FFF;
                if (color == ColorVoid)
                {
                    if (prevpixel != 0)
                    {
                        end = x-1;
                        filebuffer = writeBuffer(filebuffer, end, 8);
                        x++;
                        break;
                    }
                }
                else
                {
                    if (prevpixel == 0)
                    {
                        filebuffer = writeBuffer(filebuffer, 1, 1);

                        start = x;
                        filebuffer = writeBuffer(filebuffer, start, 8);
                        prevpixel = 1;
                    }

                    if (colormode != 0) colorbuffer[x] = color & mask;
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
	PrintConsole* print = consoleDemoInit();

    videoSetMode(MODE_0_3D);

    glInit();

    int iteration = 0;
    u16 prevkeys;
    
	scanKeys();
    u8 mode;

    {
        u16 keys = keysHeld();

        if (keys & KEY_START || keys & KEY_SELECT)
        {
            prevkeys = keys;
            menu(&prevkeys, &mode);
        }
        else mode = 0; // default test mode
    }

    FILE* dat;
    if (!handleFile(&dat, &prevkeys, mode)) return 0;

    vramSetBankA(VRAM_A_LCD);
    vramSetBankB(VRAM_B_LCD);
    REG_DISPCAPCNT = DCAP_MODE(DCAP_MODE_A)
                    | DCAP_SRC_A(DCAP_SRC_A_3DONLY)
                    | DCAP_SIZE(DCAP_SIZE_256x192)
                    | DCAP_OFFSET(0)
                    | DCAP_BANK(DCAP_BANK_VRAM_A);


    bool TestCompletionTracker[NumEntries];
    for (int i = 0; i < NumEntries; i++)
        TestCompletionTracker[i] = 0;

    bool showresults = false;
    int numcomplete = 0;
    int numpass = 0;
    bool showreference = false;
    bool showrender = false;
    bool rewind = false;

//========================================================================================
//=MAIN LOOP==============================================================================
//========================================================================================

    while (1)
    {
        // poll input
		scanKeys();
        u16 keys = keysHeld();

        bool rewinded = false;
        while (checkFilters(iteration)) // skip filtered tests.
        {
            if (!rewind)
            {
            iteration++;
            rewindData<true>(iteration);
            }
            else
            {
                rewinded = true;
                if (iteration > 0)
                    iteration--;
                else
                {
                    iteration = 0;
                    rewind = false;
                }
            }
        }
        rewind = false;
        if (rewinded)
        {
            rewindData<false>(iteration);
        }

        // check if done
        if (iteration >= NumEntries)
        {
            if (mode == 1)
            {
                // make sure nothing got left behind in the buffer
                if (shift < 32)
                {
                    u8 tempbuffer = (filebuffer << (8-shift));
                    fwrite(&tempbuffer, 1, 1, dat);
                }
                consoleClear();
                printf("Recording Done.\n\nNew datafile present in rom\ndirectory.\n\nPress A or Start to quit.\n");
                print->cursorY = 23;
                printf("Ver. ");
                printf(Version);

                fclose(dat);
                waitForInput(&prevkeys);
                return 0;
            }
            else
            {
                mode = 3; // finished mode
                iteration--;
                rewindData<false>(iteration);
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

                errorfound = test(((!(Tests[iteration].PolyAttr & Opaque)) || (Tests[iteration].ExtendedTestData > 0)), Tests[iteration].ColorMode);
                showresults |= errorfound;

                if (!TestCompletionTracker[iteration])
                {
                    TestCompletionTracker[iteration] = true;
                    numcomplete++;
                    if (!errorfound) numpass++;
                }

                if (showresults) videoSetMode(MODE_FB0);
                else iteration++;

                consoleClear();
                if (mode == 3) printf("Testing complete!\n\n");
                printf("Tests Passed: %i/%i\n\n", numpass, numcomplete);
                if (mode != 0)
                {
                    printf("Press A to view next test.\nPress B to view previous test.\nPress X to skim forward.\nPress Y to skim backward.\nPress L to toggle hw data\nPress R to toggle rendered polys\nPress Start to close.\n\n");
                    printf("Viewing Test %i...\n\n", iteration+1);
                }
                else
                {
                    if (errorfound) printf("Press A to view next test.\nPress X to skim forward.\nPress L to toggle hw data\nPress R to toggle rendered polys\nPress Start to close.\n\n");
                    printf("Testing %i...\n\n", iteration+1);
                }
                printf("Green: Matching Pixel.\nRed: Missing Pixel.\nPink: Overdrawn Pixel.\nBlue: Incorrect Color.\n");
                
                print->cursorY = 23;
                printf("Ver. ");
                printf(Version);
            }
            else // recording new data file
            {
                consoleClear();
                printf("Recording %i...\n", iteration+1);

                print->cursorY = 23;
                printf("Ver. ");
                printf(Version);
                
                record(dat, ((!(Tests[iteration].PolyAttr & Opaque)) || (Tests[iteration].ExtendedTestData > 0)), Tests[iteration].ColorMode);
                iteration++;
            }
        }
        else // if showing results
        {
            if ((keys & KEY_A && !(prevkeys & KEY_A)) || keys & KEY_X)
            {
                showresults = false;
                videoSetMode(MODE_0_3D);
                iteration++;
                showreference = false;
                showrender = false;
            }

            if ((mode >= 2) && (((keys & KEY_B) && !(prevkeys & KEY_B)) || keys & KEY_Y))
            {
                showresults = false;
                videoSetMode(MODE_0_3D);
                iteration--;
                if (iteration < 0)
                    iteration = 0;
                rewindData<false>(iteration);
                showreference = false;
                showrender = false;
                rewind = true;
            }

            if ((keys & KEY_L && !(prevkeys & KEY_L)))
            {
                showreference = !showreference;
                showrender = false;
                if (showreference) videoSetMode(MODE_FB1);
                else videoSetMode(MODE_FB0);
            }
            if ((keys & KEY_R && !(prevkeys & KEY_R)))
            {
                showrender = !showrender;
                showreference = false;
                if (showrender) videoSetMode(MODE_0_3D);
                else videoSetMode(MODE_FB0);
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
