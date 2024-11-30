# SVDImageCompressor

This project implements an image compression algorithm using Singular Value Decomposition (SVD).

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
