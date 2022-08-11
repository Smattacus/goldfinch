"""
Project goldfinch. 2022.
"""

import numpy as np
from scipy.signal import correlate

from .exceptions import BadInputImage


class Sharpener:
    """
    Main interface to sharpen images. Contains
    the settings for sharpening an image.
    """

    DEFAULT_KERNEL = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]], dtype=np.uint8)

    def __init__(self, kernel: np.array = None):
        if kernel:
            self._kernel = kernel
        else:
            self._kernel = Sharpener.DEFAULT_KERNEL
        print("Hello world!")

    @property
    def Kernel(self):
        return self._kernel

    def sharpen_image(self, src: np.array):
        """
        Takes src, sharpens it with the internal kernel, and returns
        the sharpened image.

        This performs a 2D correlation of the image with the input Kernel.

        Works with a a 2D image where the third dimension is the color encoding. Typical RGB, for example, is
        src.shape -> (N, N, 3)
        """
        if len(src.shape) != 3:
            raise BadInputImage(
                "Input image must be 3 dimensional: [X, Y, color_encoding]"
            )
        output = 0 * src
        for i in range(src.shape[-1]):
            output[:, :, i] = correlate(src[:, :, i], self.Kernel, "same", "direct")
        return output
