#include <graphics.h>  // EasyXͼ�ο�
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <mmsystem.h>  // ��������
#include <conio.h>
#pragma comment(lib, "winmm.lib")

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BAR_WIDTH = 20;
const int BAR_GAP = 5;
const int MAX_HEIGHT = 500;

class SortVisualizer {
private:
    std::vector<int> data;
    int comparisons = 0;
    int swaps = 0;

    // ���Ƶ�������
    void drawBar(int x, int height, COLORREF color) {
        setfillcolor(color);
        solidrectangle(x, WINDOW_HEIGHT - height,
            x + BAR_WIDTH, WINDOW_HEIGHT);
    }

    // �ػ���������
    void redraw(int highlightPos1 = -1, int highlightPos2 = -1) {
        cleardevice();
        for (int i = 0; i < data.size(); i++) {
            COLORREF color = WHITE;
            if (i == highlightPos1 || i == highlightPos2)
                color = RED;
            drawBar(i * (BAR_WIDTH + BAR_GAP), data[i], color);
        }

        // ��ʾͳ����Ϣ
        TCHAR s[50];
        // �� _stprintf ��Ϊ����ȫ�İ汾
        swprintf_s(s, 50, _T("�Ƚϴ���: %d  ��������: %d"), comparisons, swaps);
        outtextxy(10, 10, s);

        FlushBatchDraw();
        Sleep(50);
    }

public:
    SortVisualizer(int size) {
        // ��ʼ���������
        for (int i = 0; i < size; i++) {
            data.push_back(rand() % MAX_HEIGHT + 50);
        }
    }

    void bubbleSort() {
        PlaySound(TEXT("sort.wav"), NULL, SND_FILENAME | SND_ASYNC); // ��������

        for (int i = 0; i < data.size() - 1; i++) {
            for (int j = 0; j < data.size() - i - 1; j++) {
                comparisons++;
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                    swaps++;
                    redraw(j, j + 1);
                }
            }
        }
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pivot = partition(low, high);
            quickSort(low, pivot - 1);
            quickSort(pivot + 1, high);
        }
    }

    int partition(int low, int high) {
        int pivot = data[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            comparisons++;
            if (data[j] <= pivot) {
                i++;
                std::swap(data[i], data[j]);
                swaps++;
                redraw(i, j);
            }
        }
        std::swap(data[i + 1], data[high]);
        swaps++;
        redraw(i + 1, high);
        return i + 1;
    }
    // �� SortVisualizer ����������·���:
    void mergeSort(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            merge(left, mid, right);
        }
    }

    void merge(int left, int mid, int right) {
        std::vector<int> temp(right - left + 1);
        int i = left;
        int j = mid + 1;
        int k = 0;

        while (i <= mid && j <= right) {
            comparisons++;
            if (data[i] <= data[j]) {
                temp[k++] = data[i++];
            }
            else {
                temp[k++] = data[j++];
            }
            redraw(i, j);
        }

        while (i <= mid) {
            temp[k++] = data[i++];
            redraw(i - 1, -1);
        }

        while (j <= right) {
            temp[k++] = data[j++];
            redraw(-1, j - 1);
        }

        // ���ƻ�ԭ����
        for (int p = 0; p < k; p++) {
            data[left + p] = temp[p];
            swaps++;
            redraw(left + p);
        }
    }
};

int main() {
    srand(time(0));
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    BeginBatchDraw();
    setbkcolor(BLACK);
    cleardevice();

    SortVisualizer visualizer(30);

    // ѡ�������㷨
    int choice;
    std::cout << "ѡ�������㷨: 1.ð������ 2.�������� 3.�鲢����\n";
    std::cin >> choice;

    if (choice == 1)
        visualizer.bubbleSort();
    else if (choice == 2)
        visualizer.quickSort(0, 29);
    else if (choice == 3)
        visualizer.mergeSort(0, 29);
    _getch();
    closegraph();
    return 0;
}