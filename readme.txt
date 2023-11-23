Welcome to the Jakly Polygon Rasterization Suite.
Or uh, polyrastertest as i like to call it.
...Just call it polyrastertest.

Usage:
When launching the test you can:
Hold Start to Record New Test Data to the root(probably) of an SD Card.
Hold Select to enable Manual Mode, where you must Press A to proceed through each test.
If not holding either of those buttons you will proceed through the testing automatically.

In order to load new data into the test you have to replace the data in the /data/ folder and build the test manually.
Which just means you have to set up devkitpro and type make into a mingw64 window idk.
If that's not clear enough then uh. idk how to do this. This is the first actually independently developed from scratch thing i've put out lol.


Notes:
Data was recorded on a New3DSXL via TWiLight Menu++ 26.3.0.
It is possible there are slight differences in the 3d gpu vs other NDS models but as of now none are well documented.


Known Bugs:
1. For some reason closing the test also closes TWiLight Menu++ instead of reloading the menu, at least on new3dsxl.


Credits and Thanks:
StrikerX3 - Their line test rom provided a good reference for many of the things I struggled with implementing in this.
