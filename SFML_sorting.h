#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
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