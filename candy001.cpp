//#include <graphics.h>  // EasyX插件
//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <algorithm>
//#include <mmsystem.h>  // 音乐播放
//#include <conio.h>
//#include <chrono>  // 添加计时相关头文件
//#pragma comment(lib, "winmm.lib")
//
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//const int BAR_WIDTH = 20;
//const int BAR_GAP = 5;
//const int MAX_HEIGHT = 500;
//
//// 添加颜色常量
//const COLORREF NORMAL_COLOR = WHITE;
//const COLORREF COMPARE_COLOR = RED;
//const COLORREF SORTED_COLOR = GREEN;
//
//// 添加枚举类型表示排序状态
//enum class SortState {
//    Unsorted,
//    Comparing,
//    Sorted
//};
//
//// 添加排序算法类型
//enum class SortType {
//    Bubble,
//    Quick,
//    Merge,
//    Insert,
//    Select
//};
//
//class SortVisualizer {
//private:
//    std::vector<int> data;
//    std::vector<SortState> states;  // 替换原来的sortedIndices
//    int comparisons = 0;
//    int swaps = 0;
//    bool isPaused = false;
//	int delay = 10;// 添加延迟时间
//    double sortTime = 0.0;
//
//    // 添加计时器类
//    class Timer {
//        std::chrono::high_resolution_clock::time_point start;
//    public:
//        Timer() : start(std::chrono::high_resolution_clock::now()) {}
//        double elapsed() {
//            auto end = std::chrono::high_resolution_clock::now();
//            return std::chrono::duration<double>(end - start).count();
//        }
//    };
//
//    // 优化绘制函数
//    void drawUI() {
//        cleardevice();
//        drawBars();
//        drawStats();
//        drawControls();
//        FlushBatchDraw();
//    }
//
//    void drawBars() {
//        for (int i = 0; i < data.size(); i++) {
//            COLORREF color = NORMAL_COLOR;
//            switch (states[i]) {
//            case SortState::Comparing: color = COMPARE_COLOR; break;
//            case SortState::Sorted: color = SORTED_COLOR; break;
//            default: break;
//            }
//            drawBar(i * (BAR_WIDTH + BAR_GAP), data[i], color);
//        }
//    }
//
//    void drawBar(int x, int height, COLORREF color) {
//        setfillcolor(color);
//        solidrectangle(x, WINDOW_HEIGHT - height,
//            x + BAR_WIDTH, WINDOW_HEIGHT);
//    }
//
//    void drawStats() {
//        TCHAR s[100];
//        swprintf_s(s, 100, _T("比较次数: %d  交换次数: %d  速度: %dms"),
//            comparisons, swaps, delay);
//        outtextxy(10, 10, s);
//
//        swprintf_s(s, 100, _T("排序用时: %.3f秒"), sortTime);
//        outtextxy(10, 30, s);
//    }
//
//    void drawControls() {
//        TCHAR s[100];
//        swprintf_s(s, 100, _T("空格键: 暂停/继续  +/-: 调整速度  ESC: 退出"));
//        outtextxy(10, 50, s);
//    }
//
//    // 更新比较状态
//    void compare(int i, int j) {
//        states[i] = states[j] = SortState::Comparing;
//        comparisons++;
//        drawUI();
//        handleInput();
//    }
//
//    // 交换元素
//    void swap(int i, int j) {
//        std::swap(data[i], data[j]);
//        swaps++;
//        drawUI();
//        handleInput();
//    }
//
//    // 处理用户输入
//    void handleInput() {
//        while (isPaused || _kbhit()) {
//            if (_kbhit()) {
//                char key = _getch();
//                switch (key) {
//                case ' ': isPaused = !isPaused; break;
//                case '+': if (delay > 10) delay -= 10; break;
//                case '-': delay += 10; break;
//                case 27: exit(0); break; // ESC键退出
//                }
//            }
//            if (isPaused) Sleep(100);
//        }
//        Sleep(delay);
//    }
//
//public:
//    SortVisualizer(int size) : data(size), states(size, SortState::Unsorted) {
//        reset();
//    }
//
//    void reset() {
//        comparisons = 0;
//        swaps = 0;
//        std::fill(states.begin(), states.end(), SortState::Unsorted);
//        for (int i = 0; i < data.size(); i++) {
//            data[i] = rand() % MAX_HEIGHT + 50;
//        }
//    }
//
//    // 统一的排序接口
//    void sort(SortType type) {
//        reset();
//        Timer timer;
//        PlaySound(TEXT("sort.wav"), NULL, SND_FILENAME | SND_ASYNC);
//
//        switch (type) {
//        case SortType::Bubble: bubbleSortImpl(); break;
//        case SortType::Quick: quickSortImpl(0, data.size() - 1); break;
//        case SortType::Merge: mergeSortImpl(0, data.size() - 1); break;
//        case SortType::Insert: insertionSortImpl(); break;
//        case SortType::Select: selectionSortImpl(); break;
//        }
//
//        sortTime = timer.elapsed();
//        markAllSorted();
//    }
//
//    // 添加获取排序时间的方法
//    double getSortTime() const {
//        return sortTime;
//    }
//
//    // 将getAlgorithmName移到public部分
//    static std::string getAlgorithmName(SortType type) {
//        switch (type) {
//        case SortType::Bubble: return "冒泡排序";
//        case SortType::Quick: return "快速排序";
//        case SortType::Merge: return "归并排序";
//        case SortType::Insert: return "插入排序";
//        case SortType::Select: return "选择排序";
//        default: return "未知排序";
//        }
//    }
//
//private:
//    // 简化后的排序实现
//    void bubbleSortImpl() {
//        for (int i = 0; i < data.size() - 1; i++) {
//            for (int j = 0; j < data.size() - i - 1; j++) {
//                compare(j, j + 1);
//                if (data[j] > data[j + 1]) {
//                    swap(j, j + 1);
//                }
//            }
//            states[data.size() - i - 1] = SortState::Sorted;
//        }
//    }
//
//    void quickSortImpl(int low, int high) {
//        if (low < high) {
//            int pivot = partition(low, high);
//            quickSortImpl(low, pivot - 1);
//            quickSortImpl(pivot + 1, high);
//
//            // 当某个区间排序完成时，将该区间标记为已排序
//            for (int i = low; i <= high; i++) {
//                if (states[i] != SortState::Sorted) {
//                    states[i] = SortState::Sorted;
//                }
//            }
//            drawUI();
//        }
//    }
//
//    int partition(int low, int high) {
//        int pivot = data[high];
//        int i = low - 1;
//
//        for (int j = low; j < high; j++) {
//            compare(j, high);
//            if (data[j] <= pivot) {
//                i++;
//                swap(i, j);
//            }
//        }
//        swap(i + 1, high);
//        return i + 1;
//    }
//
//    void mergeSortImpl(int left, int right) {
//        if (left < right) {
//            int mid = left + (right - left) / 2;
//            mergeSortImpl(left, mid);
//            mergeSortImpl(mid + 1, right);
//            merge(left, mid, right);
//
//            // 当某个区间合并完成时，将该区间标记为已排序
//            for (int i = left; i <= right; i++) {
//                if (states[i] != SortState::Sorted) {
//                    states[i] = SortState::Sorted;
//                }
//            }
//            drawUI();
//        }
//    }
//
//    void merge(int left, int mid, int right) {
//        std::vector<int> temp(right - left + 1);
//        int i = left;
//        int j = mid + 1;
//        int k = 0;
//
//        while (i <= mid && j <= right) {
//            compare(i, j);
//            if (data[i] <= data[j]) {
//                temp[k++] = data[i++];
//            }
//            else {
//                temp[k++] = data[j++];
//            }
//        }
//
//        while (i <= mid) {
//            temp[k++] = data[i++];
//        }
//
//        while (j <= right) {
//            temp[k++] = data[j++];
//        }
//
//        for (int p = 0; p < k; p++) {
//            data[left + p] = temp[p];
//            swaps++;
//            drawUI();
//        }
//    }
//
//    void insertionSortImpl() {
//        for (int i = 1; i < data.size(); i++) {
//            int key = data[i];
//            int j = i - 1;
//
//            while (j >= 0 && data[j] > key) {
//                compare(j, j + 1);
//                data[j + 1] = data[j];
//                swaps++;
//                drawUI();
//                j--;
//            }
//            data[j + 1] = key;
//            states[i] = SortState::Sorted;
//            drawUI();
//        }
//        markAllSorted();  // 标记排序完成
//    }
//
//    void selectionSortImpl() {
//        for (int i = 0; i < data.size() - 1; i++) {
//            int minIdx = i;
//            for (int j = i + 1; j < data.size(); j++) {
//                compare(i, j);
//                if (data[j] < data[minIdx]) {
//                    minIdx = j;
//                }
//            }
//            if (minIdx != i) {
//                swap(i, minIdx);
//            }
//            states[i] = SortState::Sorted;
//            drawUI();
//        }
//        states[data.size() - 1] = SortState::Sorted;
//        markAllSorted();  // 标记排序完成
//    }
//
//    void markAllSorted() {
//        std::fill(states.begin(), states.end(), SortState::Sorted);
//        drawUI();
//    }
//};
//
//// 主函数优化
//int main() {
//    srand(static_cast<unsigned int>(time(0)));  // 修复类型转换警告
//    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
//    BeginBatchDraw();
//    setbkcolor(BLACK);
//    cleardevice();
//
//    SortVisualizer visualizer(30);
//    const std::vector<SortType> algorithms = {
//        SortType::Bubble, SortType::Quick, SortType::Merge,
//        SortType::Insert, SortType::Select
//    };
//
//    std::vector<std::pair<std::string, double>> results;
//    bool running = true;
//
//    while (running) {
//        system("cls");
//        std::cout << "排序算法可视化演示\n"
//            << "-------------------\n";
//
//        for (int i = 0; i < algorithms.size(); i++) {
//            std::cout << i + 1 << ". "
//                << SortVisualizer::getAlgorithmName(algorithms[i]) << "\n";
//        }
//        std::cout << "6. 显示性能比较\n"
//            << "0. 退出程序\n"
//            << "ESC. 随时退出\n"
//            << "-------------------\n"
//            << "请选择: ";
//
//        int choice;
//        std::cin >> choice;
//
//        if (choice == 0) break;
//        if (choice == 6) {
//            system("cls");
//            std::cout << "性能比较结果:\n";
//            for (const auto& result : results) {
//                std::cout << result.first << ": " << result.second << "秒\n";
//            }
//            std::cout << "\n按任意键继续...\n";
//            _getch();
//            continue;
//        }
//
//        if (choice >= 1 && choice <= algorithms.size()) {
//            SortType type = algorithms[choice - 1];
//            visualizer.sort(type);
//            results.push_back({ SortVisualizer::getAlgorithmName(type), visualizer.getSortTime() });
//            std::cout << "\n排序完成! 用时: " << visualizer.getSortTime() << "秒\n";
//            std::cout << "按任意键继续...\n";
//            _getch();
//        }
//    }
//
//    closegraph();
//    return 0;
//}