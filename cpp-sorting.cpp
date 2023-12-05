﻿#include <iostream>
#include <random>
#include <algorithm>
#include <SFML/Graphics.hpp>

std::vector<int> generate_random_vector(int vector_size);
void print_vector(const std::vector<int>& intVect);
std::vector<int> bubble_sort(const std::vector<int>& intVect);
void bubble_sort_visual(const std::vector<int>& intVect);
std::vector<int> insertion_sort(const std::vector<int>& intVect);
void rect_vector_from_int(std::vector<sf::RectangleShape>& rect_vector, const std::vector<int>& vect);
void change_rect_color(std::vector<sf::RectangleShape>& rect_vector, int index, sf::Color color);
void draw_rectangles(const std::vector<sf::RectangleShape>& rect_vector);
void reset_rect_colors(std::vector<sf::RectangleShape>& rect_vector);
void insertion_sort_visual(const std::vector<int>& unsorted_vector);
std::vector<int> combine_vectors(const std::vector<int>& first, std::vector<int>::const_iterator merge_pos, const std::vector<int>& second);

bool is_sorting_done = false;

sf::RenderWindow window(sf::VideoMode(1700, 700), "Sorting");

sf::Vector2u windowSize = window.getSize();
int window_bottomX = 0;
int window_bottomY = windowSize.y;
int window_width = windowSize.x;

const int VECTOR_SIZE = 200;
const int RECT_OFFSET = 1;
const float REFRESH_DELAY = 0.001;
const sf::Color RECT_COLOR = sf::Color::Blue;
const sf::Color SELECTION_COLOR = sf::Color::Magenta;
const sf::Color SECONDARY_SELECTION_COLOR = sf::Color::Green;

int rect_width = (window_width - (VECTOR_SIZE * RECT_OFFSET)) / VECTOR_SIZE;

int main() {

    rect_width = (rect_width == 0) ? 1 : rect_width;

    std::vector<int> unsort_vect = generate_random_vector(VECTOR_SIZE);

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!is_sorting_done) {

            insertion_sort_visual(unsort_vect);

            is_sorting_done = true;
        }
    }
    return EXIT_SUCCESS;
}

void insertion_sort_visual(const std::vector<int>& unsorted_vector) {

    std::vector<sf::RectangleShape> rect_vector;

    std::vector<int> buffer;
    std::vector<int> combined_vector;

    for (int i = 0; i < unsorted_vector.size(); i++) {

        // Наложение векторов для визуальной видимости процесса сортировки
        combined_vector = combine_vectors(buffer, buffer.end(), unsorted_vector);

        rect_vector_from_int(rect_vector, combined_vector);

        change_rect_color(rect_vector, i, SECONDARY_SELECTION_COLOR);

        int buffer_num = unsorted_vector[i];

        for (int j = 0; j < unsorted_vector.size(); j++) {

            sf::sleep(sf::seconds(REFRESH_DELAY));

            change_rect_color(rect_vector, j, SELECTION_COLOR);

            if (j >= buffer.size()) {
                buffer.push_back(buffer_num);
                break;
            }
            if (buffer[j] >= buffer_num) {
                buffer.insert(buffer.begin() + j, buffer_num);
                break;
            }
            else {
                continue;
            }
        }
    }

    combined_vector = combine_vectors(buffer, buffer.end(), unsorted_vector);
    rect_vector_from_int(rect_vector, combined_vector);
    reset_rect_colors(rect_vector);
}

std::vector<int> combine_vectors(const std::vector<int>& first, std::vector<int>::const_iterator merge_pos, const std::vector<int>& second) {
    std::vector<int> combined_vector;
    combined_vector.insert(combined_vector.begin(), first.begin(), merge_pos);
    if (first.size() + second.begin() == second.end()) return combined_vector;
    combined_vector.insert(combined_vector.end(), second.begin() + first.size(), second.end());
    return combined_vector;
}

void bubble_sort_visual(const std::vector<int>& unsorted_vector) {
    std::vector<int> sort_vector = unsorted_vector;

    std::vector<sf::RectangleShape> rect_vector;

    int sort_vector_index = 0;
    int last_selected_index = 0;
    while (!std::is_sorted(sort_vector.begin(), sort_vector.end())) {
        sf::sleep(sf::seconds(REFRESH_DELAY));

        rect_vector_from_int(rect_vector, sort_vector);


        if (sort_vector_index < sort_vector.size() - 1) {
            int& left_num = sort_vector[sort_vector_index];
            change_rect_color(rect_vector, sort_vector_index, SELECTION_COLOR);
            int& right_num = sort_vector[sort_vector_index + 1];
            change_rect_color(rect_vector, sort_vector_index + 1, SECONDARY_SELECTION_COLOR);

            if (left_num > right_num)
                std::swap(left_num, right_num);
        }

        if (sort_vector_index > sort_vector.size() - 1) sort_vector_index = 0;
        else sort_vector_index++;

    }

    rect_vector_from_int(rect_vector, sort_vector); // Последний апдейт после полной сортировки
    reset_rect_colors(rect_vector);
}

void rect_vector_from_int(std::vector<sf::RectangleShape>& rect_vector, const std::vector<int>& vect) {
    
    rect_vector.clear();

    int offset = 0;
    for (int i = 0; i < vect.size(); i++) // Отрисовка вектора в виде прямоугольников
    {
        int value = vect[i];

        sf::RectangleShape rect(sf::Vector2f(rect_width, value * -4));

        rect.setFillColor(sf::Color::Blue);
        rect.setOrigin(-window_bottomX, -window_bottomY);
        rect.setPosition(offset, 0);

        offset += rect_width + RECT_OFFSET;

        rect_vector.push_back(rect);
    }

    //draw_rectangles(rect_vector);
}

void reset_rect_colors(std::vector<sf::RectangleShape>& rect_vector) {

    window.clear();

    for (sf::RectangleShape rect : rect_vector) {
        rect.setFillColor(RECT_COLOR);
        window.draw(rect);
    }

    window.display();
}

void change_rect_color(std::vector<sf::RectangleShape>& rect_vector, int index, sf::Color color) {
    rect_vector[index].setFillColor(color);
    draw_rectangles(rect_vector);
}

void draw_rectangles(const std::vector<sf::RectangleShape>& rect_vector) {

    window.clear();

    for (const sf::RectangleShape rect : rect_vector) {
        window.draw(rect);
    }

    window.display();
}

// O(n^2)
std::vector<int> bubble_sort(const std::vector<int>& intVect) {

    std::vector<int> sortVect = intVect;

    int i = 0;
    int iteration = 0;
    while (!std::is_sorted(sortVect.begin(), sortVect.end())) {
        if (i < sortVect.size() - 1) {
            if (sortVect[i] > sortVect[i + 1]) std::swap(sortVect[i], sortVect[i + 1]);
        }
        i++;
        if (i > sortVect.size() - 1) i = 0;
        iteration++;
    }

    std::cout << "Iter count: " + std::to_string(iteration) << std::endl;

    return sortVect;
}

// O(n)
std::vector<int> insertion_sort(const std::vector<int>& intVect) {

    std::vector<int> sortVect = intVect;
    std::vector<int> buffer;

    int iteration = 0;
    for (int i = 0; i < sortVect.size(); i++) {
        int buffer_num = sortVect[i];

        for (int j = 0; j < sortVect.size(); j++) {

            if (j >= buffer.size()) {
                buffer.push_back(buffer_num);
                break;
            }
            if (buffer[j] >= buffer_num) {
                buffer.insert(buffer.begin() + j, buffer_num);
                break;
            }
            else {
                continue;
            }
        }
        iteration++;
    }

    std::cout << "Iter count: " + std::to_string(iteration) << std::endl;

    return buffer;
}

std::vector<int> generate_random_vector(int vector_size) {
    std::vector<int> rand_array;

    std::random_device random;
    std::mt19937 mt(random());
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0; i < vector_size; ++i) {
        rand_array.push_back(distribution(mt));
    }

    return rand_array;
}

void print_vector(const std::vector<int>& intVect) {
    std::cout << "[";
    for (int i = 0; i < intVect.size(); i++) {
        std::cout << intVect[i];
        if (i == intVect.size() - 1) continue;
        std::cout << ", ";
    }
    std::cout << "]";
}