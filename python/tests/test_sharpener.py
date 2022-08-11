"""
Tests for basic image sharpening algorithm.
"""
from pickletools import uint8
import pytest

import imageio.v3 as iio
import numpy as np

from goldfinch import Sharpener

TEST_INPUT = "INPUT"
TEST_OUTPUT = "OUTPUT"


@pytest.fixture
def input_mouse():
    src = iio.imread("python/tests/static/Vd-Orig.png")
    yield src


@pytest.fixture
def sharpened_mouse():
    src = iio.imread("python/tests/static/Vd-Sharp.png")
    yield src


@pytest.fixture
def input_basic():
    src = np.array(
        [
            [[1, 1, 1], [2, 2, 2], [2, 2, 2], [1, 1, 1]],
            [[1, 1, 1], [2, 2, 2], [2, 2, 2], [1, 1, 1]],
            [[1, 1, 1], [2, 2, 2], [2, 2, 2], [1, 1, 1]],
            [[1, 1, 1], [2, 2, 2], [2, 2, 2], [1, 1, 1]],
            [[1, 1, 1], [2, 2, 2], [2, 2, 2], [1, 1, 1]],
        ],
        dtype=np.uint8,
    )
    yield src


@pytest.fixture
def sharpened_basic():
    src = np.array(
        [
            [[0, 0, 0], [3, 3, 3], [3, 3, 3], [0, 0, 0]],
            [[0, 0, 0], [3, 3, 3], [3, 3, 3], [0, 0, 0]],
            [[0, 0, 0], [3, 3, 3], [3, 3, 3], [0, 0, 0]],
            [[0, 0, 0], [3, 3, 3], [3, 3, 3], [0, 0, 0]],
            [[0, 0, 0], [3, 3, 3], [3, 3, 3], [0, 0, 0]],
        ],
        dtype=np.uint8,
    )
    yield src


@pytest.fixture
def test_data(
    request,
    input_mouse,
    sharpened_mouse,
    input_basic,
    sharpened_basic,
):
    outputs = {
        "MOUSE": {
            TEST_INPUT: input_mouse,
            TEST_OUTPUT: sharpened_mouse,
        },
        "BASIC": {
            TEST_INPUT: input_basic,
            TEST_OUTPUT: sharpened_basic,
        },
    }
    yield outputs[request.param]


@pytest.mark.parametrize("test_data", ["MOUSE", "BASIC"], indirect=True)
def test_sharpener(test_data):
    """
    First test.
    """
    my_sharpener = Sharpener()
    test_sharpened_image = my_sharpener.sharpen_image(test_data[TEST_INPUT])
    iio.imwrite("test_output.png", test_sharpened_image)
    iio.imwrite("test_diff.png", test_sharpened_image - test_data[TEST_OUTPUT])
    assert np.all(test_sharpened_image == test_data[TEST_OUTPUT])
