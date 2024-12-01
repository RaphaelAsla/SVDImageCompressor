#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace Eigen;
using namespace cv;

MatrixXd ComputeU(const MatrixXd& A, const MatrixXd& V, const VectorXd& eigenvalues_AtA) {
    MatrixXd U(A.rows(), A.rows());
    for (int i = 0; i < V.cols(); i++) {
        U.col(i) = (1 / sqrt(eigenvalues_AtA(i))) * A * V.col(i);
    }
    return U;
}

MatrixXd ComputeV(const MatrixXd& A, const MatrixXd& U, const VectorXd& eigenvalues_AAt) {
    MatrixXd V(A.cols(), A.cols());
    for (int i = 0; i < U.cols(); i++) {
        V.col(i) = (1 / sqrt(eigenvalues_AAt(i))) * A.transpose() * U.col(i);
    }
    return V;
}

MatrixXd ComputeSVD(const MatrixXd& U, const MatrixXd& V, const VectorXd& eigenvalues, const int k) {
    MatrixXd A_hat = MatrixXd::Zero(U.rows(), V.cols());
    for (int i = 0; i < min(k, static_cast<int>(eigenvalues.size())); i++) {
        A_hat += U.col(i) * sqrt(eigenvalues(i)) * V.col(i).transpose();
    }
    return A_hat;
}

MatrixXd ComputeApproximation(MatrixXd& A, int k) {
    MatrixXd U, V;
    VectorXd eigenvalues;

    if (A.rows() > A.cols()) {
        EigenSolver<MatrixXd> solver(A.transpose() * A);
        eigenvalues = solver.eigenvalues().real().array();
        V = solver.eigenvectors().real();
        U = ComputeU(A, V, eigenvalues);
    } else {
        EigenSolver<MatrixXd> solver(A * A.transpose());
        eigenvalues = solver.eigenvalues().real().array();
        U = solver.eigenvectors().real();
        V = ComputeV(A, U, eigenvalues);
    }

    return ComputeSVD(U, V, eigenvalues, k);
}

Mat EigenToMat(const MatrixXd& Red, const MatrixXd& Green, const MatrixXd& Blue) {
    // All channels have the same dimensions
    const int rows = Red.rows();
    const int cols = Red.cols();

    const double minVal = min({Red.minCoeff(), Green.minCoeff(), Blue.minCoeff()});
    const double maxVal = max({Red.maxCoeff(), Green.maxCoeff(), Blue.maxCoeff()});

    Mat final_image(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Vec3b& pixel = final_image.at<Vec3b>(i, j);
            pixel[0] = static_cast<uchar>(255.0 * (Blue(i, j) - minVal) / (maxVal - minVal));
            pixel[1] = static_cast<uchar>(255.0 * (Green(i, j) - minVal) / (maxVal - minVal));
            pixel[2] = static_cast<uchar>(255.0 * (Red(i, j) - minVal) / (maxVal - minVal));
        }
    }

    return final_image;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    const int k = std::stoi(argv[1]);
    std::string image_path = argv[2];

    Mat image = imread(image_path, IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error loading image_path!" << std::endl;
        return -1;
    }

    std::vector<Mat> channels(3);
    split(image, channels);

    MatrixXd Blue(channels[0].rows, channels[0].cols);
    MatrixXd Green(channels[1].rows, channels[1].cols);
    MatrixXd Red(channels[2].rows, channels[2].cols);

    for (int i = 0; i < channels[0].rows; ++i) {
        for (int j = 0; j < channels[0].cols; ++j) {
            Blue(i, j) = channels[0].at<uchar>(i, j);
            Green(i, j) = channels[1].at<uchar>(i, j);
            Red(i, j) = channels[2].at<uchar>(i, j);
        }
    }

    const MatrixXd Red_hat = ComputeApproximation(Red, k);
    const MatrixXd Green_hat = ComputeApproximation(Green, k);
    const MatrixXd Blue_hat = ComputeApproximation(Blue, k);

    Mat A_hat = EigenToMat(Red_hat, Green_hat, Blue_hat);

    imwrite("assets/compressed_" + std::to_string(k) + '_' + image_path.substr(7), A_hat);
    imshow("Approximation", A_hat);

    waitKey(0);

    return 0;
}
