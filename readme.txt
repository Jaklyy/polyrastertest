==================================================
Welcome to the Jakly Polygon Rasterization Suite.
Or uh, polyrastertest as I like to call it.
...Just call it polyrastertest.


Usage:
While booting the test rom you can:
Hold Start to Record New Test Data to the root(probably) of an SD Card.
Hold Select to enable Manual Mode, where you must Press A to proceed through each test manually.
If not holding either of those buttons you will proceed through the testing automatically.

In order to load new data into the test you have to replace the data in the /data/ folder and build the test manually.
Which just means you have to set up devkitpro and type make into a mingw64 window idk.
If that's not clear enough then uh. idk. This is the first actually independently developed from scratch thing i've put out lol.


Notes:
Data was recorded on a New3DSXL via TWiLight Menu++ 26.3.0.
It is possible there are slight differences in the 3D gpu vs other NDS models but as far as im aware none are well documented.
Feel free to run the test on various pieces of actual hardware to find out!


Known Bugs:
1. For some reason closing the test also closes TWiLight Menu++ instead of reloading the menu, at least on new3dsxl. Not sure why.


Credits and Thanks:
StrikerX3 - Their line test rom provided a good reference for many of the things I struggled with implementing in this.
The melonDS team and the rest of the NDS emudev community - For inadvertently sending me down this rabbit hole, and providing support.