#include<string>
#include<vector>
#include<iostream>
#include<cstdlib>
#include<opencv2/opencv.hpp>
#include<atomic>
#include<fstream>
#include<chrono>

cv::Mat load_kernel(const char* filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cerr << "Unable to read file " << filename << '\n';
        std::exit(-1);
    }
    
    int width, height;
    file >> width;
    file >> height;

    cv::Mat kernel_f(cv::Size(width, height), CV_32F);
    for (int row = 0; row < height; ++row){
        for (int col = 0; col < width; ++col){
            file >> kernel_f.at<float>(cv::Point(col, row));
        }
    }

    float dividor = 0;
    file >> dividor;

    cv::Mat res = kernel_f / dividor;

    std::cout << "Using kernel:\n";
    for (int row = 0; row < height; ++row){
        for (int col = 0; col < width; ++col){
            std::cout << res.at<float>(cv::Point(col, row)) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;

    return res;
}

int main(const int argc, const char ** argv)
{
    if (argc < 4){
        std::cerr << "3 arguments expected";
        return EXIT_FAILURE;
    }

    cv::Mat kernel_f;
    kernel_f = load_kernel(argv[3]);

    cv::VideoCapture capture(argv[1]);
    double fps = capture.get(cv::CAP_PROP_FPS);
    int height = std::llround(capture.get(cv::CAP_PROP_FRAME_HEIGHT));
    int width = std::llround(capture.get(cv::CAP_PROP_FRAME_WIDTH));


        cv::Size dims(width,height);
#ifdef __gnu_linux__
    int codec = cv::VideoWriter::fourcc('a', 'v', 'c', '1');
#else
    int codec = cv::VideoWriter::fourcc('h', '2', '6', '4');
#endif
    cv::VideoWriter writer(argv[2], codec, fps, dims, false);

    auto start_time = std::chrono::high_resolution_clock::now();

    std::atomic<int> frame_n;
    frame_n = 1;
    while(capture.isOpened()){
        auto curr_time = std::chrono::high_resolution_clock::now();
        auto duration = curr_time - start_time;
        std::cout << "\rTime: " << (frame_n / fps) << " s \tSpeed: " << (frame_n / fps) / (duration.count() / (1000 * 1000 * 1000) ) << "x         " << std::flush;
        
        cv::Mat frame;
        capture >> frame;
        if (frame.empty()){
            std::cout << "Finito\n";
            break;
        }
        
        cv::Mat new_frame;
        cv::cvtColor(frame, new_frame, cv::COLOR_BGR2GRAY);
        
        cv::Mat x;
        new_frame.convertTo(x, CV_32F);

        cv::filter2D(x, frame, -1, kernel_f);
        frame.convertTo(new_frame, CV_8U);

        writer.write(new_frame);
        ++frame_n;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}