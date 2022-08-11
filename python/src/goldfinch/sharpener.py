"""
Project goldfinch. 2022.
"""

import numpy as np
from numpy import array
from scipy.signal import correlate2d

from .exceptions import BadInputImage


class Sharpener:
    """
    Main interface to sharpen images. Contains
    the settings for sharpening an image.
    """

    DEFAULT_KERNEL = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]], dtype=np.int)

    SCIPY_SIGNAL = "corr2d"
    BRUTE = "brute_force"

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
        src.astype(np.uint32)
        output = 0 * src
        for i in range(src.shape[-1]):
            output[:, :, i] = self._correlate(i, src, self.Kernel)
        print(output[np.where(output >= 256)])
        output[np.where(output >= 256)] = 255
        output[np.where(output <= 0)] = 0
        output.astype(np.uint8)
        return output

    def _correlate(self, i: int, src: array, kernel: array):
        correlators = {
            self.SCIPY_SIGNAL: self._correlate_scipy_signal,
            self.BRUTE: self._correlate_brute,
        }
        return correlators[self.SCIPY_SIGNAL](i, src, kernel)

    def _correlate_scipy_signal(self, i: int, src: array, kernel: array):
        return correlate2d(src[:, :, i], kernel, "same", "symm")

    def _correlate_brute(self):
        pass
