#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <sstream>

// загрузка изображения в формате PGM
std::vector<double> load_pgm(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    // пропускаем заголовок PGM
    std::string format;
    int width, height, max_value;
    file >> format >> width >> height >> max_value;

    // читаем значения пикселей изображения
    std::vector<double> pixels(width * height);
    for (int i = 0; i < width * height; i++) {
        int value;
        file >> value;
        pixels[i] = double(value) / max_value;
    }

    return pixels;
}

// классификация изображения с помощью нейронной сети
int classify_image(const std::vector<double>& pixels, const std::vector<std::vector<double>>& weights)
{
    // прямое распространение
    std::vector<double> activations(10);
    for (int i = 0; i < 10; i++) {
        double activation = 0.0;
        for (int j = 0; j < pixels.size(); j++) {
            activation += pixels[j] * weights[i][j];
        }
        activation += weights[i][pixels.size()];
        activations[i] = 1.0 / (1.0 + exp(-activation));
    }

    // выбираем класс с максимальной вероятностью
    int max_class = 0;
    double max_activation = activations[0];
    for (int i = 1; i < 10; i++) {
        if (activations[i] > max_activation) {
            max_class = i;
            max_activation = activations[i];
        }
    }

    return max_class;
}

int main()
{
const int SIZE = 28;
std::vector<std::vector<double>> images;

for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 100; j++) {
        std::ostringstream filename;
        filename << "digits/" << i << "_" << j << ".png";
        cv::Mat img = cv::imread(filename.str(), cv::IMREAD_GRAYSCALE);

        // Преобразуем изображение в черно-белое
        cv::Mat bin_img;
        cv::threshold(img, bin_img, 127, 255, cv::THRESH_BINARY_INV);

        // Нормализуем размер изображения
        cv::Mat norm_img;
        cv::resize(bin_img, norm_img, cv::Size(SIZE, SIZE));

        // Получаем вектор изображения
        std::vector<double> vec_img;
        norm_img.reshape(0, 1).convertTo(vec_img, CV_64FC1);

        // Добавляем вектор в список изображений
        images.push_back(std::move(vec_img));
    }
}


    for (int i = 0; i < 1000; i++) // Цикл, который идёт по строкам
    {
        for (int j = 0; j < 784; j++) // Цикл, который идёт по элементам
          std::  cout << images[i][j] << ' '; // Вывод элементов i строки вектора
       std:: cout << std::endl;
    }













//     // загрузка весов нейронной сети из файла
//     std::vector<std::vector<double>> weights(10);
//     for (int i = 0; i < 10; i++) {
//         std::string filename = "weights_" + std::to_string(i) + ".txt";
//         std::ifstream file(filename);
//         std::vector<double> row;
//         double value;
//         while (file >> value) {
//             row.push_back(value);
//         }
//         weights[i] = row;
//     }
//     // загрузка изображения пользователя
//     std::vector<double> pixels = load_pgm("image.pgm");
// int class_id=classify_image(pixels,weights);
//     std::cout << "Classified as: " << class_id << std::endl;

    }