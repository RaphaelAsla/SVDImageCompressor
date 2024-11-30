# SVDImageCompressor

This project implements an image compression algorithm using [Singular Value Decomposition (SVD)](https://en.wikipedia.org/wiki/Singular_value_decomposition).

## Compilation

### Prerequisites

Ensure you have the following dependencies installed on your system:
- [Eigen](https://eigen.tuxfamily.org/dox/)
- [OpenCV 2](https://opencv.org/releases/)

### Linux

To compile on Linux, simply clone the repository and run the provided build script:

```bash
git clone https://github.com/RaphaelAsla/SVDImageCompressor.git
cd SVDImageCompressor
./build.sh
```

### Windows
For Windows, you need to link against the OpenCV 2 libraries (Eigen is header-only). <br>
The exact method depends on your IDE or editor, but here are general steps:

Install Eigen and OpenCV 2.
Link the OpenCV libraries in your IDE (e.g., Visual Studio, Clion, etc.).
Build the project following your IDE's procedure for linking libraries.

### Usage
To run the image compressor, use the following command:

```bash
Copy code
./svd k image
```

Where:
- k is the number of singular values to retain for the compression (at most the rank of the image matrix).<br>
A lower k will result in higher compression but more loss of detail, while a higher k will preserve more details at the cost of less compression.
-image is the path to the image you want to compress.
