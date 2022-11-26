# Image Sharpener

This is a basic image sharpener that I made in order to learn the ropes of SystemC. The current implementation is very rough but it works for a 100x100 image.

Next steps are both refactors and features:

1. The SystemC logic for reading in and writing out streams can be abstracted to two mixins shared across all classes.
2. The PNG reader should dynamically accept an image and automatically set sizes as needed. Currently, they're hard coded.
3. Fix the PNG reader class so it does not need to open a file to set the `row_pointers` attribute.
4. Incorporate or create an RGB -> LAB and LAB -> RGB converter to avoid chromatic aberattions in the final output.
5. Integrate the SystemC with the Python testbench / code to generate the expected sharpened values.
6. Broaden the datatype support. Currently the SystemC model itself uses just `int` instead of parameterized SystemC data types; for example, `sc_int`.
7. Remove all instances of hard coded image width (currently, 100)
8. Accept a sharpening kernel instead of hard coding one.
9. (Optional) Rearchitect so that we don't need memory for the output; we just start streaming it out as the data is processed.
10. (Optional) Similarly, rearchitect that we don't need to start all of the data in memory arrays -- just store a smaller number of rows and begin sharpening while old data gets overwritten.