# Image Sharpener

This is a basic image sharpener that I made in order to learn the ropes of SystemC. The current implementation is very rough but it works for a 100x100 image.

Builds are handled with CMake.

# Theory of Operation

This is a simple image sharpener that consists of a source (`source.cpp`), sink (`sink.cpp`), sharpener (`sharpener.cpp`), and a top level program (`test_sharpener.cpp`) that wires them all together.


```
+----------+      +----------------------------+        +--------+
|          |      |                            |        |        |
|          |      |                            |        |        |
|          |      |                            |        |        |
|source.cpp|----->|      sharpener.cpp         |------->|sink.cpp|
|          |      |                            |        |        |
|          |      |                            |        |        |
|          |      |                            |        |        |
+----------+      +----------------------------+        +--------+
```

The flow of data, at a high level, proceeds like this:

1. The source loads a PNG image into a data array (using the linux `libpng`).
2. The source sends the image data into the sharpener.
3. The sharpener reads the PNG data into its own memory and performs image sharpening.
4. When the sharpener is done processing, it outputs the sharpened image data to the sink.
5. When all of the data is sent to the sink, the sink writes the output to a file.

The communication between the source <-> sharpener and sharpener <-> sink both follow a similar scheme:

1. The source waits for a `data_request` line to be driven `true`.
2. On receiving the request, it prepares data and drives a `data ready` signal `true`.
3. The source waits for another data request.

The receiving block follows a complementary pattern:

1. The receiver drives a `data_request` line `true`.
2. It waits for the corresponding `data_ready` signal to be driven `true`.
3. When that signal is driven true, it loads the data, and then drives a `data_req` again.

# Next Steps

There is a lot more to be done this model. Next steps are both refactors and features:

1. Abstract into mixins the SystemC logic for reading in and writing out streams.
2. The PNG reader should dynamically accept an image and automatically set sizes as needed. Currently, they're hard coded.
3. Fix the PNG reader class so it does not need to open a file to set the `row_pointers` attribute.
4. Incorporate or create an RGB -> LAB and LAB -> RGB converter to avoid chromatic aberattions in the final output.
5. Integrate the SystemC with the Python testbench / code to generate the expected sharpened values.
6. Broaden the datatype support. Currently the SystemC model itself uses just `int` instead of parameterized SystemC data types; for example, `sc_int`.
7. Remove all instances of hard coded image width (currently, 100)
8. Accept a sharpening kernel instead of hard coding one.
9. (Optional) Rearchitect so that we don't need memory for the output; we just start streaming it out as the data is processed.
10. (Optional) Similarly, rearchitect that we don't need to start all of the data in memory arrays -- just store a smaller number of rows and begin sharpening while old data gets overwritten.
11. Pack the RGB information into a single word.
12. Generate some waveforms!
13. Add signals to the communication protocol that allow the end of the image and each image row to be signaled; then this can be a variable length image sharpener.
14. The sink / sharpener / source models should have just one loop to model actual hardware. Right now, they are a bit more linear since I have them break out of the while loop after processing the one image.