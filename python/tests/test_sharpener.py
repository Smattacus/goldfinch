"""
Tests for basic image sharpening algorithm.
"""
import pytest

import imageio
import numpy as np

from goldfinch import Sharpener


@pytest.fixture
def input_image():
    src = imageio.imread("python/tests/static/Vd-Orig.png")
    yield src

@pytest.fixture
def sharpened_result():
    src = imageio.imread("python/tests/static/Vd-Sharp.png")
    yield src

def test_sharpener(input_image, sharpened_result):
    """
        First test.
    """
    my_sharpener = Sharpener([0])
    test_sharpened_image = my_sharpener.SharpenImage(input_image)
    assert np.all(test_sharpened_image == sharpened_result)
