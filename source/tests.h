


constexpr TestData Tests[] =
{
// Category: Fill Rules: Primary =============================

  // Sub Cat: Normal ----------------------------------------
        //{.Vertices = {{-32}}}
    // Left Pos. X-Major - no fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Left Pos. Diagonal - fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 32}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Left Pos. Y-Major - fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 48}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Left Neg. X-Major - fill
        {.Vertices = {{-32, 32}, {32, 32}, {32, -16}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Left Neg. Diagonal - fill
        {.Vertices = {{-32, 32}, {32, 32}, {32, -32}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Left Neg. Y-Major - fill
        {.Vertices = {{-32, 32}, {32, 32}, {32, -48}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Right Pos. X-Major - fill
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 16}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Right Pos. Diagonal - no fill
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Right Pos. Y-Major - no fill
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 48}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Right Neg. X-Major - no fill
        {.Vertices = {{32, 32}, {-32, 32}, {-32, -16}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Right Neg. Diagonal - no fill
        {.Vertices = {{32, 32}, {-32, 32}, {-32, -32}, {-512}},
        .Tags = {FillRules, FR_Normal}},
    // Right Neg. Y-Major - no fill
        {.Vertices = {{32, 32}, {-32, 32}, {-32, -48}, {-512}},
        .Tags = {FillRules, FR_Normal}},

  // Sub Cat: Swapped ---------------------------------------

    // Fill Rules for swapped polygons *generally* follow the same rules as unswapped polygons
    // Key word being generally. You might notice that vertical right slopes aren't being filled. More on that later.

    // Left X-Major - top = fill, bot = no fill
        {.Vertices = {{0, -32}, {0, 32}, {48, 32}, {-32, -16}},
        .Tags = {FillRules, FR_Swapped, Niche}},
    // Left Y-Major - fill
        {.Vertices = {{0, -48}, {0, 32}, {16, 32}, {-16, -16}},
        .Tags = {FillRules, FR_Swapped, Niche}},
    // Left Diagonal - fill
        {.Vertices = {{0, -16}, {0, 32}, {16, 32}, {-16, 0}},
        .Tags = {FillRules, FR_Swapped, Niche}},
    // Right X-Major - top = fill, bot = no fill
        {.Vertices = {{0, -32}, {-1, 32}, {-48, 32}, {32, -16}},
        .Tags = {FillRules, FR_Swapped, Niche}},
    // Right Y-Major - no fill
        {.Vertices = {{0, -48}, {-1, 32}, {-16, 32}, {16, -16}},
        .Tags = {FillRules, FR_Swapped, Niche}},
    // Right Diagonal - no fill
        {.Vertices = {{0, -16}, {-1, 32}, {-16, 32}, {16, 0}},
        .Tags = {FillRules, FR_Swapped, Niche}},

  // Sub Cat: Override---------------------------------------
    
    // There are a few things that can force a polygon to fill all edges.

    // Transparency + Blend - Fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {FillRules, FR_Override, Translucency}},
    // Transparency + NO BLEND - no fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Tags = {FillRules, FR_Override, Translucency}},
    // Wireframe - Fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .PolyAttr = Wireframe | POLY_CULL_NONE,
        .Tags = {FillRules, FR_Override, Tag_Wireframe}},
    // Anti-Aliasing - Fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .Disp3DCnt = GL_ANTIALIAS,
        .Tags = {FillRules, FR_Override, AntiAliasing}},
    // Edge Marking - Fill
        {.Vertices = {{-32, -32}, {32, -32}, {32, 16}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .Tags = {FillRules, FR_Override, Edgemarking}},

// Category: Fill Rules: Unusual =============================

  // Sub Cat: Line Polygon Exception ------------------------

    // Note: My current theory is that this is an explicit fill rule
    // There may be alternative explanations, but this seems to check
    // out with all the other weird behavior this gpu has thrown out.

    // simple line polygon - fill
        {.Vertices = {{-10, -5}, {-10, -5}, {10, 5}, {-512}},
        .Tags = {FillRules, FR_Unusual}},
    // not quite a line polygon - no fill
        {.Vertices = {{-11, -6}, {-10, -5}, {10, 5}, {-512}},
        .Tags = {FillRules, FR_Unusual, Niche}},
    // if you can see this you're doing something wrong - no fill
        {.Vertices = {{-2, -1}, {0, 0}, {2, 1}, {-512}},
        .Tags = {FillRules, FR_Unusual, Niche}},
    // cursed line polygon 1 - fill, but like, only the line part
        {.Vertices = {{47, 8}, {-46, -27}, {47, 27}, {-46, -27}},
        .Tags = {FillRules, FR_Unusual, Niche}},
    // cursed line polygon 2 - see above
        {.Vertices = {{47, 8}, {-46, -27}, {0, 0}, {-46, -27}},
        .Tags = {FillRules, FR_Unusual, Niche}},
    // cursed line polygon 3 - fill
        {.Vertices = {{48, 0}, {0, -27}, {-40, -8}, {0, -27}},
        .Tags = {FillRules, FR_Unusual, Niche}},

  // Sub Cat: Swapped Vertical Left Glitch ------------------

    // instead of filling the right side when the right side is vertical
    // ...when swapped they uh- check the left side--
    // oops

    // half filled. oh dear.
        {.Vertices = {{-110, -12}, {-110, 24}, {0, 24}, {-140, 0}},
        .Tags = {FillRules, FR_Unusual, Niche, Clipping}},
    // is the slope half filled or half unfilled?
        {.Vertices = {{50, -30}, {-30, 50}, {0, 50}, {0, -20}},
        .Tags = {FillRules, FR_Unusual, Niche}},
    // x major slopes are never filled by this glitch, though. - no fill
        {.Vertices = {{50, -30}, {-20, 20}, {0, 20}, {0, -20}},
        .Tags = {FillRules, FR_Unusual, Niche}},

  // Sub Cat: Trapezoids ------------------------------------

    // this is a fill rule ...for some reason?
        {.Vertices = {{-25, 10}, {25, 10}, {50, -10}, {-50, -10}},
        .Tags = {FillRules, FR_Unusual, Niche}},
    // it applies to clipped vertices too!
        {.Vertices = {{-50, 90}, {50, 90}, {0, 110}, {-512, 0}},
        .Tags = {FillRules, FR_Unusual, Niche, Clipping}},
    // only x major slopes though
        {.Vertices = {{-25, 10}, {25, 10}, {35, -10}, {-45, -10}},
        .Tags = {FillRules, FR_Unusual, Niche}},
    // does not work when both the bottom of both slopes have the same x coord
        {.Vertices = {{0, 10}, {0, 10}, {50, -10}, {-50, -10}},
        .Tags = {FillRules, FR_Unusual, Niche}},
    // even when their y coord is different
        {.Vertices = {{0, 5}, {0, 10}, {50, -10}, {-50, -10}},
        .Tags = {FillRules, FR_Unusual, Niche}},

  // Sub Cat: The Curse of Edge Marking ---------------------

    // Edgemarking (only) + overlapping edges + same id = no fill????
    // right ymajor/vert (overriden by left ymajor/vert)
    // bottom xmajor/flat (overriden by top xmajor/flat)

    // I hate fill rules now (does this even count as a fill rule?)
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 1,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // Does not apply when poly ids are different
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .PolyAttr = Opaque | POLY_CULL_NONE | PolyID(1), 
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 1,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    /*// Also doesn't apply with aa, ofc
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .Disp3DCnt = GL_OUTLINE | GL_ANTIALIAS,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 1,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking, AntiAliasing}},*/
    // What about translucency? - no
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_OUTLINE | GL_BLEND,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 1,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking, Translucency}},
    // Wireframe? - yes, for some reason?
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .PolyAttr =  Wireframe | POLY_CULL_NONE,
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 5,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking, Tag_Wireframe}},
    // How about when over the Rear Plane? - no, but that makes sense
        {.Vertices = {{32, -32}, {-32, -32}, {-32, 32}, {-512}},
        .PolyAttr =  Opaque | POLY_CULL_NONE | PolyID(63),
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // also applies to verticals babyy
        {.Vertices = {{-32, -32}, {-32, 32}, {0, 32}, {0, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 2,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // bottom xmajor
        {.Vertices = {{-32, -32}, {-32, 0}, {32, -32}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 3,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // bottom flat
        {.Vertices = {{-32, -32}, {-32, 0}, {32, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 4,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // note that it's specifically the center of the polygon, and not the slopes that this applies to in this case.
        {.Vertices = {{-32, -32}, {-28, 0}, {28, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 4,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // the rules dont seem to combine, though (weird phrasing i know)
        {.Vertices = {{-32, -32}, {-32, 32}, {0, 32}, {0, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 4,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // Anyway now for some weird stuff:
        {.Vertices = {{-32, -2}, {-32, 0}, {32, 0}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 6,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // 
        {.Vertices = {{-32, 2}, {-32, 0}, {32, 0}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 7,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    //
        {.Vertices = {{-32, -32}, {-32, 0}, {32, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 8,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    //
        {.Vertices = {{-32, -32}, {-32, -2}, {32, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 9,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    //
        {.Vertices = {{-2, -32}, {0, -32}, {0, 32}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 10,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    //
        {.Vertices = {{0, -32}, {2, -32}, {0, 32}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 11,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    //
        {.Vertices = {{-32, -32}, {0, -32}, {0, 32}, {-32, 32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 12,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    //
        {.Vertices = {{-32, -32}, {2, -32}, {0, 32}, {-32, 32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 13,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // does not apply if the edge becomes properly edge marked
        {.Vertices = {{-32, -32}, {32, -32}, {32, 0}, {-32, 0}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 14,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // line polygons (horizontal)
        {.Vertices = {{-32, -32}, {-32, 0}, {32, 0}, {32, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 15,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // line poly (vert)
        {.Vertices = {{-32, -32}, {-32, 32}, {0, 32}, {0, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 16,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},
    // more curse
        {.Vertices = {{-32, -32}, {-32, 32}, {0, 32}, {0, -32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {Green},
        .ColorMode = 3,
        .ExtendedTestData = 16,
        .Tags = {FillRules, FR_Unusual, Niche, Edgemarking}},

        
// Category: Vertical Right Edge Shift =======================

    // vertical right edges are shifted left by one pixel

    // square
        {.Vertices = {{-32, -32}, {-32, 32}, {32, 32}, {32, -32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift}},
    // vertical 0 wide line polygon, right edges are *not* shifted left
        {.Vertices = {{0, -32}, {0, 32}, {0, 32}, {0, -32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift}},
    // vertical 1 wide line polygon, right edges are shifted left
        {.Vertices = {{0, -32}, {0, 32}, {1, 32}, {1, -32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift}},
    // but not when touching the edge of the screen
    // todo: test if it is shifted left when drawn oob? cause im pretty sure it does matter
        {.Vertices = {{-128, -32}, {-128, 32}, {-127, 32}, {-127, -32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift, Niche}},
    // swapped polygon 1
        {.Vertices = {{-32, -32}, {0, -32}, {0, 32}, {32, 32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift, Niche}},
    // swapped polygon 1 reversed
        {.Vertices = {{32, -32}, {0, -32}, {0, 32}, {-32, 32}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift, Niche}},
    // idk what this one even is
        {.Vertices = {{-32, -32}, {-32, 32}, {32, 0}, {-32, 0}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift, Niche}},
    // still dont know
        {.Vertices = {{32, -32}, {32, 32}, {-32, 0}, {32, 0}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift, Niche}},
    // Do note: it isn't always the case that a 0 wide span wont be shifted left.
        {.Vertices = {{72, 45}, {-63, 65}, {65, 65}, {65, -63}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {VertRightShift, Niche}},

// Category: Anti-Aliasing ===================================

  //Sub Cat: General Anti-Aliasing---------------------------

    // Todo

  // Sub Cat: Swapped Vertical Edge Glitch ------------------

    // yeah they also messed this up, im guessing they invert the aa alpha for swapped polygons to make them work properly?
    // ...even though vertical edges shouldn't be

    // swapped polygons are very glitchy, it turns out
        {.Vertices = {{-32, -32}, {0, -32}, {0, 32}, {32, 32}},
        .Disp3DCnt = GL_ANTIALIAS,
        .Tags = {AntiAliasing, AA_SwapVert, Niche}},
    // see above
        {.Vertices = {{32, -32}, {0, -32}, {0, 32}, {-32, 32}},
        .Disp3DCnt = GL_ANTIALIAS,
        .Tags = {AntiAliasing, AA_SwapVert, Niche}},
    // edge case within an edge case combined with an edge case
        {.Vertices = {{-110, -12}, {-110, 24}, {0, 24}, {-140, 0}},
        .Disp3DCnt = GL_ANTIALIAS,
        .Tags = {AntiAliasing, AA_SwapVert, Niche}},

// Category: Edge Marking ====================================

    // Basic Square
        {.Vertices = {{-32, -32}, {32, -32}, {32, 32}, {-32, 32}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000000000011111},
        .ColorMode = 2,
        .Tags = {Edgemarking}},
    // Basic Triangle
        {.Vertices = {{-32, -32}, {32, -32}, {0, 16}, {-512}},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors = {0b000000000011111},
        .ColorMode = 2,
        .Tags = {Edgemarking}},

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
        {.Vertices = {{-32, 0}, {0, 0}, {48, 0}, {32, 0}},
        .Tags = {Clipping, Niche}},
    // 1-2,
        {.Vertices = {{-32, 0}, {32, 0}, {48, 0}, {0, 0}},
        .Tags = {Clipping, Niche}},
    // or 2-4. 3 is never rendered
        {.Vertices = {{0, 0}, {-32, 0}, {48, 0}, {32, 0}},
        .Tags = {Clipping, Niche}},
    // Until the first vertex gets clipped.... (1-2)
        {.Vertices = {{-128, 0}, {-32, 0}, {32, 0}, {48, 0}},
        .Tags = {Clipping, Niche}},
    // Then things start to get interesting... (2-3)
        {.Vertices = {{-128, 0}, {-128, 0}, {32, 0}, {48, 0}},
        .Tags = {Clipping, Niche}},
    // 2-3
        {.Vertices = {{-128, 0}, {-128, 0}, {32, 0}, {48, 0}},
        .Tags = {Clipping, Niche}},
    // 3-4
        {.Vertices = {{-128, 0}, {-128, 0}, {-128, 0}, {48, 0}},
        .Tags = {Clipping, Niche}},
    // 4th vertex being clipped might complicate things, might not, probably depends on implementation of clipping (1-2)
        {.Vertices = {{-128, 0}, {-32, 0}, {32, 0}, {-128, 0}},
        .Tags = {Clipping, Niche}},
    //  2-3
        {.Vertices = {{-128, 0}, {-128, 0}, {32, 0}, {-128, 0}},
        .Tags = {Clipping, Niche}},

// Category: Upper Limits =====================================

  // Sub Cat: Polygon Limit ----------------------------------

    // There can only be 2048 polygons per frame.
        {.Vertices = {{-64, -64}, {-32, -64}, {-32, -32}, {-64, -32}},
        .ExtendedTestData = 22,
        .Tags = {UpperLimits, PolyLimit}},
    
  // Sub Cat: Vertex Limit -----------------------------------

    // There can only be 6144 vertices per frame.

    //This should render the polygon due it it barely fitting in the limit thanks to clipping
        {.Vertices = {{-256}, {-256}, {-256}, {-512}}, // lazy way to not render a polygon cause render order matters
        .ExtendedTestData = 23,
        .Tags = {UpperLimits, VertexLimit, Clipping}},
    // This should not render due to it just barely overflowing the limit
        {.Vertices = {{-256}, {-256}, {-256}, {-512}}, // lazy way to not render a polygon cause render order matters
        .ExtendedTestData = 24,
        .Tags = {UpperLimits, VertexLimit, Clipping}},

  // Sub Cat: Scanline Rasterization Timings -----------------

    // It appears that you can only render so much in one scanline before the rasterizer gives up on it.
    // Good luck passing these, basically requires sussing out rasterization timings.

    // Look at this
        {.Vertices = {{-256, -256}, {-256, 256}, {256, 256}, {256, -256}},
        .ExtendedTestData = 17,
        .Tags = {UpperLimits, Niche, UltraNiche, Clipping}},
    // Here we have the scanline *after* the polygon spam being partially aborted, doesn't seem to care about polygon size, just num of polys?
        {.Vertices = {{-256, -256}, {-256, 256}, {256, 256}, {256, -256}},
        .ExtendedTestData = 18,
        .Tags = {UpperLimits, Niche, UltraNiche, Clipping}},
    // Parial Line, Mid Scanline
        {.Vertices = {{-256, -256}, {-256, 256}, {256, 256}, {256, -256}},
        .ExtendedTestData = 19,
        .Tags = {UpperLimits, Niche, UltraNiche, Clipping}},
    // Here it is with a triangle
        {.Vertices = {{97, -25}, {72, 25}, {122, 25}, {-512}},
        .ExtendedTestData = 20,
        .Tags = {UpperLimits, Niche, UltraNiche}},
    // Also it impacts edgemarking jank for some reason.
        {.Vertices = {{-256, -256}, {-256, 256}, {256, 256}, {256, -256}},
        .VertexColors = {Green, Green, Green, Green},
        .Disp3DCnt = GL_OUTLINE,
        .OutlineColors {Red},
        .ColorMode = 2,
        .ExtendedTestData = 21,
        .Tags = {UpperLimits, Niche, UltraNiche, Edgemarking, Clipping}},
    // If we render the bg first, it does not fail to render.
        {.Vertices = {{-256, -256, -1}, {-256, 4, -1}, {256, 4, -1}, {256, -256, -1}},
        .ExtendedTestData = 17,
        .Tags = {UpperLimits, Niche, UltraNiche, Clipping}},

// Catgory: Misc =============================================
 
    // left side has precedence over right side
    // Just an innocent square c:
        {.Vertices = {{-32, -32}, {-32, 32}, {32, 33}, {32, -32}},
        .Tags = {Misc, Niche}},
    // Evil square
        {.Vertices = {{-32, -32}, {-32, 33}, {32, 32}, {32, -32}},
        .Tags = {Misc, Niche}},
    // pointer never goes backwards
        {.Vertices = {{-30, -14}, {20, 15}, {52, 15}, {-51, 10}},
        .Tags = {Misc, Niche}},
    //these slopes are identical, but render differently due to rounding.
        {.Vertices = {{-64, 0}, {64, -41}, {64, 41}, {-512, 0}},
        .PolyAttr = Trans(30) | POLY_CULL_NONE,
        .Disp3DCnt = GL_BLEND,
        .Tags = {Misc}},

  // Sub Cat: Second Vertex is Weird ------------------------

    // Second vertex behaves differently vs others for w/e reason.

    // should behave normally
        {.Vertices = {{-32, -32}, {-1, -1}, {32, 32}, {32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE,
        .Tags = {Misc, Tag_Wireframe, Niche}},
    // should behave normally ...or not?
        {.Vertices = {{-32, -32}, {0, 0}, {32, 32}, {32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE,
        .Tags = {Misc, Tag_Wireframe, Niche}},
    // should glitch out, behaving as if it was swapped
        {.Vertices = {{-32, -32}, {1, -1}, {32, 32}, {32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE,
        .Tags = {Misc, Tag_Wireframe, Niche}},
    // however only the second vertex should cause this behavior
        {.Vertices = {{1, -1}, {32, 32}, {32, -32}, {-32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE,
        .Tags = {Misc, Tag_Wireframe, Niche}},
    // should also behave normally
        {.Vertices = {{-32, -32}, {-32, -32}, {32, 32}, {32, -31}},
        .PolyAttr = Wireframe | POLY_CULL_NONE,
        .Tags = {Misc, Tag_Wireframe}},
    /*// not sure if this one would behave weirdly tbh? idk im just gonna throw it in for the heck of it. might get removed.
        {.Vertices = {{-2, -1}, {0, 0}, {-2, -1}, {2, 1}},
        .PolyAttr = Wireframe | POLY_CULL_NONE,
        .Tags = {Misc, Wireframe, Niche}},*/
};

constexpr ExtTestData ExtendedTests[] =
{
    // ext 1
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{32, -32, -16}, {32, 32, -16}, {-32, 32, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 2
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-1, -32, -16}, {-1, 32, -16}, {32, 32, -16}, {32, -32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 3
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{32, 0}, {-32, 0}, {32, -32}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 4
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
    // ext 6
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 32, -16}, {-32, -1, -16}, {32, -1, -16}, {32, 32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 7
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 32, -16}, {-32, 2, -16}, {32, 0, -16}, {32, 32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 8
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, -1, -16}, {-32, 1, -16}, {32, -1, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 9
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 0, -16}, {-32, -2, -16}, {32, 0, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 10
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-1, -32, -16}, {-1, 32, -16}, {32, 32, -16}, {32, -32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 11
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{2, -32, -16}, {0, 32, -16}, {32, 32, -16}, {32, -32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 12
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-1, -32, -16}, {-1, 32, -16}, {1, 32, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 13
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{2, -32, -16}, {0, 32, -16}, {2, 32, -16}, {-512}},
            .VertexColors{Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 14
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, 0, -8}, {32, 0, -8}, {32, 32, -8}, {-32, 32, -8}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{-32, -1, -16}, {32, -1, -16}, {32, 32, -16}, {-32, 32, -16}},
            .PolyAttr = Opaque | POLY_CULL_NONE | PolyID(1),
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 15
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-32, -1, -16}, {32, -1, -16}, {32, -1, -16}, {-32, -1, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 16
        {.NumPolygons = 2,
        .Polygons = {{.Vertices = {{-1, -32, -16}, {-1, -32, -16}, {-1, 32, -16}, {-1, 32, -16}},
            .VertexColors{Red, Red, Red, Red}},
            {.Vertices = {{34, -34, -32}, {34, 34, -32}, {-34, 34, -32}, {-34, -34, -32}},
            .VertexColors{Blue, Blue, Blue, Blue}}}},
    // ext 17
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-80, -5}, {-80, 5}, {80, 5}, {80, -5}},
            .VertexColors{Yellow, Yellow, Yellow, Yellow},
            .Copies = 94}}},
    // ext 18
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-80, -5}, {-80, 5}, {0, 5}, {0, -5}},
            .VertexColors{Yellow, Yellow, Yellow, Yellow},
            .Copies = 501}}},
    // ext 19
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-124, -5}, {-124, 5}, {-100, 5}, {-100, -5}},
            .VertexColors{Yellow, Yellow, Yellow, Yellow},
            .Copies = 448}}},
    // ext 20
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-124, -5}, {-124, 5}, {-100, 5}, {-100, -5}},
            .VertexColors{Yellow, Yellow, Yellow, Yellow},
            .Copies = 2048}}},
    // ext 21
        {.NumPolygons = 1,
        .Polygons = {{.Vertices = {{-80, -90}, {-80, -80}, {80, -80}, {80, -90}},
            .VertexColors{Yellow, Yellow, Yellow, Yellow},
            .Copies = 94}}},
    // ext 22
        {.NumPolygons = 3,
        .Polygons = {{.Vertices = {{0, 0}, {0, 0}, {0, 0}, {-512}},
        .PolyAttr = Opaque | POLY_CULL_NONE | ForceZeroDot,
        .Copies = 2046,
        .Strip = true},
            {.Vertices = {{64, -64}, {32, -64}, {32, -32}, {64, -32}}},
            {.Vertices = {{-32, 64}, {32, 64}, {32, 32}, {-32, 32}}}}},
    // ext 23
        {.NumPolygons = 3,
        .Polygons = {{.Vertices = {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
        .PolyAttr = Opaque | POLY_CULL_NONE | ForceZeroDot,
        .Copies = 1533},
            {.Vertices = {{0, 0}, {0, 0}, {0, 0}, {-512}},
            .PolyAttr = Opaque | POLY_CULL_NONE | ForceZeroDot,
            .Copies = 3},
            {.Vertices = {{108, 0}, {140, -32}, {172, 0}, {140, 32}}}}},
    // ext 24
        {.NumPolygons = 3,
        .Polygons = {{.Vertices = {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
        .PolyAttr = Opaque | POLY_CULL_NONE | ForceZeroDot,
        .Copies = 1533},
            {.Vertices = {{0, 0}, {0, 0}, {0, 0}, {-512}},
            .PolyAttr = Opaque | POLY_CULL_NONE | ForceZeroDot,
            .Copies = 3},
            {.Vertices = {{-32, 0}, {0, -32}, {32, 0}, {0, 32}}}}},
};

constexpr int NumEntries = sizeof(Tests) / sizeof(Tests[0]);
