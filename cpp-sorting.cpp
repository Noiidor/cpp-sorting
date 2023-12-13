#include <iostream>
#include <random>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

// Вынести весь этот мусор в header file
std::vector<int> generate_random_vector(int vector_size);
void print_vector(const std::vector<int>& intVect);
std::vector<int> bubble_sort(const std::vector<int>& intVect);
void bubble_sort_visual(const std::vector<int>& intVect);
std::vector<int> insertion_sort(const std::vector<int>& intVect);
void rect_vector_from_int(std::vector<sf::RectangleShape>& rect_vector, const std::vector<int>& vect);
void change_vert_color(sf::VertexArray& vert_array, int index, sf::Color color);
void draw_rectangles(const std::vector<sf::RectangleShape>& rect_vector);
void reset_vert_colors(sf::VertexArray& vert_array);
void insertion_sort_visual(const std::vector<int>& unsorted_vector);
std::vector<int> combine_vectors(const std::vector<int>& first, std::vector<int>::const_iterator merge_pos, const std::vector<int>& second);
void fill_vertex_array(sf::VertexArray& vert_array, const std::vector<int>& vect);
void draw_vertexes(const sf::VertexArray& vert_array);

bool is_sorting_done = false;

sf::RenderWindow window(sf::VideoMode(1500, 500), "Sorting");

sf::Vector2u windowSize = window.getSize();
int window_bottomX = 0;
int window_bottomY = windowSize.y;
int window_width = windowSize.x;

const int VECTOR_SIZE = 1500;
const uint16_t RECT_OFFSET = 0;
const float REFRESH_DELAY = 0;
const sf::Color DEFAULT_COLOR = sf::Color::Blue;
const sf::Color SELECTION_COLOR = sf::Color::Magenta;
const sf::Color SECONDARY_SELECTION_COLOR = sf::Color::Green;

float rect_width = (window_width - (VECTOR_SIZE * RECT_OFFSET)) / static_cast<float>(VECTOR_SIZE);

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
        //window.display();
    }
    return EXIT_SUCCESS;
}

// Рендеринг на основе VertexArray
void fill_vertex_array(sf::VertexArray& vert_array, const std::vector<int>& vect) {
    vert_array.clear();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);

    sf::Color randomColor(dis(gen), dis(gen), dis(gen));

    //const int max_num = *std::max_element(vect.begin(), vect.end());
    float height_offset = window_bottomY / static_cast<float>(VECTOR_SIZE);

    int offset = 0;
    for (const int i : vect) {
    
        /*std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 255);

        sf::Color randomColor(dis(gen), dis(gen), dis(gen));*/

        int vertex_origin_posX = window_bottomX + offset;
        int vertex_origin_posY = window_bottomY;

        int vert_top_offset = i * height_offset;

        // l - left, r - right, b - bottom, t - top
        sf::Vertex vertex_lb;
        vertex_lb.position = sf::Vector2f(vertex_origin_posX, vertex_origin_posY);
        vertex_lb.color = randomColor;
        vert_array.append(vertex_lb);

        sf::Vertex vertex_rb;
        vertex_rb.position = sf::Vector2f(vertex_origin_posX + rect_width, vertex_origin_posY);
        vertex_rb.color = randomColor;
        vert_array.append(vertex_rb);

        randomColor = sf::Color(dis(gen), dis(gen), dis(gen));

        sf::Vertex vertex_rt;
        vertex_rt.position = sf::Vector2f(vertex_origin_posX + rect_width, vertex_origin_posY - vert_top_offset);
        vertex_rt.color = randomColor;
        vert_array.append(vertex_rt);

        sf::Vertex vertex_lt;
        vertex_lt.position = sf::Vector2f(vertex_origin_posX, vertex_origin_posY - vert_top_offset);
        vertex_lt.color = randomColor;
        vert_array.append(vertex_lt);
        
        offset += rect_width + RECT_OFFSET;
    }
}

void bogo_sort_visual(const std::vector<int>& unsorted_vector) {
    
    std::vector<sf::RectangleShape> rect_vector;


}

// Перераспледелить window.clear() и window.display() для оптимизации
bool is_sorted_visual(const std::vector<int>& vect) {

    sf::VertexArray vert_array(sf::Quads);
    fill_vertex_array(vert_array, vect);

    for (size_t i = 0; i < vect.size(); i++) {
        //sf::sleep(sf::seconds(REFRESH_DELAY/2));

        change_vert_color(vert_array, i, SECONDARY_SELECTION_COLOR);
        //draw_rectangles(rect_vector);
        draw_vertexes(vert_array);

        int left_num = vect.at(i);
        int right_num;
        if (i == vect.size() - 1) {
            right_num = left_num;
        }
        else {
            right_num = vect.at(i + 1);
        }
        if (left_num > right_num) return false;
    }
    return true;
}

void insertion_sort_visual(const std::vector<int>& unsorted_vector) {

    std::vector<sf::RectangleShape> rect_vector;
    sf::VertexArray vert_array(sf::Quads);

    std::vector<int> buffer;
    std::vector<int> combined_vector;

    for (int i = 0; i < unsorted_vector.size(); i++) {

        // Наложение векторов для визуальной видимости процесса сортировки
        combined_vector = combine_vectors(buffer, buffer.end(), unsorted_vector);

        fill_vertex_array(vert_array, combined_vector);

        //change_vert_color(vert_array, i, SECONDARY_SELECTION_COLOR);
        draw_vertexes(vert_array);

        int buffer_num = unsorted_vector[i];

        for (int j = 0; j < unsorted_vector.size(); j++) {
            sf::sleep(sf::seconds(REFRESH_DELAY));

            if (j % 1 == 0 && j != 0) {
                //fill_vertex_array(vert_array, combined_vector);
                //reset_vert_colors(vert_array);
                //change_vert_color(vert_array, j-1, DEFAULT_COLOR);
                //change_vert_color(vert_array, j, SELECTION_COLOR);
                //draw_vertexes(vert_array);
            }


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
    fill_vertex_array(vert_array, combined_vector);
    draw_vertexes(vert_array);

    //is_sorted_visual(combined_vector);
}

void draw_vertexes(const sf::VertexArray& vert_array) {
    window.clear();
    window.draw(vert_array);
    window.display();
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

    //std::vector<sf::RectangleShape> rect_vector;
    sf::VertexArray vert_array(sf::Quads);

    int sort_vector_index = 0;
    int last_selected_index = 0;
    while (/*!std::is_sorted(sort_vector.begin(), sort_vector.end())*/!is_sorted_visual(sort_vector)) {
        sf::sleep(sf::seconds(REFRESH_DELAY));

        fill_vertex_array(vert_array, sort_vector);


        if (sort_vector_index < sort_vector.size() - 1) {
            int& left_num = sort_vector[sort_vector_index];
            change_vert_color(vert_array, sort_vector_index, SELECTION_COLOR);
            int& right_num = sort_vector[sort_vector_index + 1];
            change_vert_color(vert_array, sort_vector_index + 1, SECONDARY_SELECTION_COLOR);

            draw_vertexes(vert_array);

            if (left_num > right_num)
                std::swap(left_num, right_num);
        }

        if (sort_vector_index > sort_vector.size() - 1) sort_vector_index = 0;
        else sort_vector_index++;

    }

    fill_vertex_array(vert_array, sort_vector); // Последний апдейт после полной сортировки
    draw_vertexes(vert_array);
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

void reset_vert_colors(sf::VertexArray& vert_array) {

    for (int i = 0; i < vert_array.getVertexCount(); i++)
    {
        vert_array[i].color = DEFAULT_COLOR;
    }
}

//void change_rect_color(std::vector<sf::RectangleShape>& rect_vector, int index, sf::Color color) {
//    rect_vector[index].setFillColor(color);
//    draw_rectangles(rect_vector);
//}

void change_vert_color(sf::VertexArray& vert_array, int index, sf::Color color) {
    index *= 4;

    for (int i = 0; i <= 4; i++)
    {
        vert_array[index + i].color = color;
    }
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
    /*std::vector<int> rand_array;


    std::random_device random;
    std::mt19937 mt(random());
    std::distrib<int> distribution(;*/

    std::vector<int> source_vector;
    for (size_t i = 1; i < vector_size; i++)
    {
        source_vector.push_back(i);
    }
    std::random_shuffle(source_vector.begin(), source_vector.end());


    /*for (size_t i = 0; i < source_vector.size(); i++)
    {
        
    }*/
    

    /*for (int i = 0; i < vector_size; ++i) {
        rand_array.push_back(distribution(mt));
    }*/

    return source_vector;
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