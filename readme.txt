=========================================================
Welcome to the Jakly Polygon Rasterization Suite v1.0.2-b
Or uh, polyrastertest as I like to call it.
...Just call it polyrastertest.


Usage:
While booting the test rom you can:
Hold Start or Select to access a menu, where you can select filters to disable tests, record new data, or select a "manual" mode for testing.
If not holding either of those buttons you will proceed through the testing automatically.

In order to load new data into the test you have to replace the data in the /data/ folder and build the test manually.
Which just means you have to follow these instructions https://github.com/blocksds/sdk/blob/master/readme.rst to set up a blocksds build environment.
could likely also compile with devkitpro but you'll need to understand how to convert the makefile. (or dig up the old one from earlier commits).
If that's not clear enough then uh. idk. This is the first actually independently developed from scratch thing i've put out lol.


Notes:
Data was recorded on a New3DSXL via TWiLight Menu++ 26.3.0.
It is possible there are slight differences in the 3D gpu vs other NDS models but as far as im aware none are known of.
Feel free to run the test on various pieces of actual hardware to find out!


Known Bugs:
1. For some reason closing the test also closes TWiLight Menu++ instead of reloading the menu, at least on new3dsxl. Not sure why.
2. Sometimes dots appear when tabbing through the tests on hardware. Not sure why, but probably worth emulating.    Maybe.


Credits and Thanks:
StrikerX3 - Their line test rom provided a good reference for many of the things I struggled with implementing in this.
The melonDS team and the rest of the NDS emudev community - For inadvertently sending me down this rabbit hole, and providing support.